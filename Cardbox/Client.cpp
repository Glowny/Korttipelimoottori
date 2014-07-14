#include "Client.h"
#include <iostream>

Client::Client(void) : window(sf::RenderWindow(sf::VideoMode(1280,760), "Cardbox"))
{
	window.setFramerateLimit(60);
	UDPreceive.bind(sf::Socket::AnyPort);
	std::srand(time(NULL));

	currentPhase = CONNECTIONS;

	deltaTime_time = deltaClock.restart();
	cardPicked = false;

	//dView = new DialogueView();
}

void Client::run()
{
	while(true)
	{
		deltaTime_time = deltaClock.restart();
		deltaTime = deltaTime_time.asMilliseconds();

		checkInput();

		switch(currentPhase)
		{
		case CONNECTIONS:
			connectionPhase();
			break;
		case DOWNLOADS:
			dialoguePhase();
			break;
		case GAME:
			gamePhase();
			break;
		}
		
		draw();
	}
}

void Client::connect(sf::IpAddress ip, int port, std::string id)
{
	ownName = id;
	serverIP = ip;
	serverPort = port;
	TCPsocket.connect(serverIP,port);
	sf::Uint16 udpReceivePort = UDPreceive.getLocalPort();
	packet<<id<<udpReceivePort;
	TCPsocket.send(packet);
	TCPsocket.setBlocking(false);
	UDPreceive.setBlocking(false);
	UDPsend.setBlocking(false);

	window.setTitle(ownName);
}

void Client::connectionPhase()
{
	packet.clear();

	packetID = EMPTY;

	TCPsocket.receive(packet);

	packet>>packetID;

	switch(packetID)
	{
		case EMPTY:
			break;
		case CONTINUE:
			currentPhase = DOWNLOADS;
			std::cout<<"Client going to downloadsPhase"<<std::endl;
			break;
		case START:
			handleStartPacket();
			break;
	}
}

void Client::handleStartPacket()
{
	packet>>ownIndex>>playerCount;

	for(int i = 0; i <playerCount;i++)
	{
		std::string name;
		packet>>name;
				
		sf::Uint16 r,g,b;
		packet>>r>>g>>b;

		playerNames.push_back(name);
		playerColors.push_back(sf::Color(r,g,b));
	}

	initPlayers();
}

void Client::dialoguePhase()
{
	//dView->draw(window);

	packet.clear();

	packetID = EMPTY;

	TCPsocket.receive(packet);

	packet>>packetID;

	/*std::string filename;
	int state = -1;*/

	switch(packetID)
	{
	case EMPTY:

		/*state = dView->checkQuestion(-1, sf::Vector2i(posX,posY));
		switch(state)
		{
		case -1:
			break;
		case 0:
			packet.clear();
			packetID = DECLINE_REQUEST;
			TCPsocket.send(packet);
			break;
		case 1:
			packet.clear();
			packetID = ACCEPT_REQUEST;
			TCPsocket.send(packet);
			break;
		}*/

		break;
	case CONTINUE:

		currentPhase = GAME;
		std::cout<<"Client going to gamePhase"<<std::endl;
		window.setMouseCursorVisible(false);
		//delete dView;
		break;
	case REQUEST_UPLOAD:
		packet>>fileName>>cardAmount>>cardSizeX>>cardSizeY;
		std::cout<<"Server sends request to upload "<<fileName<<"Amount: "<<cardAmount<<" X:"<<cardSizeX<<" Y:"<<cardSizeY<<std::endl;
	
		packet.clear();
		packetID = ACCEPT_REQUEST;
		packet<<packetID;
		TCPsocket.send(packet);

		receiveImageFile(fileName,cardAmount,cardSizeX,cardSizeY);
		/*packet>>filename;
		dView->addQuestion(-1 ,"SERVER", ("upload "+filename) );*/
		break;
	case ACCEPT_REQUEST:
		std::cout<<"Got server acceptance"<<std::endl;
		sendImageFile(fileName);
		break;
	case DECLINE_REQUEST:
		break;
	case UPLOAD:
		break;
	}
}

void Client::gamePhase()
{
	shapes[ownIndex].setPosition(posX, posY);

	sendUDP();
	receiveUDP();
	receiveTCP();

	for(int i = 0; i < shapes.size(); i++)
	{
		if(i != ownIndex)
		{
			if(i>ownIndex)
				smootheMouse(i, shapes[i].getPosition() ,otherPlayersMousePos[i-1]);
			else
				smootheMouse(i, shapes[i].getPosition() ,otherPlayersMousePos[i]);
		}
	}
}

void Client::sendUDP()
{
	if(_sendTimer.getElapsedTime().asMilliseconds()>5)
	{

	packet.clear();

	packetID = MOVE_SHIT;

	packet<<packetID<<ownIndex<<posX<<posY;

	UDPsend.send(packet,serverIP,serverPort);

	_sendTimer.restart();

	}
}

void Client::receiveTCP()
{
	packet.clear();

	packetID = EMPTY;

	TCPsocket.receive(packet);

	packet>>packetID;

	switch(packetID)
	{

	case PICK_UP_CARD:
		//saaattaa räjähtää mutta ei kuitenkaan räjähä
		sf::Uint16 playerID,cardID,x,y;
		packet>>playerID>>cardID>>x>>y;
		std::cout <<"player "<<playerID<<"picked "<<cardID<<"from X: "<<x<<"Y: "<<y<<std::endl;
		if(playerID > ownIndex)
			playerID--;
		otherPlayersMouseDist[playerID] = sf::Vector2f(x,y);
		pickers.push_back(playerID);
		break;
		case EMPTY:
			break;
	}
}

void Client::smootheMouse(int index, sf::Vector2f oldpos,sf::Vector2f newpos)
{
	sf::Vector2f homovector = newpos-oldpos;

	if(homovector.x != 0 && homovector.y != 0)
	{
		shapes[index].move(homovector*deltaTime*0.005f);
	}

}

void Client::receiveUDP()
{
	packet.clear();

	packetID = EMPTY;

	unsigned short tempPort = UDPreceive.getLocalPort();
	sf::IpAddress tempIP = serverIP;
	UDPreceive.receive(packet, tempIP, tempPort);
	
	packet>>packetID;

	switch(packetID)
	{
		case EMPTY:
			break;
		case MOVE_SHIT:
			
			sf::Uint16 playerIndex, tempX, tempY;
			packet>>playerIndex>>tempX>>tempY;

			//std::cout<<"Client received: "<<playerIndex<<". X: "<<tempX<<" Y: "<<tempY<<std::endl;

			if(playerIndex > ownIndex)
				playerIndex--;

			otherPlayersMousePos[playerIndex] = sf::Vector2f(tempX,tempY);

			break;
	}
}

void Client::initPlayers()
{
		for(int i = 0; i < playerCount; i++)
		{
			if(i != ownIndex)
			{
			otherPlayersMousePos.push_back(sf::Vector2f());
			otherPlayersMouseDist.push_back(sf::Vector2f());
			}
			shapes.push_back(sf::RectangleShape(sf::Vector2f(10,10)));
			shapes[i].setFillColor(playerColors[i]);
		}
}

void Client::checkInput()
{
	sf::Event Event;

	
	while(window.pollEvent(Event))
	{
		
		posX = sf::Mouse::getPosition(window).x;
		posY = sf::Mouse::getPosition(window).y;

		switch(Event.type)
		{

		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			if(Event.key.code == sf::Keyboard::Escape)
				window.close();
			if(Event.key.code == sf::Keyboard::Space && currentPhase != GAME)
			{
				packet.clear();
				packetID = CONTINUE;
				packet<<packetID;
				TCPsocket.send(packet);
				std::cout<<"Sending continue"<<std::endl;
			}
			if(Event.key.code == sf::Keyboard::Num1 && currentPhase == DOWNLOADS)
			{
				std::cout<<"Sending upload request"<<std::endl;
				fileName = "vesa";
				cardAmount = 10;
				cardSizeX = 170;
				cardSizeY = 340;
				packet.clear();
				packetID = REQUEST_UPLOAD;
				packet<<packetID<<fileName<<cardAmount<<cardSizeX<<cardSizeY;
				TCPsocket.send(packet);
			}
			if(Event.key.code == sf::Keyboard::Num2 && currentPhase == DOWNLOADS)
			{
				std::cout<<"Sending upload request"<<std::endl;
				cardAmount = 10;
				cardSizeX = 170;
				cardSizeY = 340;
				fileName = "karjalainen";
				packet.clear();
				packetID = REQUEST_UPLOAD;
				packet<<packetID<<fileName<<cardAmount<<cardSizeX<<cardSizeY;
				TCPsocket.send(packet);
			}
			break;
			
		case sf::Event::MouseButtonPressed:
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Uint16 distanceX,distanceY,cardID = checkClick(sf::Mouse::getPosition(window));
				std::cout <<cardID<<std::endl;

				if(cardID != 1337)
				{
				pickers.push_back(ownIndex);
				distance = sf::Vector2f(posX,posY)-cards[0]._sprite.getPosition();
				std::cout<<"Mouse click X: "<<sf::Mouse::getPosition(window).x<<" Y: "<<sf::Mouse::getPosition(window).y<<std::endl;
				packet.clear();
				packetID = PICK_UP_CARD;

				distanceX = distance.x;
				distanceY = distance.y;
				packet<<packetID<<cardID<<distanceX<<distanceY;
				TCPsocket.send(packet);
				}
			}
			break;
		}
			
		if(cardPicked)
		{
		

			if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				for(int i = 0; i < pickers.size();i++)
				{
					if(pickers[i] == ownIndex)
					pickers.erase(pickers.begin()+i);
				}

				cardPicked = false;
				packet.clear();
				packetID = RELEASE_CARD;
				sf::Uint16 x,y;
				x = cards[0]._sprite.getPosition().x;
				y = cards[0]._sprite.getPosition().y;
				packet<<packetID<<x<<y;
				TCPsocket.send(packet);
			}
		}
		
	}
	
	if(pickers.size()>0)
		for(int i = 0; i < pickers.size();i++)
		{
			moveCard(pickers[i],pickedCard);
		}

}

sf::Uint16 Client::checkClick(sf::Vector2i mousepos)
{

	sf::Vector2f mouse(mousepos);

	for(int i = 0; i < cards.size();i++)
	{
		if(cards[i]._sprite.getGlobalBounds().contains(mouse))
		{
			CardObject temp = cards[i];
			cards.erase(cards.begin()+i);
			cards.insert(cards.begin(),temp);
			cardPicked = true;
			pickedCard = cards[0].getID();
			return cards[0].getID();
		}
	}

	sf::Uint16 nothing = 1337;
	return nothing;
	
}

void Client::checkHover(sf::Vector2i mousepos)
{
	
}


void Client::moveCard(sf::Uint16 playerID,sf::Uint16 cardID)
{
	for(int i = 0; i < cards.size(); i++)
	{
		if(cardID == cards[i].getID())
		{
			
			if(playerID != ownIndex)
			{
				cards[i]._sprite.setPosition(otherPlayersMousePos[playerID]-otherPlayersMouseDist[playerID]);
			}

			else
			{
				std::cout<<distance.x<<distance.y<<std::endl;
				cards[i]._sprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(window))-distance);
			}
		}
	}

}
void Client::sendImageFile(std::string filename)
{
	std::fstream inputFile(filename+".png", std::ios::binary|std::ios::in);

	if(inputFile)
	{
		char buffer[16384];
		std::string sendString;
		bool done = false;
		int i;

		packetID = UPLOAD;

		while(!done)
		{
			packet.clear();
			packet<<packetID;

			i = 0;

			while(i < 16384 && inputFile.peek() != EOF)
			{
				inputFile.read(&buffer[i], 1);

				i++;

				if(inputFile.peek() == EOF)
					done = true;
			}

			for(int j = 0; j < i; j++)
			{
				sendString.push_back(buffer[j]);
			}
			std::cout<<"Sending buffer"<<std::endl;
			packet<<sendString;
			TCPsocket.send(packet);
			sendString.clear();
		}
		inputFile.close();
	}
	std::cout<<"Done sending stuff"<<std::endl;
	makeDeck(filename,cardAmount,sf::Vector2f(cardSizeX,cardSizeY));
	packet.clear();
	packetID = UPLOAD_DONE;
	packet<<packetID;
	TCPsocket.send(packet);
}

void Client::receiveImageFile(std::string filename,sf::Uint16 amount,sf::Uint16 x,sf::Uint16 y)
{
	sf::Clock uploadTime;

	std::fstream *outputFile = new std::fstream;

	*outputFile = std::fstream(filename+".png", std::ios::binary|std::ios::out);

	bool done = false;
	while(!done)
	{
		packet.clear();
		packetID = EMPTY;

		std::string data;
		
		TCPsocket.receive(packet);

		packet>>packetID;

		switch(packetID)
		{
		case UPLOAD:
			std::cout<<"Received upload packet"<<std::endl;
			packet>>data;
			writeImageFile(filename,data,outputFile);
			break;
		case UPLOAD_DONE:
			std::cout<<"Server says upload done, I believe"<<std::endl;
			std::cout<<uploadTime.getElapsedTime().asSeconds()<<std::endl;
			done = true;
			outputFile->close();
			makeDeck(filename,cardAmount,sf::Vector2f(cardSizeX,cardSizeY));
			break;
		}
	}
}

void Client::writeImageFile(std::string filename, std::string data, std::fstream* output)
{
	if(*output)
	{
		char buffer[16384];

		sf::Uint16 dataStringSize = data.size();

		for(int i = 0; i < dataStringSize; i++)
		{
			buffer[i] = data[i];
		}

		for(int i = 0; i < dataStringSize; i++)
		{
			output->write(&buffer[i], 1);
		}
	}
}

void Client::makeDeck(std::string filename, int cardAmount,sf::Vector2f cardSize)
{
	int size = cards.size();

	sf::Texture *texture = new sf::Texture;
	texture->loadFromFile(filename+".png");

	float cardSizeY = cardSize.y;
	float cardSizeX = cardSize.x;

	sf::Vector2f textureSize = sf::Vector2f(texture->getSize());

	int timesx = textureSize.x/cardSizeX;
	int timesy = textureSize.y/cardSizeY;
	bool brake = false;

	for(int y = 0; y < timesy;y++)
	{

	for(int x = 0; x < timesx;x++)
		{
			cards.push_back(CardObject(texture,sf::IntRect(x*cardSizeX,cardSizeY*y,cardSizeX,cardSizeY)));
			if(cards.size() == cardAmount+size)
			{
				brake = true;
				break;
			}
			//cardObjects[cardObjects.size()-1]._sprite.setPosition((sf::Vector2f(x*cardSizeX,cardSizeY*y)));

		}
	if(brake)
		break;

	}

	sf::IntRect backRect = cards[0]._sprite.getTextureRect();
	cards.erase(cards.begin()+size);
	std::cout<<"cards.size():"<<cards.size()<<std::endl;

	for(int i = size; i < cards.size();i++)
	{
		cards[i].setID(i);
		cards[i].changeTexture(backRect);
	}

}

void Client::draw()
{
	window.clear(sf::Color(50,135,50,255));


	for(int i = cards.size()-1; i >= 0;i--)
	{
		cards[i].draw(window);
	}
	for(int i = 0; i < shapes.size(); i++)
	{
		window.draw(shapes[i]);
	}
	window.display();
}

Client::~Client(void)
{
}