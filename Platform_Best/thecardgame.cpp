#include "Server.h"
#include "Platform.h"

int main()
{
	Server server;
	Platform platform;

	server.send(2, "lol");

	return 0;
}