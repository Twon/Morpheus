#include <common.hpp>
#include <morpheus/core/conformance/expected.hpp>
#include <morpheus/core/conformance/print.hpp>

#include <arpa/inet.h>
#include <unistd.h>

using namespace morpheus;
using namespace morpheus::conf;

int main()
{
    auto const combineSockAndAddr = [](Socket sock)
    {
        return createSockAddr("127.0.0.1", 8080)
            .and_then([sock = std::move(sock)](struct sockaddr_in addr) mutable -> exp::expected<std::pair<Socket, struct sockaddr_in>, std::error_code>
                      { return std::pair{std::move(sock), std::move(addr)}; });
    };

    auto const sendMsg = [](SocketAndAddr sockInfo) -> exp::expected<SocketAndAddr, std::error_code>
    {
        auto const& [sock, serv_addr] = sockInfo;
        if (auto const result = sendData(sock, "Hello from the client!"))
        {
            print::print("Sent {} bytes to server\n", *result);
        }
        else
        {
            return exp::unexpected(result.error());
        }
        return sockInfo;
    };

    auto const receiveMsg = [](SocketAndAddr sockInfo) -> exp::expected<SocketAndAddr, std::error_code>
    {
        auto const& [sock, serv_addr] = sockInfo;
        if (auto const result = receiveData(sock))
        {
            return exp::unexpected(result.error());
        }
        else
        {
            print::print("Received {} bytes from server: {}\n", result->size(), *result);
        }
        return sockInfo;
    };

    auto sockAndAdds = createSocket().and_then(combineSockAndAddr).and_then(createConnection).and_then(sendMsg).and_then(receiveMsg);

    if (!sockAndAdds)
    {
        print::print("Error: {}\n", sockAndAdds.error().message());
        return EXIT_FAILURE;
    }
    else
    {
        return EXIT_SUCCESS;
    }
}
