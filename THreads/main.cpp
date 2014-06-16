#include <iostream>
#include "drawThread.h"
int main()
{
	std::vector<sf::FloatRect> objectVector;


	sf::FloatRect dsa(10,10,50,50);
	sf::FloatRect dssa(10,200,50,50);
	std::vector<sf::Vector2i> stateVector;
	objectVector.push_back(dsa);
	objectVector.push_back(dssa);
	objectVector.push_back(dsa);

	drawThread drawStuff(&objectVector, stateVector);
	sf::Thread thread (&drawThread::draw,&drawStuff);
	
	thread.launch();

	while(1)
	{
		std::cin >> objectVector[0].left;
		std::cout << objectVector[0].left;
	}

}
