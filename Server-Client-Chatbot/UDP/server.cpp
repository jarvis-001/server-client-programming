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
        cerr << "Enter the Port Number!\n";
        exit(0);
    }

    int port = atoi(argv[1]);
    char message[1500];

    sockaddr_in serverSocket;
    bzero((char *)&serverSocket, sizeof(serverSocket));
    serverSocket.sin_family = AF_INET;
    serverSocket.sin_port = htons(port);
    serverSocket.sin_addr.s_addr = htonl(INADDR_ANY);

    int ServerSocketID = socket(AF_INET, SOCK_DGRAM, 0);
    if (ServerSocketID<0)
    {
        cerr<<" Socket failed()"<<endl;
        exit(0);
    }

    int bindStatus =  bind(ServerSocketID, (struct sockaddr *)&serverSocket, sizeof(serverSocket));
    if (bindStatus<0)
    {
        cerr<<" Bind() attempt failed"<<"\n";
        exit(0);
    }
    
    cout<<"Connecting to the client...."<<"\n";
    // Initialising socket
    sockaddr_in newSocket;
    memset(&newSocket, 0, sizeof(newSocket));

    socklen_t newSocketLen = sizeof(newSocket);



    while (true)
    {
        cout<<"client: ";

        recvfrom(ServerSocketID, (char *)&message, sizeof(message), 0, (struct sockaddr*)&newSocket, &newSocketLen);

        if (!strcmp(message, "exit"))
        {
            cout<<"Session exit status - Success!"<<endl;
            break;
        }
        cout<<message<<endl;

        cout<<"server: ";
        string data;
        getline(cin, data);
        // cin>>data;
        strcpy(message, data.c_str());
        sendto(ServerSocketID, (char *)&message, sizeof(message), 0, (struct sockaddr*)&newSocket, sizeof(newSocket));

        if (data=="exit")
        {
            cout<<"Session exit status - Success!"<<endl;
            break;
        }
    }
    
    close(ServerSocketID);

    return 0;
}


