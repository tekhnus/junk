#include "client/Client.hpp"

int main()
{
	junk::Client client;
	client.connectToServer("localhost", 7777);
	while (true)
	{

	}
	return 0;
}
