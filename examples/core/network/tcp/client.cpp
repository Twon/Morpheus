#include <morpheus/core/conformance/expected.hpp>
#include <morpheus/core/conformance/print.hpp>
#include <common.hpp>

#include <unistd.h>
#include <arpa/inet.h>

#include <expected>

using namespace morpheus;
using namespace morpheus::conf;

int main()
{
    auto const combineSockAndAddr = [](Socket sock) {
        return createSockAddr("127.0.0.1", 8080).and_then([sock = std::move(sock)](struct sockaddr_in addr) mutable -> exp::expected<std::pair<Socket, struct sockaddr_in>, std::error_code> {
            return std::pair{std::move(sock), std::move(addr)};
        });
    };

    auto sockAndAdds = createSocket()
                           .and_then(combineSockAndAddr)
                           .and_then(createConnection);

    if (!sockAndAdds) {
        print::print("Error: {}\n", sockAndAdds.error().message());
        return EXIT_FAILURE;
    }

    auto const& [sock, serv_addr] = *sockAndAdds;

    std::string_view const msg = "Hello from client!";
    send(sock.get(), msg.data(), msg.size(), 0);

    std::array<char, 1024> buffer = {0};
    read(sock.get(), buffer.data(), buffer.size());

    print::print("Server says: {}\n", std::string_view(buffer.data(), buffer.size()));
    return EXIT_SUCCESS;
}