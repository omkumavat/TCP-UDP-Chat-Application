#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
using namespace std;

void receiveMessages(int sock) {
    char buffer[1024];
    while (true) {
        int bytes = read(sock, buffer, sizeof(buffer));
        if (bytes > 0) {
            buffer[bytes] = '\0';
            cout << "\n[Server]: " << buffer << endl;
        }
    }
}

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr));

    thread(receiveMessages, sock).detach();

    string msg;
    while (true) {
        getline(cin, msg);
        send(sock, msg.c_str(), msg.size(), 0);
    }
}
