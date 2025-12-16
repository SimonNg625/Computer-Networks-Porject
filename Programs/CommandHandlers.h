#ifndef COMMANDHANDLERS_H
#define COMMANDHANDLERS_H

#include <iostream>
#include <string>
#include <winsock2.h>

using namespace std;

// Commands handling functions
void Commands(SOCKET sock);
void Post(SOCKET sock);
void Delete(SOCKET sock);
void Get(SOCKET sock);
void Quit(SOCKET sock);

#endif
