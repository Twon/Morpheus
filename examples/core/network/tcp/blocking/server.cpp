#include "common.hpp"

#include <morpheus/core/base/platform.hpp>
#include <morpheus/core/conformance/print.hpp>

#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else
    #include <arpa/inet.h> // for sockaddr_in, inet_addr()
    #include <sys/socket.h>
    #include <unistd.h> // for close()
#endif

#include <array>
#include <cstring>

using namespace morpheus;
using namespace morpheus::conf;

auto createSockAddr(std::uint16_t port) -> conf::exp::expected<struct sockaddr_in, std::error_code>
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY; // Bind to all interfaces
    addr.sin_port = htons(port);
    return addr;
}

auto acceptConnection(SocketAndAddr const& socketInfo) -> exp::expected<Socket, std::error_code>
{
    int addrlen = sizeof(socketInfo.second);
    // Accept a client connection
    if (auto clientSocket = accept(socketInfo.first.get(), (struct sockaddr*)&socketInfo.second, (socklen_t*)&addrlen); socketError(clientSocket))
    {
        return conf::exp::unexpected(socketErrorCode());
    }
    else
    {
        return Socket(clientSocket);
    }
}

int main()
{
    SocketSystem initialiseSockers;

    std::uint16_t const PORT = 8080;

    auto const setSockOptions = [](Socket sock) -> exp::expected<Socket, std::error_code>
    {
        // Allow reuse of the address/port
        int const opt = 1;
#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
        int const optName = SO_EXCLUSIVEADDRUSE;
#else
        int const optName = SO_REUSEADDR | SO_REUSEPORT;
#endif
        if (auto result = setsockopt(sock.get(), SOL_SOCKET, optName, reinterpret_cast<char const*>(&opt), sizeof(opt)); result < 0)
        {
            return conf::exp::unexpected(socketErrorCode());
        }
        return sock;
    };

    auto const combineSockAndAddr = [&](Socket sock) -> exp::expected<SocketAndAddr, std::error_code>
    {
        return createSockAddr(PORT).and_then([sock = std::move(sock)](struct sockaddr_in addr) mutable -> exp::expected<SocketAndAddr, std::error_code>
                                             { return std::pair{std::move(sock), std::move(addr)}; });
    };

    auto const bindAddress = [](SocketAndAddr sockInfo) -> exp::expected<SocketAndAddr, std::error_code>
    {
        auto [sock, addr] = std::move(sockInfo);
        // Bind socket to the address
        if (auto const result = bind(sock.get(), (struct sockaddr*)&addr, sizeof(addr)); result < 0)
        {
            return conf::exp::unexpected(socketErrorCode());
        }
        return std::pair{std::move(sock), std::move(addr)};
    };

    auto const listenOnSocket = [](SocketAndAddr socketInfo) -> exp::expected<SocketAndAddr, std::error_code>
    {
        // Listen for connections (max backlog 3)
        if (auto const result = listen(socketInfo.first.get(), 3); result < 0)
        {
            return conf::exp::unexpected(socketErrorCode());
        }
        return socketInfo;
    };

    auto const acceptConnectionAndFwdSocketInfo =
        [&PORT](SocketAndAddr socketInfo) -> exp::expected<std::tuple<Socket, struct sockaddr_in, Socket>, std::error_code>
    {
        print::print("Server listening on port {}...\n", PORT);
        if (auto client = acceptConnection(socketInfo); !client)
        {
            return exp::unexpected(client.error());
        }
        else
        {
            return std::tuple{std::move(socketInfo.first), std::move(socketInfo.second), std::move(*client)};
        }
    };

    auto receiveMessage =
        [](std::tuple<Socket, struct sockaddr_in, Socket>&& serverAndClient) -> exp::expected<std::tuple<Socket, struct sockaddr_in, Socket>, std::error_code>
    {
        auto const data = receiveData(std::get<2>(serverAndClient))
                              .and_then(
                                  [](auto const& data) -> exp::expected<std::vector<std::byte>, std::error_code>
                                  {
                                      print::print("Received: {}\n", std::string_view(reinterpret_cast<char const*>(data.data()), data.size()));
                                      return data;
                                  });
        if (!data)
        {
            return exp::unexpected(data.error());
        }
        return std::move(serverAndClient);
    };

    auto sendMessage =
        [](std::tuple<Socket, struct sockaddr_in, Socket>&& serverAndClient) -> exp::expected<std::tuple<Socket, struct sockaddr_in, Socket>, std::error_code>
    {
        auto&& [server_fd, serv_addr, client_fd] = std::move(serverAndClient);
        auto const sent = sendData(client_fd, "Hello from server!");
        if (!sent)
        {
            return exp::unexpected(sent.error());
        }
        return std::tuple{std::move(server_fd), std::move(serv_addr), std::move(client_fd)};
    };

    auto sockAddrClient = createSocket()
                              .and_then(setSockOptions)
                              .and_then(combineSockAndAddr)
                              .and_then(bindAddress)
                              .and_then(listenOnSocket)
                              .and_then(acceptConnectionAndFwdSocketInfo)
                              .and_then(receiveMessage)
                              .and_then(sendMessage);

    if (!sockAddrClient)
    {
        print::print("Error: {}\n", sockAddrClient.error().message());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
