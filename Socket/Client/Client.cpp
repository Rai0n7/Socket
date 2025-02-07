#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string> // F�r std::string und std::getline
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
    SOCKET clientSocket;
    SOCKADDR_IN serverAddr;
    char buffer[BUFFER_SIZE];
    bool cont = 1;
    string message;

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

    clientSocket = socket(AF_INET, SOCK_STREAM, 0); // Erstellt einen neuen TCP-Socket

    serverAddr.sin_family = AF_INET; // Verwendet das IPv4-Protokoll
    serverAddr.sin_port = htons(54000); // Setzt den Port auf 54000
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr); // Konvertiert die IP-Adresse von Text- in Bin�rform

    connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)); // Verbindet sich mit dem Server

    cout << "Connected to the server!\n";

    while (true) {
        cout << "Enter your message: ";
        getline(cin >> ws, message);
        send(clientSocket, message.c_str(), message.size() + 1, 0); // Sendet eine Nachricht an den Server
        int bytesReceived = recv(clientSocket, buffer, 1024, 0); // Empf�ngt die Antwort vom Server

        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0'; // Nullterminierung des empfangenen Datenblocks
            cout << "Received: " << buffer << "\n";
        }
        /*cout << "If you wanna go on press 1, else press 0. -> ";
        cin >> cont;*/
    }

    closesocket(clientSocket); // Schlie�t den Client-Socket
    WSACleanup(); // Beendet die Verwendung der WinSock-Bibliothek

    return 0;
}
