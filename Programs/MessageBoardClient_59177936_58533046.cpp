#include "NetworkUtilities.h"
#include "CommandHandlers.h"

int main() {
    SOCKET sock = INVALID_SOCKET;
    string server_ip;
    int port;

    cout << "Enter server IP: "; // Prompt for user to input server IP address
    cin >> server_ip;
    cout << "Enter port number: "; // Prompt for user to input port number 
    cin >> port;
    cin.ignore();

    if (!initializeSocket(sock, server_ip, port)) { // connect to the server
        return 1; // Exit if socket initialization fails
    }

    Commands(sock);

    return 0;
}
