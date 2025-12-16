#include "NetworkUtilities.h"

bool initializeSocket(SOCKET& sock, const string& server_ip, int port) {
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed." << endl;
        return false;
    }

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        cerr << "Socket creation error." << endl;
        WSACleanup();
        return false;
    }

    // Set up server address structure
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, server_ip.c_str(), &serv_addr.sin_addr) <= 0) {
        cerr << "Invalid address." << endl;
        closesocket(sock);
        WSACleanup();
        return false;
    }

    // Attempt to connect
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        cerr << "Connection Failed." << endl;
        closesocket(sock);
        WSACleanup();
        return false;
    }

    return true;
}

void sendMessage(SOCKET sock, const string& message) {
    send(sock, message.c_str(), message.size(), 0);
}

string receiveMessage(SOCKET sock) {
    char buffer[BUFFER_SIZE] = { 0 };
    int bytesReceived = recv(sock, buffer, BUFFER_SIZE, 0);
    if (bytesReceived <= 0) {
        cerr << "Cannot receive message from server." << endl;
        return "";
    }
    return string(buffer, bytesReceived);
}
