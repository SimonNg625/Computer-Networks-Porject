#include "CommandHandlers.h"
#include "NetworkUtilities.h"

void Post(SOCKET sock) {
    string postMessage;
    while (true) {
        cout << "client: ";
        getline(cin, postMessage); // get client input
        sendMessage(sock, postMessage + "\n"); // post message to server
        if (postMessage == "#") break; // break the loop when client input "#"
    }

    string response = receiveMessage(sock); // get server response
    cout << "server: " << response << endl; // show server response
}

void Get(SOCKET sock) {
    while (true) {
        string response = receiveMessage(sock); // get server response
        if (response == "#") break; // break the loop when client input "#"
        cout << "server: " << response << endl; // show server response
    }
}

void Delete(SOCKET sock) {
    bool deleteFinished = false; // I encoutered issues while using same method as above, thus changed to this method
    while (!deleteFinished) {
        cout << "client: ";
        string deleteID;
        getline(cin, deleteID); // get user input
        sendMessage(sock, deleteID + "\n"); // send user input to server

        if (deleteID == "#") {
            deleteFinished = true; // break the loop
            string response = receiveMessage(sock); 
            cout << "server: " << response << endl; // show server response
        }
    }
}

void Quit(SOCKET sock) {
    string response = receiveMessage(sock); // show server response
    cout << "server: " << response << endl;
    if (response == "OK") { // break the loop and close the socket
        closesocket(sock);
        WSACleanup();
        cout << "Connection closed." << endl;
        exit(0);
    }
}

void Commands(SOCKET sock) {
    string command;
    while (true) {  // keep prompting for commands until "QUIT"
        cout << "client: ";
        getline(cin, command);
        sendMessage(sock, command + "\n"); // send commands to server

        if (command == "POST") { // call command functions according to user input
            Post(sock);
        }
        else if (command == "GET") {
            Get(sock);
        }

        else if (command == "DELETE") {
            Delete(sock);
        }

        else if (command == "QUIT") {
            Quit(sock);
        }
        else {
            string response = receiveMessage(sock); // handle other commands that server cannot recognize
            cout << "server: " << response << endl;
        }
    }
}
