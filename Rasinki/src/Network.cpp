#include "Network.h"

using namespace std;

const string SERVER_NOT_FULL = "OK";
const string SERVER_FULL     = "FULL";



Network::Network(Game *g, bool isServer) {
    if ( SDLNet_Init() < 0 ) {
        fprintf(stderr, "Couldn't initialize net: %s\n", SDLNet_GetError());
        SDL_Quit();
        exit(1);
    }
    socketSet = NULL;
    this->serverName = "localhost";
    this->isServer = isServer;
    game = g;
    receivedByteCount = 0;
    clientCount = 0;
    shutdownServer = false;

}


Network::~Network() {
     // Free our socket set (i.e. all the clients in our socket set)
    SDLNet_FreeSocketSet(socketSet);
    // Close our server socket, cleanup SDL_net and finish!
    if (serverSocket)
        SDLNet_TCP_Close(serverSocket);
    if (clientSocket[0])
        SDLNet_TCP_Close(clientSocket[0]);
    SDLNet_Quit();
}


void Network::Start() {
    if (isServer)
        SetUpServer();
    else
        ConnectToServer();
}


void Network::SetUpServer() {
    // Create the socket set with enough space to store our desired number of connections (i.e. sockets)
    socketSet = SDLNet_AllocSocketSet(MAX_SOCKETS);
    if (socketSet == NULL)
    {
        cout << "Failed to allocate the socket set: " << SDLNet_GetError() << "\n";
        exit(-1); // Quit!
    }
    else
    {
        cout << "Allocated socket set with size:  " << MAX_SOCKETS << ", of which " << MAX_CLIENTS << " are availble for use by clients." <<  endl;
    }
    // Initialize all the client sockets (i.e. blank them ready for use!)
    for (int loop = 0; loop < MAX_CLIENTS; loop++)
    {
        clientSocket[loop] = NULL;
        std::cout << "clientSocket[" << loop << "] initialized to NULL" << std::endl;
        socketIsFree[loop] = true; // Set all our sockets to be free (i.e. available for use for new client connections)
    }
    // Try to resolve the provided server hostname. If successful, this places the connection details in the serverIP object and creates a listening port on the provided port number
    // Note: Passing the second parameter as "NULL" means "make a listening port". SDLNet_ResolveHost returns one of two values: -1 if resolving failed, and 0 if resolving was successful
    int hostResolved = SDLNet_ResolveHost(&serverIP, NULL, PORT);
 
    if (hostResolved == -1)
    {
        cout << "Failed to resolve the server host: " << SDLNet_GetError() << endl;
    }
    else // If we resolved the host successfully, output the details
    {
        // Get our IP address in proper dot-quad format by breaking up the 32-bit unsigned host address and splitting it into an array of four 8-bit unsigned numbers...
        Uint8 * dotQuad = (Uint8*)&serverIP.host;
 
        //... and then outputting them cast to integers. Then read the last 16 bits of the serverIP object to get the port number
        cout << "Successfully resolved server host to IP: " << (unsigned short)dotQuad[0] << "." << (unsigned short)dotQuad[1] << "." << (unsigned short)dotQuad[2] << "." << (unsigned short)dotQuad[3];
        cout << " port " << SDLNet_Read16(&serverIP.port) << endl << endl;
    }
    // Try to open the server socket
    serverSocket = SDLNet_TCP_Open(&serverIP);
    if (!serverSocket)
    {
        cout << "Failed to open the server socket: " << SDLNet_GetError() << "\n";
        exit(-1);
    }
    else
    {
        cout << "Sucessfully created server socket." << endl;
    }
    // Add our server socket to the socket set
    SDLNet_TCP_AddSocket(socketSet, serverSocket);
    cout << "Awaiting clients..." << endl;
}


void Network::ConnectToServer() {
    // Ask the user for a server to connect to - can be entered as a hostname (i.e. localhost etc.) or an IP address (i.e. 127.0.0.1 etc.)
    cout << "Server Name: " << this->serverName << endl;
    //getline(cin, serverName); // Uncomment this and remove the below line to change the server we're connecting to...
   // serverName = "localhost";
 
    // Create the socket set with enough space to store our desired number of connections (i.e. sockets)
    socketSet = SDLNet_AllocSocketSet(1);
    if (socketSet == NULL)
    {
        cout << "Failed to allocate the socket set: " << SDLNet_GetError() << "\n";
        exit(-1); // Quit!
    }
    else
    {
        cout << "Successfully allocated socket set." << endl;
    }
 
    // Try to resolve the host. If successful, this places the connection details in the serverIP object
    int hostResolved = SDLNet_ResolveHost(&serverIP, serverName.c_str(), PORT);
 
    if (hostResolved == -1)
    {
        cout << "Failed to resolve the server hostname: " << SDLNet_GetError() << "\nContinuing...\n";
    }
    else // If we successfully resolved the host then output the details
    {
        // Get our IP address in proper dot-quad format by breaking up the 32-bit unsigned host address and splitting it into an array of four 8-bit unsigned numbers...
        Uint8 * dotQuad = (Uint8*)&serverIP.host;
 
        //... and then outputting them cast to integers. Then read the last 16 bits of the serverIP object to get the port number
        cout << "Successfully resolved host to IP: " << (unsigned short)dotQuad[0] << "." << (unsigned short)dotQuad[1] << "." << (unsigned short)dotQuad[2] << "." << (unsigned short)dotQuad[3];
        cout << " port " << SDLNet_Read16(&serverIP.port) << endl << endl;
    }
 
    // Try to resolve the IP of the server, just for kicks
    if ((host = SDLNet_ResolveIP(&serverIP)) == NULL)
    {
        cout << "Failed to resolve the server IP address: " << SDLNet_GetError() << endl;
    }
    else
    {
        cout << "Successfully resolved IP to host: " << host << endl;
    }
 
    // Flag to keep track of when to disconnect and finish up. We initially set it so that we CANNOT connect, and only change this to false when we got an "OK" response from the server
    bool shutdownClient = true;
 
    // Try to open a connection to the server and quit out if we can't connect
    clientSocket[0] = SDLNet_TCP_Open(&serverIP);
    if (!clientSocket[0])
    {
        cout << "Failed to open socket to server: " << SDLNet_GetError() << "\n";
        return;
    }
    else // If we successfully opened a connection then check for the server response to our connection
    {
        cout << "Connection okay, about to read connection status from the server..." << endl;
 
        // Add our socket to the socket set for polling
        SDLNet_TCP_AddSocket(socketSet, clientSocket[0]);
 
        // Wait for up to five seconds for a response from the server
        // Note: If we don't check the socket set and WAIT for the response, we'll be checking before the server can respond, and it'll look as if the server sent us nothing back
        int activeSockets = SDLNet_CheckSockets(socketSet, 1000);
 
        cout << "There are " << activeSockets << " socket(s) with data on them at the moment." << endl;
 
        // Check if we got a response from the server
        int gotServerResponse = SDLNet_SocketReady(clientSocket[0]);
 
        if (gotServerResponse != 0)
        {
            cout << "Got a response from the server... " << endl;
            int serverResponseByteCount = SDLNet_TCP_Recv(clientSocket[0], buffer, BUFFER_SIZE);
 
            cout << "Got the following from server: " << buffer << "(" << serverResponseByteCount << " bytes)" << endl;
 
            // We got an okay from the server, so we can join!
            if ( strcmp(buffer, "OK") == 0 )
            {
                // So set the flag to say we're not quitting out just yet
                shutdownClient = false;
 
                cout << "Joining server now..." << endl << endl;
            }
            else
            {
                cout << "Server is full... Terminating connection." << endl;
            }
        }
        else
        {
            cout << "No response from server..." << endl;
        }
    } // End of if we managed to open a connection to the server condition
}


void Network::ProcessClients() {
     // Check for activity on the entire socket set. The second parameter is the number of milliseconds to wait for.
    // For the wait-time, 0 means do not wait (high CPU!), -1 means wait for up to 49 days (no, really), and any other number is a number of milliseconds, i.e. 5000 means wait for 5 seconds
    int numActiveSockets = SDLNet_CheckSockets(socketSet, 0);

    if (numActiveSockets != 0)
    {
        cout << "There are currently " << numActiveSockets << " socket(s) with data to be processed." << endl;
    }

    // Check if our server socket has received any data
    // Note: SocketReady can only be called on a socket which is part of a set and that has CheckSockets called on it (the set, that is)
    // SDLNet_SocketRead returns non-zero for activity, and zero is returned for no activity. Which is a bit bass-ackwards IMHO, but there you go.
    int serverSocketActivity = SDLNet_SocketReady(serverSocket);

    // If there is activity on our server socket (i.e. a client has trasmitted data to us) then...
    if (serverSocketActivity != 0)
    {
        // If we have room for more clients...
        if (clientCount < MAX_CLIENTS)
        {

            // Find the first free socket in our array of client sockets
            int freeSpot = -99;
            for (int loop = 0; loop < MAX_CLIENTS; loop++)
            {
                if (socketIsFree[loop] == true)
                {
                    //cout << "Found a free spot at element: " << loop << endl;
                    socketIsFree[loop] = false; // Set the socket to be taken
                    freeSpot = loop;            // Keep the location to add our connection at that index in the array of client sockets
                    break;                      // Break out of the loop straight away
                }
            }

            // ...accept the client connection and then...
            clientSocket[freeSpot] = SDLNet_TCP_Accept(serverSocket);

            // ...add the new client socket to the socket set (i.e. the list of sockets we check for activity)
            SDLNet_TCP_AddSocket(socketSet, clientSocket[freeSpot]);

            // Increase our client count
            clientCount++;

            // Send a message to the client saying "OK" to indicate the incoming connection has been accepted
            strcpy( buffer, SERVER_NOT_FULL.c_str() );
            int msgLength = strlen(buffer) + 1;
            SDLNet_TCP_Send(clientSocket[freeSpot], (void *)buffer, msgLength);

            cout << "Client connected. There are now " << clientCount << " client(s) connected." << endl << endl;
        }
        else // If we don't have room for new clients...
        {
            cout << "*** Maximum client count reached - rejecting client connection ***" << endl;

            // Accept the client connection to clear it from the incoming connections list
            TCPsocket tempSock = SDLNet_TCP_Accept(serverSocket);

            // Send a message to the client saying "FULL" to tell the client to go away
            strcpy( buffer, SERVER_FULL.c_str() );
            int msgLength = strlen(buffer) + 1;
            SDLNet_TCP_Send(tempSock, (void *)buffer, msgLength);

            // Shutdown, disconnect, and close the socket to the client
            SDLNet_TCP_Close(tempSock);
        }

    } // End of if server socket is has activity check

    // Loop to check all possible client sockets for activity
    for (int clientNumber = 0; clientNumber < MAX_CLIENTS; clientNumber++)
    {
        // If the socket is ready (i.e. it has data we can read)... (SDLNet_SocketReady returns non-zero if there is activity on the socket, and zero if there is no activity)
        int clientSocketActivity = SDLNet_SocketReady(clientSocket[clientNumber]);

        //cout << "Just checked client number " << clientNumber << " and received activity status is: " << clientSocketActivity << endl;

        // If there is any activity on the client socket...
        if (clientSocketActivity != 0)
        {
            // Check if the client socket has transmitted any data by reading from the socket and placing it in the buffer character array
            receivedByteCount = SDLNet_TCP_Recv(clientSocket[clientNumber], buffer, BUFFER_SIZE);

            // If there's activity, but we didn't read anything from the client socket, then the client has disconnected...
            if (receivedByteCount <= 0)
            {
                //...so output a suitable message and then...
                cout << "Client " << clientNumber << " disconnected." << endl << endl;

                //... remove the socket from the socket set, then close and reset the socket ready for re-use and finally...
                SDLNet_TCP_DelSocket(socketSet, clientSocket[clientNumber]);
                SDLNet_TCP_Close(clientSocket[clientNumber]);
                clientSocket[clientNumber] = NULL;

                // ...free up their slot so it can be reused...
                socketIsFree[clientNumber] = true;

                // ...and decrement the count of connected clients.
                clientCount--;

                cout << "Server is now connected to: " << clientCount << " client(s)." << endl << endl;
            }
            else // If we read some data from the client socket...
            {
                // Output the message the server received to the screen
                cout << "Received: >>>> " << buffer << " from client number: " << clientNumber << endl;
                ProcessInputFromClient();

                // Send message to all other connected clients
                int originatingClient = clientNumber;

                for (int loop = 0; loop < MAX_CLIENTS; loop++)
                {
                    // Send a message to the client saying "OK" to indicate the incoming connection has been accepted
                    //strcpy( buffer, SERVER_NOT_FULL.c_str() );
                    int msgLength = strlen(buffer) + 1;

                    // If the message length is more than 1 (i.e. client pressed enter without entering any other text), then
                    // send the message to all connected clients except the client who originated the message in the first place
                    if (msgLength > 1 && loop != originatingClient && socketIsFree[loop] == false)
                    {
                        cout << "Retransmitting message: " << buffer << " (" << msgLength << " bytes) to client number: " << loop << endl;
                        SDLNet_TCP_Send(clientSocket[loop], (void *)buffer, msgLength);
                    }

                }

                // If the client told us to shut down the server, then set the flag to get us out of the main loop and shut down
                if ( strcmp(buffer, "shutdown") == 0 )
                {
                    shutdownServer = true;

                    cout << "Disconnecting all clients and shutting down the server..." << endl << endl;
                }

            }

        } // End of if client socket is active check

    } // End of server socket check sockets loop
 
}


void Network::ProcessInputFromClient() {
    ClientInput clientInput = *((ClientInput *)buffer);
    game->playerList[1]->clientInput = ((ClientInput *)buffer);
    std::cout << "Input recieved from client: " << std::endl;
    //clientInput.print();
}
void Network::SendMessageToClient(ServerMessage message) {
    if (clientSocket[0] == NULL)
        return;
    std::cout << "Message before sending to client: " << std::endl;
    //serverMessage.print();
    int numBytes = sizeof(ServerMessage);
    if (SDLNet_TCP_Send(clientSocket[0], (void *)&message, numBytes) < numBytes) {
        cout << "Failed to send message: " << SDLNet_GetError() << endl;
    }
}
void Network::SendMessageToClient(ScoreMessage message) {
    if (clientSocket[0] == NULL)
        return;
    std::cout << "Message before sending to client: " << std::endl;
    //serverMessage.print();
    int numBytes = sizeof(ScoreMessage);
    if (SDLNet_TCP_Send(clientSocket[0], (void *)&message, numBytes) < numBytes) {
        cout << "Failed to send message: " << SDLNet_GetError() << endl;
    }
}
void Network::SendInputToServer() {
    ClientInput clientInput;
    clientInput.isKeyDownW = Input::IsKeyDown(OIS::KC_W);
    clientInput.isKeyDownA = Input::IsKeyDown(OIS::KC_A);
    clientInput.isKeyDownS = Input::IsKeyDown(OIS::KC_S);
    clientInput.isKeyDownD = Input::IsKeyDown(OIS::KC_D);

    std::cout << "Input before sending to server: " << std::endl;
    //clientInput.print();

    int bytesToSend = sizeof(clientInput);
 
    // Send the message to the server
    if (SDLNet_TCP_Send(clientSocket[0], (void *)(&clientInput), bytesToSend) < bytesToSend) {
        cout << "Failed to send message: " << SDLNet_GetError() << endl;
    }
}
void Network::ProcessServer(){
    if (socketSet == NULL)
        return;
    int activeSockets = SDLNet_CheckSockets(socketSet, 0);
    // cout << "Sockets with data on them at the moment: " << activeSockets << endl;
    // Check if we got a response from the server
    if (activeSockets < 0)
        return;
    int messageFromServer = SDLNet_SocketReady(clientSocket[0]);
    while (messageFromServer > 0)
    {
        //cout << "Got a response from the server... " << endl;
        int serverResponseByteCount = SDLNet_TCP_Recv(clientSocket[0], buffer, BUFFER_SIZE);
        cout << "Received: " << serverResponseByteCount << endl;// "(" << serverResponseByteCount << " bytes)" << endl;
        int i = 0;
        while (i < serverResponseByteCount) {
            ServerMessageType messageType = *((ServerMessageType *)(buffer + i));
            //serverMessage.print();
            if (messageType == STARTGAME)
            {
                ServerMessage serverMessage = *((ServerMessage *)(buffer+i));
                cout << "Server is starting game" << endl;
                game->newGame();
                i += sizeof(ServerMessage);
            }
            else if (messageType == OBJECTPOSITION) {
                ServerMessage serverMessage = *((ServerMessage *)(buffer+i));
                cout << "GOT OBJECT POSITION" << endl;
                game->gameObjects[serverMessage.objectIndex]->physics->setWorldPosition(Ogre::Vector3(serverMessage.posx, serverMessage.posy, serverMessage.posz));
                i += sizeof(ServerMessage);
            }
            else if (messageType == SCORE) {
                ScoreMessage scoreMessage = *((ScoreMessage *)(buffer+i));
                cout << "GOT OBJECT POSITION" << endl;
                game->playerList[scoreMessage.playerNumber]->scored(scoreMessage.score);
                i += sizeof(ScoreMessage);
            }
        }
        messageFromServer = SDLNet_SocketReady(clientSocket[0]);
    }
    // End of if socket has activity check
}

void Network::OnNetworkUpdate() {
    if (isServer) {
        ProcessClients();
    }
    else {        
        ProcessServer();
        if (game->gameMode) {
            SendInputToServer();
        }
    }
}