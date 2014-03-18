#include "Network.h"
#define UDP_PORT 57351

Network::Network(bool isServer){
	if ( SDLNet_Init() < 0 ) {
		fprintf(stderr, "Couldn't initialize net: %s\n”, SDLNet_GetError()");
		SDL_Quit();
		exit(1);
	}
	this->isServer = isServer;
	if (isServer)
		HostServer();
	else
		ConnectToServer();
}
void Network::HostServer() {
	IPaddress ipaddress;
	SDLNet_ResolveHost(&ipaddress, NULL, UPD_PORT);
	std::cout << "SERVER IPADDRESS: " << ipaddress.host << std::endl;
}