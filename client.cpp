#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

class TCPClient {
private:
    int port;
    std::string clientName;
    int period;

public:
    TCPClient(std::string name, int portNum, int sec) : clientName(name), port(portNum), period(sec) {}

    void start() {
        while (true) {
            int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
            if (clientSocket < 0) {
                std::cerr << "Error creating socket\n";
                return;
            }

            struct sockaddr_in serverAddress;
            serverAddress.sin_family = AF_INET;
            serverAddress.sin_port = htons(port);
            serverAddress.sin_addr.s_addr = INADDR_ANY;

            if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
                std::cerr << "Connection failed\n";
                return;
            }

            time_t currTime = time(nullptr);
            std::string timeStamp = "[" + std::to_string(currTime) + "] " + clientName;

            send(clientSocket, timeStamp.c_str(), timeStamp.length(), 0);
            close(clientSocket);

            sleep(period);
        }
    }
};

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <client_name> <port> <period>\n";
        return 1;
    }

    TCPClient client(argv[1], std::stoi(argv[2]), std::stoi(argv[3]));
    client.start();

    return 0;
}