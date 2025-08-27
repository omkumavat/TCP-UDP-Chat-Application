#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>
#include <thread>
using namespace std;

vector<int> clients;  // store client sockets

void handleClient(int clientSock) {
    char buffer[1024];
    while (true) {
        int bytes = read(clientSock, buffer, sizeof(buffer));
        if (bytes <= 0) {
            close(clientSock);
            break;
        }
        buffer[bytes] = '\0';

        // broadcast to all clients
        for (int sock : clients) {
            if (sock != clientSock) {
                send(sock, buffer, bytes, 0);
            }
        }
    }
}

int main() {
    int serverSock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSock, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSock, 5);

    cout << "Server started on port 8080...\n";

    while (true) {
        int clientSock = accept(serverSock, nullptr, nullptr);
        clients.push_back(clientSock);
        thread(handleClient, clientSock).detach();
    }
}
