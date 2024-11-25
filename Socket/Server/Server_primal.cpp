/*
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET serverSocket;
    SOCKADDR_IN serverAddr;

    WSAStartup(MAKEWORD(2, 2), &wsaData); // Initialisiert die WinSock-Bibliothek

    serverSocket = socket(AF_INET, SOCK_STREAM, 0); // Erstellt einen neuen TCP-Socket

    serverAddr.sin_addr.s_addr = INADDR_ANY; // Akzeptiert Verbindungen von jeder IP-Adresse
    serverAddr.sin_family = AF_INET; // Verwendet das IPv4-Protokoll
    serverAddr.sin_port = htons(54000); // Setzt den Port auf 54000

    bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)); // Bindet den Socket an die Adresse und den Port
    listen(serverSocket, SOMAXCONN); // Wartet auf eingehende Verbindungen

    std::cout << "Waiting for a connection..." << std::endl;

    SOCKET clientSocket;
    clientSocket = accept(serverSocket, NULL, NULL); // Akzeptiert eine eingehende Verbindung

    std::cout << "Client connected!" << std::endl;

    closesocket(clientSocket); // Schließt den Client-Socket
    closesocket(serverSocket); // Schließt den Server-Socket
    WSACleanup(); // Beendet die Verwendung der WinSock-Bibliothek

    return 0;
}
WSADATA wsaData;: Struktur, die Informationen über die WinSock-Implementierung enthält.

WSAStartup(MAKEWORD(2, 2), &wsaData);: Initialisiert die WinSock-Bibliothek. Das MAKEWORD(2, 2) spezifiziert, dass Version 2.2 verwendet wird.

socket(AF_INET, SOCK_STREAM, 0);: Erstellt einen neuen TCP-Socket.

bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));: Bindet den Socket an eine bestimmte IP-Adresse und Portnummer.

listen(serverSocket, SOMAXCONN);: Versetzt den Socket in den Modus, in dem er auf Verbindungen wartet.

accept(serverSocket, NULL, NULL);: Akzeptiert eine eingehende Verbindung.*/
