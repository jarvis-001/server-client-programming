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

int main(int argc, char const *argv[])
{
    if (argc!=2)
    {
        cerr << "Missing port number\n";
        exit(0);
    }

    int port = atoi(argv[1]);
    char message[1500];

    sockaddr_in serverSocket;
    bzero((char *)&serverSocket, sizeof(serverSocket));
    serverSocket.sin_family = AF_INET;
    serverSocket.sin_port = htons(port);
    serverSocket.sin_addr.s_addr = htonl(INADDR_ANY);

    int ServerSocketID = socket(AF_INET, SOCK_STREAM, 0);
    if (ServerSocketID<0)
    {
        cerr<<"Socket() attempt failed\n";
        exit(0);
    }

    int bindStatus =  bind(ServerSocketID, (struct sockaddr *)&serverSocket, sizeof(serverSocket));
    if (bindStatus<0)
    {
        cerr<<"Bind() attempt failed\n";
        exit(0);
    }
    
    cout<<"Connecting to the client...."<<"\n";

    listen(ServerSocketID, 1);

    //------- Code for connection socket -------
    sockaddr_in newSocket;
    socklen_t newSocketLen = sizeof(newSocket);

    int NewSocketID = accept(ServerSocketID, (struct sockaddr *)&newSocket, &newSocketLen);

    if (NewSocketID<0)
    {
        cerr<<" Accept unsuccessful()\n";
        exit(0);
    }
    cout<<"Connection to Client Successful"<<"\n";

    while (true)
    {
        cout<<"client: ";

        recv(NewSocketID, (char *)&message, sizeof(message), 0);

        if (!strcmp(message, "exit"))
        {
            cout<<"Terminated the session... "<<"\n";
            break;
        }
        cout<<message<<"\n";

        cout<<"Server: ";
        string data;
        // cin>>data;
        getline(cin, data);

        strcpy(message, data.c_str());

        send(NewSocketID, (char *)&message, sizeof(message), 0);

        if (data=="exit")
        {
            cout<<"Session exit status - Success!"<<"\n";
            break;
        }

    }
    
    close(NewSocketID);     close(ServerSocketID);

    return 0;
}