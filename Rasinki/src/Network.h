#ifndef __NETWORK__H__
#define __NETWORK__H__
#include <iostream>
#include <cstdlib>
#include <string>
#include <string.h>
#include <Game.h>
#include <iostream>
#include <SDL_net.h>
#include <Input.h>

#define PORT 60000
#define BUFFER_SIZE 512
#define MAX_SOCKETS 2
#define MAX_CLIENTS 1 // Max_sockets - 1

using namespace std;
enum ServerMessageType { STARTGAME, OBJECTPOSITION, SCORE, DISABLEOBJECT, DISABLESPHERE};
class Game;

struct ServerMessage {
	enum ServerMessageType messageType;
	int objectIndex;
	float posx, posy, posz;
	ServerMessage(int i, Ogre::Vector3 pos) : messageType(OBJECTPOSITION), objectIndex(i), posx(pos.x), posy(pos.y), posz(pos.z) {}
	ServerMessage(ServerMessageType t, int i) : messageType(t), objectIndex(i) {}
	ServerMessage() : messageType(STARTGAME) {}
	void print() {
		std::cout << "messageType " << messageType << std::endl;
		std::cout << "posx " << posx << std::endl;
		std::cout << "posy " << posy << std::endl;
		std::cout << "posz " << posz << std::endl;
	}
};
struct ScoreMessage {
	enum ServerMessageType messageType;
	int playerNumber;
	int score;
	ScoreMessage(int pNum, int s): messageType(SCORE), playerNumber(pNum), score(s){}
	void print() {
		std::cout << "messageType " << messageType << std::endl;
		std::cout << "playerNumber " << playerNumber << std::endl;
		std::cout << "score " << score << std::endl;
	}
};

class Network {
	public:
		bool isServer;
		Network(Game* g, bool isServer);
		~Network();
		void Start();
		void OnNetworkUpdate();
		void SendMessageToClient(ServerMessage message);
		void SendMessageToClient(ScoreMessage message);
		string serverName;

	private:
		void SetUpServer();
		void ConnectToServer();
		void CloseConnection();
		void ProcessClients();
		void ProcessServer();
		void ProcessInputFromClient();
		void SendInputToServer();

		Game *game;
		const char *host;

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

	ClientInput() :
		isKeyDownW(false),
		isKeyDownA(false),
		isKeyDownS(false),
		isKeyDownD(false),
		isKeyDownUp(false),
		isKeyDownDown(false),
		isKeyDownLeft(false),
		isKeyDownRight(false),
		isKeyDownSpacebar(false),
		isKeyDownEscape(false),

		isKeyUpW(false),
		isKeyUpA(false),
		isKeyUpS(false),
		isKeyUpD(false),
		isKeyUpUp(false),
		isKeyUpDown(false),
		isKeyUpLeft(false),
		isKeyUpRight(false),
		isKeyUpSpacebar(false),
		isKeyUpEscape(false) 
	{};

	void print() {

		std::cout << "isKeyDownW? " << isKeyDownW << std::endl;
		std::cout << "isKeyDownA? " << isKeyDownA << std::endl;
		std::cout << "isKeyDownS? " << isKeyDownS << std::endl;
		std::cout << "isKeyDownD? " << isKeyDownD << std::endl;
		std::cout << "isKeyDownUp? " << isKeyDownUp<< std::endl;
		std::cout << "isKeyDownDown? " << isKeyDownDown << std::endl;
		std::cout << "isKeyDownLeft? " << isKeyDownLeft << std::endl;
		std::cout << "isKeyDownRight? " << isKeyDownRight << std::endl;
		std::cout << "isKeyDownSpacebar? " << isKeyDownSpacebar << std::endl;
		std::cout << "isKeyDownEscape? " << isKeyDownEscape << std::endl;
		std::cout << "isKeyUpW? " << isKeyUpW << std::endl;
		std::cout << "isKeyUpA? " << isKeyUpA << std::endl;
		std::cout << "isKeyUpS? " << isKeyUpS << std::endl;
		std::cout << "isKeyUpD? " << isKeyUpD << std::endl;
		std::cout << "isKeyUpUp? " << isKeyUpUp << std::endl;
		std::cout << "isKeyUpDown? " << isKeyUpDown << std::endl;
		std::cout << "isKeyUpLeft? " << isKeyUpLeft << std::endl;
		std::cout << "isKeyUpRight? " << isKeyUpRight << std::endl;
		std::cout << "isKeyUpSpacebar? " << isKeyUpSpacebar << std::endl;
		std::cout << "isKeyUpEscape? " << isKeyUpEscape << std::endl;

	}
};

#endif
