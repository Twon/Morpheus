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

bool socketError(SocketHandle const sock);

struct SocketCloser
{
    using pointer = SocketHandle; /// Unique ptr should store a file descriptor handle, not a pointer
    void operator()(pointer fd) const noexcept
    {
        if (!socketError(fd))
        {
#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
            ::closesocket(fd);
#else
            ::close(fd);
#endif
        }
    }
};

using Socket = boost::scope::unique_resource<int, SocketCloser>;
using SocketAndAddr = std::pair<Socket, struct sockaddr_in>;

bool socketError(SocketHandle const sock)
{
#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
    return (sock == invalidSocket);
#else
    return (sock < 0);
#endif
}

auto socketErrorCode() -> std::error_code
{
#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
    return std::error_code(WSAGetLastError(), std::system_category());
#else
    return std::error_code(errno, std::system_category());
#endif
}

auto createSocket() -> conf::exp::expected<Socket, std::error_code>
{
    auto const s = socket(AF_INET, SOCK_STREAM, 0);
    if (socketError(s))
    {
        return conf::exp::unexpected(socketErrorCode());
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
        return conf::exp::unexpected(socketErrorCode());
    }
    return addr;
}

auto createConnection(SocketAndAddr sockInfo) -> conf::exp::expected<SocketAndAddr, std::error_code>
{
    auto [sock, serv_addr] = std::move(sockInfo);
    if (auto const result = connect(sock.get(), (struct sockaddr*)&serv_addr, sizeof(serv_addr)); result < 0)
    {
        return conf::exp::unexpected(socketErrorCode());
    }
    return std::pair{std::move(sock), std::move(serv_addr)};
}

inline auto socketRead(SocketHandle s, void* buf, size_t len) noexcept
{
#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
    return ::recv(s, static_cast<char*>(buf), static_cast<int>(len), 0);
#else
    return ::read(s, buf, len);
#endif
}

inline auto socketWrite(SocketHandle s, void const* buf, size_t len) noexcept
{
#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
    return ::send(s, static_cast<const char*>(buf), static_cast<int>(len), 0);
#else
    return ::write(s, buf, len);
#endif
}

auto sendData(Socket const& sock, std::string_view data) -> conf::exp::expected<std::size_t, std::error_code>
{
    if (auto result = socketWrite(sock.get(), data.data(), data.size()); result < 0)
    {
        return conf::exp::unexpected(socketErrorCode());
    }
    else
    {
        return static_cast<std::size_t>(result);
    }
}

auto receiveData(Socket const& sock) -> conf::exp::expected<std::string, std::error_code>
{
    std::array<char, 1024> buffer = {0};
    if (auto result = socketRead(sock.get(), buffer.data(), buffer.size()); result < 0)
    {
        return conf::exp::unexpected(socketErrorCode());
    }
    else
    {
        return std::string(buffer.data(), static_cast<std::size_t>(result));
    }
}

} // namespace morpheus
