#include <iostream>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include "kripto.cpp"

using boost::asio::ip::tcp;

class HttpServer {
public:
    HttpServer(unsigned short port) 
        : acceptor_(io_context_, tcp::endpoint(tcp::v4(), port)) {}

    void start() {
        acceptConnection();
        io_context_.run();
    }

private:
    void acceptConnection() {
        acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                handleClient(std::move(socket));
            }
            acceptConnection();
        });
    }

    void handleClient(tcp::socket socket) {
        boost::asio::streambuf request_buffer;
        boost::asio::read_until(socket, request_buffer, "\r\n\r\n");
        
        std::string request_data((std::istreambuf_iterator<char>(&request_buffer)), 
                                  std::istreambuf_iterator<char>());
        //cout << "0";
        vector<string> rd = splitPerenos(request_data);
        request_data = rd[rd.size() - 1];
        
        // Печатаем полученный запрос на консоль (для отладки)
        //std::cout << "Received request:\n" << request_data << std::endl;

        std::string str = "";

        auto fut = async(kripto, std::ref(str), std::ref(request_data));
        int result = fut.get();




        // Формируем ответ, который будет отправлен клиенту
        std::string response = "HTTP/1.1 200 OK\r\n"
                               "Content-Type: text/plain\r\n"
                               "Connection: close\r\n\r\n" +
                               str; 
        //std::cout << str << std::endl;

        boost::asio::write(socket, boost::asio::buffer(response));
    }

    boost::asio::io_context io_context_;
    tcp::acceptor acceptor_;
};

int main() {

    ReadJsonFile(fileName, schemaName, tuplesLimit, *jsonStructure, *keys);
    pushInfo();

    try {
        HttpServer server(8080);
        std::cout << "Server is running on port 8080." << std::endl;
        server.start();
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}

