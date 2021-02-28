
#include <sys/types.h>
#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <sys/time.h>

using namespace std;

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        cerr << " Hostname and Port number missing\n";
        exit(0);
    }
    char *serverName = argv[1];
    char message[1500];
    int port = atoi(argv[2]);

    struct hostent *host = gethostbyname(serverName);
    sockaddr_in clientSocket;
    clientSocket.sin_family = AF_INET;
    clientSocket.sin_port = htons(port);
    clientSocket.sin_addr = **(struct in_addr **)host->h_addr_list;

    int ClientSocketID = socket(AF_INET, SOCK_STREAM, 0);

    if (ClientSocketID < 0)
    {
        cout << "Socket failed()\n";
        exit(0);
    }

    int Status = connect(ClientSocketID, (struct sockaddr *)&clientSocket, sizeof(clientSocket));

    if (Status < 0)
    {
        cout << "Failed to connect()\n";
        exit(0);
    }

    cout << "Successfuly connected\n";

    while (true)
    {
        string data;
        cout << "Client : ";
        getline(cin, data);

        strcpy(message, data.c_str());

        send(ClientSocketID, (char *)&message, sizeof(message), 0);
        
        if (data=="exit")
        {
            cout<<"Session exit Status - Success!"<<"\n";
            break;
        }

        cout << "Server: ";

        recv(ClientSocketID, (char *)&message, sizeof(message), 0);

        if (!strcmp(message, "exit"))
        {
            cout<<"Session exit Status - Success!"<<"\n";
            break;
        }
        cout<<message<<" \n";
    }

    close(ClientSocketID);

    return 0;
}