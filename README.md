# TCP & UDP Chat Application (C++ / Linux Sockets)

This project demonstrates a simple **multi-client chat system** using **C++ sockets** on Linux.  
It includes two versions:
- **TCP Chat** – reliable, connection-oriented communication
- **UDP Chat** – connectionless datagram-based communication with server-side broadcast

---

## 📌 Features
- Multi-client support  
- Real-time messaging using sockets and threads  
- Separate TCP and UDP implementations for comparison  

---

## ⚡ TCP Version
- Uses `SOCK_STREAM` sockets (connection-oriented).  
- Server maintains a socket per client (`accept`).  
- Messages are broadcast to all connected clients.  
- Reliable delivery is handled automatically by TCP.  

### Run (from `TCP-Application/`):
```bash
g++ server.cpp -o server -pthread
g++ client.cpp -o client -pthread

./server   # start server
./client   # run clients in separate terminals
```

⚡ UDP Version
- Uses `SOCK_DGRAM` sockets (connectionless).
- Server binds to a port and listens for datagrams (`recvfrom`).
- Server tracks client addresses and broadcasts incoming messages to all clients.
- Delivery is **not guaranteed** (packets may be lost, duplicated, or arrive out of order).

### Run (from UDP-Application/):
```bash
g++ server.cpp -o server
g++ client.cpp -o client

./server   # start server
./client   # run clients in separate terminals
```
