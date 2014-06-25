#include "Server.h"
#include "Platform.h"

int main()
{
	int players = 2;
	Server server;
	Platform platform(server);

	platform.setUp(players);
	bool win=0;
	int cardCounter = 1;
	while (!win)
	{
		Player lastPlayer = platform.getCurrentPlayer();
		
		if(lastPlayer.getHand().hand.size() == 0)
			{
				server.send(lastPlayer.getID() +" voitti");
				win = true;
			}
		CardPacket receivedCards = platform.processTurn();
		server.send(receivedCards);
		if(receivedCards._cards.hand.size() == 0)
		{
			cardCounter++;
			if (players != 1)
			{
				if (cardCounter == players)
				{
					Card tempC(14,1);
					Hand tempH;
					tempH.hand.push_back(tempC);
					server.send(CardPacket(0,tempH));
					cardCounter = 1;

					// tai käske clienttiä tyhjentämään pöytä
				}
			}
			else
			{
				Card tempC(14,1);
				Hand tempH;
				tempH.hand.push_back(tempC);
				server.send(CardPacket(0,tempH));
				cardCounter = 1;
				// tai käske clienttiä tyhjentämään pöytä
			}
				
		}
	
	}
	return 0;
}