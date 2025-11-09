#include <morpheus/core/conformance/expected.hpp>
#include <morpheus/core/conformance/print.hpp>

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#include <expected>
#include <memory>

using namespace morpheus::conf;

struct SocketCloser {
    using pointer = int; /// Unique ptr should store a file descriptor handle, not a pointer
    void operator()(pointer fd) const noexcept {
        if (fd >= 0){
            ::close(fd);
        }
    }
};

using Socket = std::unique_ptr<int, SocketCloser>;

auto createSocket() -> exp::expected<Socket, int> {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        return exp::unexpected(s);
    }
    return Socket(s);
}

auto createSockAddr(std::string_view address, std::uint16_t port) -> exp::expected<struct sockaddr_in, int> {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    // Convert IPv4 address from text to binary form
    if (auto const result = inet_pton(AF_INET, address.data(), &addr.sin_addr); result <= 0) {
        return exp::unexpected(result);
    }
    return addr;
}

auto createConnection(std::pair<Socket, struct sockaddr_in> sockInfo) -> exp::expected<std::pair<Socket, struct sockaddr_in>, int> {
    auto [sock, serv_addr] = std::move(sockInfo);
    if (auto const result = connect(sock.get(), (struct sockaddr *)&serv_addr, sizeof(serv_addr)); result < 0) {
        return exp::unexpected(result);
    }
    return std::pair{std::move(sock), std::move(serv_addr)};
}

int main()
{
    auto const combineSockAndAddr = [](Socket sock) {
        return createSockAddr("127.0.0.1", 8080).and_then([sock = std::move(sock)](struct sockaddr_in addr) mutable -> exp::expected<std::pair<Socket, struct sockaddr_in>, int> {
            return std::pair{std::move(sock), std::move(addr)};
        });
    };

    auto sockAndAdds = createSocket()
                           .and_then(combineSockAndAddr)
                           .and_then(createConnection);

    if (!sockAndAdds) {
        return 1;
    }
    auto [sock, serv_addr] = std::move(*sockAndAdds);

    std::string_view const msg = "Hello from client!";
    send(sock.get(), msg.data(), msg.size(), 0);

    std::array<char, 1024> buffer = {0};
    read(sock.get(), buffer.data(), buffer.size());

    print::print("Server says: {}\n", std::string_view(buffer.data(), buffer.size()));
    return 0;
}