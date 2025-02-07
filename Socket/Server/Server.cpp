#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#define BUFFER_SIZE 2048
using namespace std;

#pragma comment(lib, "ws2_32.lib")

BOOL WINAPI ConsoleHandler(DWORD ctrlType) {
    switch (ctrlType) {
        case CTRL_C_EVENT:
            cout << "Ctrl-C event\n";
            return TRUE;
        case CTRL_CLOSE_EVENT:
            cout << "Ctrl-Close event\n";
            return TRUE;
        case CTRL_BREAK_EVENT:
            cout << "Ctrl-Break event\n";
            return TRUE;
        case CTRL_LOGOFF_EVENT:
            cout << "Ctrl-Logoff event\n";
            return TRUE;
        case CTRL_SHUTDOWN_EVENT:
            cout << "Ctrl-Shutdown event\n";
            return TRUE;
        default:
            return FALSE;
    }
}

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    SOCKADDR_IN serverAddr, clientAddr;
    char buffer[BUFFER_SIZE];
    int clientAddrSize = sizeof(clientAddr);

    if (SetConsoleCtrlHandler(ConsoleHandler, TRUE)) {
        cout << "The control handler is installed.\n";
    }
    else {
        cerr << "ERROR: Could not set control handler\n";
        return 1;
    }

    int result = WSAStartup(MAKEWORD(2, 2), &wsaData); // Initialisiert die WinSock-Bibliothek
    if (result != 0) {
        // Fehlerbehandlung
        fprintf(stderr, "WSAStartup failed with error: %d\n", result);
        return 1;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, 0); // Erstellt einen neuen TCP-Socket

    serverAddr.sin_addr.s_addr = INADDR_ANY; // Akzeptiert Verbindungen von jeder IP-Adresse
    serverAddr.sin_family = AF_INET; // Verwendet das IPv4-Protokoll
    serverAddr.sin_port = htons(54000); // Setzt den Port auf 54000

    bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)); // Bindet den Socket an die Adresse und den Port
    listen(serverSocket, SOMAXCONN); // Wartet auf eingehende Verbindungen

    cout << "Waiting for a connection... \n";

    clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &clientAddrSize); // Akzeptiert eine eingehende Verbindung

    cout << "Client connected! \n";

    // Schleife, um Nachrichten zu empfangen und zu senden
    while (true) {
        int bytesReceived = recv(clientSocket, buffer, 1024, 0); // Empf�ngt Daten vom Client
        if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
            cout << "Connection closed";
            break;
        }
        buffer[bytesReceived] = '\0'; // Nullterminierung des empfangenen Datenblocks
        cout << "Received: " << buffer << "\n";

        string response = "Message received";
        send(clientSocket, response.c_str(), response.size() + 1, 0); // Antwortet dem Client
    }

    closesocket(clientSocket); // Schließt den Client-Socket
    closesocket(serverSocket); // Schließt den Server-Socket
    WSACleanup(); // Beendet die Verwendung der WinSock-Bibliothek

    return 0;
}
