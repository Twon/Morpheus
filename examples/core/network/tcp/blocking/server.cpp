#include "common.hpp"

#include <morpheus/core/base/platform.hpp>
#include <morpheus/core/conformance/print.hpp>

#include <arpa/inet.h> // for sockaddr_in, inet_addr()
#include <unistd.h>    // for close()

#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <unistd.h>
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
    if (int client_fd = accept(socketInfo.first.get(), (struct sockaddr*)&socketInfo.second, (socklen_t*)&addrlen); client_fd < 0)
    {
        return conf::exp::unexpected(std::error_code(errno, std::system_category()));
    }
    else
    {
        return Socket(client_fd);
    }
}

int main()
{

    std::uint16_t const PORT = 8080;

    auto const setSockOptions = [](Socket sock) -> exp::expected<Socket, std::error_code>
    {
        // Allow reuse of the address/port
        int opt = 1;
        if (auto result = setsockopt(sock.get(), SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)); result < 0)
        {
            return conf::exp::unexpected(std::error_code(errno, std::system_category()));
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
            return conf::exp::unexpected(std::error_code(errno, std::system_category()));
        }
        return std::pair{std::move(sock), std::move(addr)};
    };

    auto const listenOnSocket = [](SocketAndAddr socketInfo) -> exp::expected<SocketAndAddr, std::error_code>
    {
        // Listen for connections (max backlog 3)
        if (auto const result = listen(socketInfo.first.get(), 3); result < 0)
        {
            return conf::exp::unexpected(std::error_code(errno, std::system_category()));
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

    auto sockAddrClient = createSocket()
                              .and_then(setSockOptions)
                              .and_then(combineSockAndAddr)
                              .and_then(bindAddress)
                              .and_then(listenOnSocket)
                              .and_then(acceptConnectionAndFwdSocketInfo);

    if (!sockAddrClient)
    {
        print::print("Error: {}\n", sockAddrClient.error().message());
        return EXIT_FAILURE;
    }

    auto const& [server_fd, serv_addr, client_fd] = *sockAddrClient;

    print::print("Server listening on port {}...\n", PORT);

    std::array<char, 1024> buffer = {0};
    socketRead(client_fd.get(), buffer.data(), buffer.size());
    print::print("Received: {}\n", std::string_view(buffer.data(), buffer.size()));

    std::string_view const reply = "Hello from server!";
    socketWrite(client_fd.get(), reply.data(), reply.size());

    return EXIT_SUCCESS;
}
