#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <cstring>
using namespace std;

sockaddr_in serverAddr{};
int sock;

void receiveMessages() {
    char buffer[1024];
    socklen_t addrLen = sizeof(serverAddr);
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes = recvfrom(sock, buffer, sizeof(buffer), 0,
                             (sockaddr*)&serverAddr, &addrLen);
        if (bytes > 0) {
            buffer[bytes] = '\0';
            cout << "\n[Server]: " << buffer << endl;
        }
    }
}

int main() {
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        cerr << "Socket creation failed\n";
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    thread(receiveMessages).detach();

    string msg;
    while (true) {
        getline(cin, msg);
        sendto(sock, msg.c_str(), msg.size(), 0,
               (sockaddr*)&serverAddr, sizeof(serverAddr));
    }

    close(sock);
    return 0;
}
