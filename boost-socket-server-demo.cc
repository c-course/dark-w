#include <boost/array.hpp>
#include <boost/asio.hpp>

int main(int argc, char **argv)
{
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor acceptor(
        io_service,
        boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 3200));

    boost::asio::ip::tcp::socket socket(io_service);
    acceptor.accept(socket);
    boost::system::error_code ign_code;
    socket.write_some(boost::asio::buffer("123"), ign_code);

    return 0;
}

