#ifndef __NETWORK__H__
#define __NETWORK__H__
#include "SDL_net.h"

class Network {
	public:
		bool isServer;
		Network();
	private:
		void HostServer();
		void ConnectToServer(...);
		void SendData(...);
		void ReadData(...);
		void CloseConnection();

};

#endif