#pragma once

#include <morpheus/core/conformance/expected.hpp>
#include <morpheus/core/conformance/print.hpp>

#include <unistd.h>
#include <arpa/inet.h>

#include <expected>
#include <memory>

namespace morpheus {

struct SocketCloser {
    using pointer = int; /// Unique ptr should store a file descriptor handle, not a pointer
    void operator()(pointer fd) const noexcept {
        if (fd >= 0){
            ::close(fd);
        }
    }
};

using Socket = std::unique_ptr<int, SocketCloser>;
using SocketAndAddr = std::pair<Socket, struct sockaddr_in>;

auto createSocket() -> conf::exp::expected<Socket, int> {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        return conf::exp::unexpected(s);
    }
    return Socket(s);
}

auto createSockAddr(std::string_view address, std::uint16_t port) -> conf::exp::expected<struct sockaddr_in, int> {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    // Convert IPv4 address from text to binary form
    if (auto const result = inet_pton(AF_INET, address.data(), &addr.sin_addr); result <= 0) {
        return conf::exp::unexpected(result);
    }
    return addr;
}

auto createConnection(SocketAndAddr sockInfo) -> conf::exp::expected<SocketAndAddr, int> {
    auto [sock, serv_addr] = std::move(sockInfo);
    if (auto const result = connect(sock.get(), (struct sockaddr *)&serv_addr, sizeof(serv_addr)); result < 0) {
        return conf::exp::unexpected(result);
    }
    return std::pair{std::move(sock), std::move(serv_addr)};
}

} // namespace morpheus