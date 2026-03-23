#include <morpheus/application/po/adapters/boost/asio.hpp>
#include <morpheus/application/po/options.hpp>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/write.hpp>
#include <boost/hana/functional/fix.hpp>
#include <boost/program_options.hpp>

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>

struct Settings
{
    // boost::asio::ip::address address;
    std::uint16_t port = 0;

    void addOptions(boost::program_options::options_description& options)
    {
        namespace po = boost::program_options;
        // clang-format off
        options.add_options()
            //("address", po::value(&address), "The address to listen on.");
            ("port", po::value(&port)->required(), "The port to listen on.");
        // clang-format on
    }
};

using namespace morpheus::application::po;

void force_shared_ptr_vtable()
{
    using T = std::array<char, 1024>;
    // Allocate a shared_ptr on the heap
    std::shared_ptr<T> dummy = std::shared_ptr<T>(new T);
    (void)dummy; // suppress unused variable warning
}

int main(int argc, char* argv[])
{
    Settings settings;
    auto const help = HelpDocumentation{.name = "EchoServer", .synopsis = "Simple application to echo back tcp messages"};
    auto const result = parseProgramOptions(argc, argv, help, settings);
    if (result)
        return result.value();

    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), settings.port));

    auto const doRead = boost::hana::fix(
        [](auto self, std::shared_ptr<boost::asio::ip::tcp::socket> socket) -> void
        {
            auto data = std::make_shared<std::array<char, 1024>>();

            socket->async_read_some(
                boost::asio::buffer(data->data(), data->size()),
                [self, socket, data](boost::system::error_code ec, std::size_t n) mutable -> void
                {
                    if (!ec)
                    {
                        boost::asio::async_write(
                            *socket,
                            boost::asio::buffer(data->data(), n), // Write only the 'n' bytes read in.
                            [self, socket, data](boost::system::error_code ec, std::size_t) mutable
                            {
                                if (!ec)
                                {
                                    self(socket);
                                }
                            });
                    }
                });
        });

    auto const doAccept = boost::hana::fix(
        [&acceptor, &doRead](auto self) -> void
        {
            acceptor.async_accept(
                [self, &doRead](boost::system::error_code ec, boost::asio::ip::tcp::socket socket)
                {
                    if (!ec)
                    {
                        doRead(std::make_shared<boost::asio::ip::tcp::socket>(std::move(socket)));
                    }
                    self();
                });
        });

    doAccept();

    io_context.run();
}
