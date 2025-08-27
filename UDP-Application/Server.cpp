#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
using namespace std;

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        cerr << "Socket creation failed\n";
        return 1;
    }

    sockaddr_in serverAddr{}, clientAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cerr << "Bind failed\n";
        close(sock);
        return 1;
    }

    cout << "UDP Server started on port 8080...\n";

    char buffer[1024];
    socklen_t clientLen = sizeof(clientAddr);

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes = recvfrom(sock, buffer, sizeof(buffer), 0,
                             (sockaddr*)&clientAddr, &clientLen);
        if (bytes > 0) {
            buffer[bytes] = '\0';
            cout << "Received: " << buffer << endl;

            // Echo message back to client
            sendto(sock, buffer, bytes, 0,
                   (sockaddr*)&clientAddr, clientLen);
        }
    }

    close(sock);
    return 0;
}
