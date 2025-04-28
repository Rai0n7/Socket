#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <ctime>
#define BUFFER_SIZE 2048
using namespace std;

#pragma comment(lib, "ws2_32.lib")

BOOL runServer = TRUE;

BOOL WINAPI ConsoleHandler(DWORD signal) {
    if (signal == CTRL_C_EVENT) {
        runServer = FALSE;
    }
    return TRUE;
}

string curr_Time () {
	time_t now = time(0);   // get time now
    tm local_time;
    localtime_s(&local_time, &now);
	return "The current time is " + to_string(local_time.tm_hour) + ":" + to_string(local_time.tm_min) + ":" + to_string(local_time.tm_sec);
}

string get_Date (){
	time_t now = time(0);   // get time now
    tm local_time;
    localtime_s(&local_time, &now);
	return "The current date is " + to_string(local_time.tm_mday) + "." + to_string(local_time.tm_mon + 1) + "." + to_string(local_time.tm_year + 1900);
}

/*string ressources() {

}

string get_IP (){

}*/

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
        system("exit");
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
    while (runServer) {
        int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0); // Empf�ngt Daten vom Client
        if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
            cout << "Connection closed";
            continue;
        }

		buffer[bytesReceived] = '\0'; // Nullterminierung des empfangenen Datenblocks

        if (strcmp(buffer, "-help") == 0) {
            //  buffer[bytesReceived] = '\0'; // Nullterminierung des empfangenen Datenblocks
                string help = "\n\nCommands: \n"
                              "-gettime: Get the current time \n"
                              "-getdate: Get the current date \n"
                              "-getressources: Get the Pc informations \n"
                              "-getip: Get the IP of the client \n";

			    send(clientSocket, help.c_str(), help.size() + 1, 0); // Antwortet dem Client
                continue;
        }
        else if (strcmp(buffer, "-gettime") == 0) {
				string time = curr_Time();
				send(clientSocket, time.c_str(), time.size() + 1, 0); // Antwortet dem Client
                continue;
		}
        else if(strcmp(buffer, "-getdate") == 0){
				string date = get_Date();
				send(clientSocket, date.c_str(), date.size() + 1, 0); // Antwortet dem Client
				continue;
		}
        else if (strcmp(buffer, "-getip") == 0) {
        
        }
        else{
            //buffer[bytesReceived] = '\0'; // Nullterminierung des empfangenen Datenblocks
            cout << "Received: " << buffer << "\n";

            string response = "Message received";
            send(clientSocket, response.c_str(), response.size() + 1, 0); // Antwortet dem Client
        }
		/*else if (strcmp(buffer, "-getressources") == 0) {
        }*/
    }

    closesocket(clientSocket); // Schließt den Client-Socket
    closesocket(serverSocket); // Schließt den Server-Socket
    WSACleanup(); // Beendet die Verwendung der WinSock-Bibliothek

    return 0;
}
