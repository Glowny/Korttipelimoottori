#include "Client.h"
#include <iostream>

Client::Client(void) : window(sf::RenderWindow(sf::VideoMode(760,760), "Cardbox"))
{
	window.setFramerateLimit(60);
	UDPreceive.bind(sf::Socket::AnyPort);
	std::srand(time(NULL));

	lastScaled = -1;
	currentPhase = CONNECTIONS;

	deltaTime_time = deltaClock.restart();
	cardPicked = false;

	//dView = new DialogueView();
}

void Client::scaleCardsNormal()
{
	for(int i = 0; i < cards.size();i++)
	{
		if(cards[i]._sprite.getScale()!=sf::Vector2f(0.3f,0.3f) && !cards[i]._sprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			cards[i]._sprite.setScale(0.3f,0.3f);
	}
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
	TCPsocket.connect(serverIP,serverPort);
	sf::Uint16 udpReceivePort = UDPreceive.getLocalPort();
	packet<<id<<udpReceivePort;
	TCPsocket.send(packet);
	TCPsocket.setBlocking(false);
	UDPreceive.setBlocking(false);
	UDPsend.setBlocking(false);

	std::cout<<"Connected to server; ip: "<<serverIP<<" & port: "<<serverPort<<" Sent UDPport: "<<udpReceivePort<<std::endl;

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
		TCPsocket.setBlocking(true);

		receiveImageFile(fileName,cardAmount,cardSizeX,cardSizeY);
		/*packet>>filename;
		dView->addQuestion(-1 ,"SERVER", ("upload "+filename) );*/
		break;
	case ACCEPT_REQUEST:
		std::cout<<"Got server acceptance"<<std::endl;
		TCPsocket.setBlocking(true);
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

	//if(scaleTimer.getElapsedTime().asSeconds()>6.0)
	//	{
	//		scaleCardsNormal();
	//		scaleTimer.restart();
	//	}

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

	if(pickers.size()>0)
	{
		for(int i = 0; i < pickers.size();i++)
		{
			moveCard(pickers[i],pickings[i]);
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

	sf::Uint16 playerID,cardID,x,y;

	switch(packetID)
	{
	case SHUFFLE:
		//FUNKTIO TÄLLE PLZ, eri dekeille vois omat ja kaikkeee
		sf::Uint16 seed;
		packet>>seed;
		std::srand(seed);
		std::random_shuffle(cards.begin(), cards.end());
		cardPicked = false;
		pickers.clear();
		pickings.clear();
		for(int i = 0; i < cards.size(); i++)
		{
			cards[i]._sprite.setPosition(0,0);
		}
		break;
	case PICK_UP_CARD:
		//saaattaa räjähtää mutta ei kuitenkaan räjähä
		packet>>playerID>>cardID>>x>>y;
		std::cout <<"player "<<playerID<<"picked "<<cardID<<" from X: "<<x<<"Y: "<<y<<std::endl;
		checkCardOwnage(cardID);
		pickers.push_back(playerID);
		pickings.push_back(cardID);
		putCardOnTop(cardID);
		if(playerID > ownIndex)
			playerID--;
		otherPlayersMouseDist[playerID] = sf::Vector2f(x,y);
		break;
	case RELEASE_CARD:
		packet>>playerID>>x>>y;
		std::cout <<"player "<<playerID<<" dropped that shit to X: "<<x<<" Y: "<<y<<std::endl;
		for(int i = 0; i < pickers.size(); i++)
		{
			if(pickers[i] == playerID)
			{
				for(int j = 0; j < cards.size(); j++)
				{
					if(cards[j].getID() == pickings[i])
					{
						cards[j]._sprite.setPosition(sf::Vector2f(x,y));
						break;
					}
				}

				pickers.erase(pickers.begin()+i);
				pickings.erase(pickings.begin()+i);
				break;
			}

		}
		break;
	case TURN_CARD:
		packet>>playerID>>cardID;
		std::cout <<"player "<<playerID<<"turned "<<cardID<<std::endl;
		putCardOnTop(cardID);
		cards[0].swapTexture();
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

		case sf::Event::MouseWheelMoved:
			//checkRoll(sf::Mouse::getPosition(window),Event.mouseWheel.delta);
			zoomzoom(Event.mouseWheel.delta);
			break;

		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			if(Event.key.code == sf::Keyboard::Escape)
				window.close();
			if(Event.key.code == sf::Keyboard::R && currentPhase == GAME)
			{
				packet.clear();
				packetID = SHUFFLE;
				packet<<packetID;
				TCPsocket.send(packet);
			}
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
			if(Event.key.code == sf::Keyboard::Num3 && currentPhase == DOWNLOADS)
			{
				std::cout<<"Sending upload request"<<std::endl;
				cardAmount = 57;
				cardSizeX = 256;
				cardSizeY = 256;
				fileName = "Jigsaw";
				packet.clear();
				packetID = REQUEST_UPLOAD;
				packet<<packetID<<fileName<<cardAmount<<cardSizeX<<cardSizeY;
				TCPsocket.send(packet);
			}
			break;
			
		case sf::Event::MouseButtonPressed:
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				sf::Uint16 distanceX,distanceY,cardID = checkClick(sf::Mouse::getPosition(window));

				if(cardID != 1337)
				{
				std::cout<<"I picks card"<<std::endl;
				pickers.push_back(ownIndex);
				pickings.push_back(cardID);
				distance = sf::Vector2f(posX,posY)-cards[0]._sprite.getPosition();
				packet.clear();
				packetID = PICK_UP_CARD;

				distanceX = distance.x;
				distanceY = distance.y;
				packet<<packetID<<cardID<<distanceX<<distanceY;
				TCPsocket.send(packet);
				}
			}
			if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				sf::Uint16 cardID = checkClick(sf::Mouse::getPosition(window));

				if(cardID != 1337)
				{
					cards[0].swapTexture();
				
					packet.clear();
					packetID = TURN_CARD;
					packet<<packetID<<cardID;
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
					{
					std::cout<<"I drops card"<<std::endl;
					pickers.erase(pickers.begin()+i);
					pickings.erase(pickings.begin()+i);
					break;
					}
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
}

void Client::zoomzoom(int delta)
{
	sf::Vector2f viewSize = sf::Vector2f(0.f,0.f);

	if(delta>0)
	{
		if(window.getView().getSize().x == window.getSize().x)
		{
			viewSize = sf::Vector2f(window.getSize().x*0.75f,window.getSize().y*0.75f);
			window.setView(sf::View(sf::Vector2f(posX,posY),viewSize));
			
		}
		else if(window.getView().getSize().x == window.getSize().x*0.75f)
		{
			viewSize = sf::Vector2f(window.getSize().x*0.5f,window.getSize().y*0.5f);
			window.setView(sf::View(sf::Vector2f(posX,posY),viewSize));
		}
	}

	if(delta<0)
	{
		if(window.getView().getSize().x == window.getSize().x*0.75f)
		{
			viewSize = sf::Vector2f(window.getSize().x*1.0f,window.getSize().y*1.0f);
			window.setView(sf::View(sf::Vector2f(window.getSize().x*0.5f,window.getSize().y*0.5f),viewSize));
		}
		else if(window.getView().getSize().x == window.getSize().x*0.5f)
		{
			viewSize = sf::Vector2f(window.getSize().x*0.75f,window.getSize().y*0.75f);
			window.setView(sf::View(sf::Vector2f(window.getSize().x*0.5f,window.getSize().y*0.5f),viewSize));
		}
	}
	if(viewSize != sf::Vector2f(0.f,0.f))
		correctView(viewSize);
}

void Client::correctView(sf::Vector2f viewSize)
{
	int viewLeft = posX - window.getView().getSize().x*0.5f;
	int viewRight = posX + window.getView().getSize().x*0.5f;
	int viewTop = posY - window.getView().getSize().y*0.5f;
	int viewBot = posY + window.getView().getSize().y*0.5f;
	int offsetX=0,offsetY=0;

	if(viewLeft<0)
	{
		offsetX = -viewLeft;
	}
				
	if(viewRight>window.getSize().x)
	{
		offsetX = viewRight-window.getSize().x;
		offsetX*=-1;
	}

	if(viewTop<0)
	{
		offsetY = -viewTop;
	}
				
	if(viewBot>window.getSize().y)
	{
		offsetY = viewBot-window.getSize().y;
		offsetY*=-1;
	}

	window.setView(sf::View(sf::Vector2f(posX+offsetX,posY+offsetY),viewSize));
}

sf::Uint16 Client::checkClick(sf::Vector2i mousepos)
{

	sf::Vector2f mouse(mousepos);

	for(int i = 0; i < cards.size();i++)
	{
		if(cards[i]._sprite.getGlobalBounds().contains(mouse))
		{
			//sf::Sprite sprite;
			////sprite.setTexture();

			//sf::Vector2f distance;

			//distance = sf::Vector2f(cards[i]._sprite.getTextureRect().left,cards[i]._sprite.getTextureRect().top)-cards[i]._sprite.getPosition();
			//std::cout<<"X: "<<distance.x<<"Y :"<<distance.y<<std::endl;

			//sf::IntRect mouseRect(mouse.x,mouse.y,1,1);

			//mouseRect.left+=distance.x;
			//mouseRect.top+=distance.y;
			//std::cout<<"mouseX: "<<mouseRect.left<<"mouseY: "<<mouseRect.top<<std::endl;

			//sprite.setTextureRect(mouseRect);

			//int r = sprite.getColor().r;
			//int g = sprite.getColor().g;
			//int b = sprite.getColor().b;
			//int a = sprite.getColor().a;
		

			//std::cout<<"r"<<r<<"g"<<g<<"b"<<b<<"a"<<a<<std::endl;


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

void Client::checkRoll(sf::Vector2i mousepos,int delta)
{
	sf::Vector2f mouse(mousepos);
	bool scaled = true;

	for(int i = 0; i < cards.size();i++)
	{
		if(cards[i]._sprite.getGlobalBounds().contains(mouse))
		{

			if(delta<0)
			{
				if(cards[i]._sprite.getScale() == sf::Vector2f(0.3f,0.3f))
					cards[i]._sprite.setScale(0.4f,0.4f);
				else if(cards[i]._sprite.getScale() == sf::Vector2f(0.4f,0.4f))
					cards[i]._sprite.setScale(0.5f,0.5f);
				else
					scaled = false;
			}

			if(delta>0)
				{

					if(cards[i]._sprite.getScale() == sf::Vector2f(0.4f,0.4f))
						cards[i]._sprite.setScale(0.3f,0.3f);
					else if(cards[i]._sprite.getScale() == sf::Vector2f(0.5f,0.5f))
						cards[i]._sprite.setScale(0.4f,0.4f);
					else
						scaled = false;
				}

			if(scaled)
				putCardOnTop(cards[i].getID());


			break;
		}	
		
	}

}

void Client::moveCard(sf::Uint16 playerID,sf::Uint16 cardID)
{
	for(int i = 0; i < cards.size(); i++)
	{
		if(cardID == cards[i].getID())
		{
			
			if(playerID != ownIndex)
			{
				if(playerID > ownIndex)
					cards[i]._sprite.setPosition(shapes[playerID].getPosition()-otherPlayersMouseDist[playerID-1]);
				else
					cards[i]._sprite.setPosition(shapes[playerID].getPosition()-otherPlayersMouseDist[playerID]);
			}

			else
			{
				//std::cout<<distance.x<<distance.y<<std::endl;
				cards[i]._sprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(window))-distance);
			}

			if(cards[i]._sprite.getPosition().x<0)
			{
				cards[i]._sprite.setPosition(0,cards[i]._sprite.getPosition().y);
			}

			if(cards[i]._sprite.getPosition().x+cards[i]._sprite.getGlobalBounds().width>window.getSize().x)
			{
				cards[i]._sprite.setPosition(window.getSize().x-cards[i]._sprite.getGlobalBounds().width,cards[i]._sprite.getPosition().y);
			}

			if(cards[i]._sprite.getPosition().y<0)
			{
				cards[i]._sprite.setPosition(cards[i]._sprite.getPosition().x,0);
			}

			if(cards[i]._sprite.getPosition().y+cards[i]._sprite.getGlobalBounds().height>window.getSize().y)
			{
				cards[i]._sprite.setPosition(cards[i]._sprite.getPosition().x,window.getSize().y-cards[i]._sprite.getGlobalBounds().height);
			}
		}
	}

}

void Client::sendImageFile(std::string filename)
{
	int packetCounter = 0;
	std::fstream inputFile(filename+".png", std::ios::binary|std::ios::in);

	if(inputFile)
	{
		char buffer[1024];
		std::string sendString;
		bool done = false;
		int i;

		packetID = UPLOAD;

		while(!done)
		{
			packet.clear();
			packet<<packetID;

			i = 0;

			while(i < 1024 && inputFile.peek() != EOF)
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
			packetCounter++;
			packet<<sendString;
			TCPsocket.send(packet);
			sendString.clear();
		}
		inputFile.close();
	}
	std::cout<<"Done sending stuff"<<std::endl;
	std::cout<<"Number of packets sent: "<<packetCounter<<std::endl;
	makeDeck(filename,cardAmount,sf::Vector2f(cardSizeX,cardSizeY));
	packet.clear();
	packetID = UPLOAD_DONE;
	packet<<packetID;
	TCPsocket.send(packet);
	TCPsocket.setBlocking(false);
}

void Client::receiveImageFile(std::string filename,sf::Uint16 amount,sf::Uint16 x,sf::Uint16 y)
{
	sf::Clock uploadTime;
	int packetCounter = 0;

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
			packetCounter++;
			packet>>data;
			writeImageFile(filename,data,outputFile);
			break;
		case UPLOAD_DONE:
			std::cout<<"Server says upload done, I believe"<<std::endl;
			std::cout<<"Time: "<<uploadTime.getElapsedTime().asSeconds()<<std::endl;
			std::cout<<"Number of packets received: "<<packetCounter<<std::endl;
			done = true;
			outputFile->close();
			TCPsocket.setBlocking(false);
			makeDeck(filename,cardAmount,sf::Vector2f(cardSizeX,cardSizeY));
			break;
		}
	}
}

void Client::writeImageFile(std::string filename, std::string data, std::fstream* output)
{
	if(*output)
	{
		char buffer[1024];

		sf::Uint16 dataStringSize = data.size();

		std::cout<<"Data string size: "<<dataStringSize<<std::endl;

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
		cards[i].setBackRect(backRect);
		cards[i].swapTexture();
		cards[i]._sprite.setScale(0.3f,0.3f);
	}

}

void Client::putCardOnTop(int cardID)
{
	for(int i = 0; i < cards.size(); i++)
	{
		if(cards[i].getID() == cardID)
		{
			CardObject temp = cards[i];
			cards.erase(cards.begin()+i);
			cards.insert(cards.begin(),temp);
			break;
		}
	}
}

void Client::checkCardOwnage(int cardID)
{ 
	//Tää on hyvä kommentti, joka selkeyttää asioita. Rakkaudella Vesalle
	for(int i = 0; i < pickings.size(); i++)
	{
		if(pickings[i] == cardID)
		{
			pickings.erase(pickings.begin()+i);
			pickers.erase(pickers.begin()+i);
			cardPicked = false;
			break;
		}
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