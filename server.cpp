#include <iostream>
#include <cstring>
#include <fstream>
#include <thread>
#include <unistd.h>
#include <arpa/inet.h>

class TCPServer {
private:
    int port;

public:
    TCPServer(int portNum) : port(portNum) {}

    void start() {
        int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket < 0) {
            std::cerr << "Error creating socket\n";
            return;
        }

        struct sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(port);
        serverAddress.sin_addr.s_addr = INADDR_ANY;

        if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
            std::cerr << "Bind failed\n";
            return;
        }

        listen(serverSocket, 5);

        while (true) {
            int clientSocket = accept(serverSocket, nullptr, nullptr);

            if (clientSocket < 0) {
                std::cerr << "Accept failed\n";
                return;
            }

            std::thread t(&TCPServer::handleClient, this, clientSocket);
            t.detach();
        }
    }

    void handleClient(int clientSocket) {
        char buffer[1024] = {0};
        read(clientSocket, buffer, 1024);

        std::ofstream logFile("log.txt", std::ios_base::app);
        logFile << buffer << std::endl;
        logFile.close();

        close(clientSocket);
    }
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>\n";
        return 1;
    }

    TCPServer server(std::stoi(argv[1]));
    server.start();

    return 0;
}