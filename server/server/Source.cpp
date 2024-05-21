#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;

int main() {
    io_service service;
    //ip::tcp::endpoint ep(ip::tcp::v4(), 2001);
    ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 3000);

    ip::tcp::acceptor acc(service, ep);
    std::cout << "Server started on port 3000" << std::endl;
    while (true) {
        ip::tcp::socket sock(service);
        acc.accept(sock);
        std::string message = "Hello, client Vartan!\n";
        boost::system::error_code error;
        write(sock, buffer(message), error);
    }
    return 0;
}