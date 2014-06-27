#include "Server.h"
#include "Platform.h"

int main()
{
	int players = 2;
	Server server;
	Platform platform(server);

	platform.setUp(players,5);
	bool win=false;
	int cardCounter = 1;
	while (!win)
	{
		int lastPlayerIndex = platform.getCurrentPlayerIndex();
		
		
		CardPacket receivedCards = platform.processTurn();
		if(platform.getPlayer(lastPlayerIndex).getHand().hand.size() == 0)
			{
				server.send(platform.getPlayer(lastPlayerIndex).getID() +" voitti");
				win = true;
			}
		server.send(receivedCards);
		if(receivedCards._cards.hand.size() == 0)
		{
			cardCounter++;
			if (players != 1)
			{
				if (cardCounter == players)
				{
					Hand tempH;
					server.sendReplacement(CardPacket(players,tempH));
					cardCounter = 1;

					// tai käske clienttiä tyhjentämään pöytä
				}
			}
			else
			{
				Hand tempH;
				server.sendReplacement(CardPacket(players,tempH));
				cardCounter = 1;
				// tai käske clienttiä tyhjentämään pöytä
			}
				
		}
		else
			cardCounter = 1;

		if(!server.checkConnection())
		{
			platform.reset();
			platform.setUp(players,5);
			cardCounter = 1;
			win = false;
		}
	
	}
	return 0;
}