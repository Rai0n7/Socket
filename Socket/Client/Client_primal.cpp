/*
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    SOCKADDR_IN serverAddr;

    WSAStartup(MAKEWORD(2, 2), &wsaData); // Initialisiert die WinSock-Bibliothek

    clientSocket = socket(AF_INET, SOCK_STREAM, 0); // Erstellt einen neuen TCP-Socket

    serverAddr.sin_family = AF_INET; // Verwendet das IPv4-Protokoll
    serverAddr.sin_port = htons(54000); // Setzt den Port auf 54000
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr); // Konvertiert die IP-Adresse von Text- in Binärform

    connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)); // Verbindet sich mit dem Server

    std::cout << "Connected to the server!" << std::endl;

    closesocket(clientSocket); // Schließt den Client-Socket
    WSACleanup(); // Beendet die Verwendung der WinSock-Bibliothek

    return 0;
}
inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);: 
Diese Funktion konvertiert die IP-Adresse von Textform (z. B. "127.0.0.1") in Binärform, 
die von der sockaddr_in Struktur benötigt wird.*/