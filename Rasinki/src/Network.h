#ifndef __NETWORK__H__
#define __NETWORK__H__
#include <iostream>
#include <cstdlib>
#include <string>
#include <string.h>
#include <iostream>
#include <SDL_net.h>

#define PORT 60000
#define BUFFER_SIZE 512
#define MAX_SOCKETS 2
#define MAX_CLIENTS 1 // Max_sockets - 1

using namespace std;

class Network {
	public:
		bool isServer;
		Network(bool isServer);
		~Network();
		void OnNetworkUpdate();
	private:
		void SetUpServer();
		void ConnectToServer();
		void SendInputToServer();
		// void SendData(...);
		// void ReadData(...);
		void CloseConnection();
		void ProcessClients();

		const char *host;
		string serverName;

		IPaddress serverIP;                  // The IP of the server (this will end up being 0.0.0.0 - which means roughly "any IP address")
	    TCPsocket serverSocket;              // The server socket that clients will use to connect to us
	    TCPsocket clientSocket[MAX_CLIENTS]; // An array of sockets for the clients, we don't include the server socket (it's specified separately in the line above)
	    bool      socketIsFree[MAX_CLIENTS]; // An array of flags to keep track of which client sockets are free (so we know whether we can use the socket for a new client connection or not)
	 	SDLNet_SocketSet socketSet;

	    char buffer[BUFFER_SIZE];            // Array of characters used to store the messages we receive
	    int receivedByteCount;           // A variable to keep track of how many bytes (i.e. characters) we need to read for any given incoming message i.e. the size of the incoming data
	 
	    int clientCount;                 // Count of how many clients are currently connected to the server
	 
	    bool shutdownServer;         // Flag to control when to shut down the server

};


struct ClientInput {
	bool isKeyDownW;
	bool isKeyDownA;
	bool isKeyDownS;
	bool isKeyDownD;
	bool isKeyDownUp;
	bool isKeyDownDown;
	bool isKeyDownLeft;
	bool isKeyDownRight;
	bool isKeyDownSpacebar;
	bool isKeyDownEscape;

	bool isKeyUpW;
	bool isKeyUpA;
	bool isKeyUpS;
	bool isKeyUpD;
	bool isKeyUpUp;
	bool isKeyUpDown;
	bool isKeyUpLeft;
	bool isKeyUpRight;
	bool isKeyUpSpacebar;
	bool isKeyUpEscape;
};

#endif