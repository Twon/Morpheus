#pragma once

#include <morpheus/core/base/platform.hpp>
#include <morpheus/core/conformance/expected.hpp>
#include <morpheus/core/conformance/print.hpp>

#include <boost/scope/unique_resource.hpp>

#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <unistd.h>
#endif

#include <array>
#include <cstdint>
#include <string>
#include <system_error>

namespace morpheus
{

#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
using SocketHandle = ::SOCKET;
constexpr SocketHandle invalidSocket = INVALID_SOCKET;
#else
using SocketHandle = int;
constexpr SocketHandle invalidSocket = -1;
#endif

struct SocketCloser
{
    using pointer = SocketHandle; /// Unique ptr should store a file descriptor handle, not a pointer
    void operator()(pointer fd) const noexcept
    {
#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
        if (fd != invalidSocket)
        {
            ::closesocket(fd);
        }
#else
        if (fd >= 0)
        {
            ::close(fd);
        }
#endif
    }
};

using Socket = boost::scope::unique_resource<int, SocketCloser>;
using SocketAndAddr = std::pair<Socket, struct sockaddr_in>;

auto createSocket() -> conf::exp::expected<Socket, std::error_code>
{
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)
    {
        return conf::exp::unexpected(std::error_code(errno, std::system_category()));
    }
    return Socket(s, SocketCloser{});
}

auto createSockAddr(std::string_view address, std::uint16_t port) -> conf::exp::expected<struct sockaddr_in, std::error_code>
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    // Convert IPv4 address from text to binary form
    if (auto const result = inet_pton(AF_INET, address.data(), &addr.sin_addr); result <= 0)
    {
        return conf::exp::unexpected(std::error_code(errno, std::system_category()));
    }
    return addr;
}

auto createConnection(SocketAndAddr sockInfo) -> conf::exp::expected<SocketAndAddr, std::error_code>
{
    auto [sock, serv_addr] = std::move(sockInfo);
    if (auto const result = connect(sock.get(), (struct sockaddr*)&serv_addr, sizeof(serv_addr)); result < 0)
    {
        return conf::exp::unexpected(std::error_code(errno, std::system_category()));
    }
    return std::pair{std::move(sock), std::move(serv_addr)};
}

auto sendData(Socket const& sock, std::string_view data) -> conf::exp::expected<std::size_t, std::error_code>
{
    if (auto result = send(sock.get(), data.data(), data.size(), 0); result < 0)
    {
        return conf::exp::unexpected(std::error_code(errno, std::system_category()));
    }
    else
    {
        return static_cast<std::size_t>(result);
    }
}

auto receiveData(Socket const& sock) -> conf::exp::expected<std::string, std::error_code>
{
    std::array<char, 1024> buffer = {0};
    if (auto result = read(sock.get(), buffer.data(), buffer.size()); result < 0)
    {
        return conf::exp::unexpected(std::error_code(errno, std::system_category()));
    }
    else
    {
        return std::string(buffer.data(), static_cast<std::size_t>(result));
    }
}

} // namespace morpheus
