#ifndef NETWORKUTILITIES_H
#define NETWORKUTILITIES_H

#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define BUFFER_SIZE 4096

using namespace std;

bool initializeSocket(SOCKET& sock, const string& server_ip, int port);
void sendMessage(SOCKET sock, const string& message);
string receiveMessage(SOCKET sock);

#endif 
