#include "Client.h"
#include <iostream>

Client::Client(AssetLoader &al) :assLoad(al), window(sf::RenderWindow(sf::VideoMode(760,760), "Cardbox")),tools(ToolMenu(al,sf::Vector2u(760,760)))
{
	window.setFramerateLimit(60);
	std::srand(time(NULL));
	
	menuOn = false;

	windowRect = sf::FloatRect(-1.f,-1.f,window.getSize().x+2.f, window.getSize().y+2.f);

	currentPhase = CONNECTIONS;
	
	deltaTime_time = deltaClock.restart();
	cardPicked = false;
	drawMode = false;
	makingArea = false;

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
	TCPsocket.connect(serverIP,serverPort);
	packet<<id;
	TCPsocket.send(packet);
	TCPsocket.setBlocking(false);

	std::cout<<"Connected to server; ip: "<<serverIP<<" & port: "<<serverPort<<std::endl;

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
				
		sf::Int16 r,g,b;
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
		
		if(assLoad.check(fileName))
		{
		packet.clear();
		packetID = DECLINE_REQUEST;
		packet<<packetID;
		TCPsocket.send(packet);

		makeDeck(fileName,cardAmount,sf::Vector2f(cardSizeX,cardSizeY));
		}
		else
		{
		packet.clear();
		packetID = ACCEPT_REQUEST;
		packet<<packetID;
		TCPsocket.send(packet);
		TCPsocket.setBlocking(true);

		receiveImageFile(fileName,cardAmount,cardSizeX,cardSizeY);
		}
		/*packet>>filename;
		dView->addQuestion(-1 ,"SERVER", ("upload "+filename) );*/
		break;
	case ACCEPT_REQUEST:
		std::cout<<"Got server acceptance"<<std::endl;
		TCPsocket.setBlocking(true);
		sendImageFile(fileName);
		break;
	case DECLINE_REQUEST:
		std::cout<<"Server says no"<<std::endl;
		break;
	case UPLOAD:
		break;
	}
}

void Client::gamePhase()
{
	if(!menuOn)
	{	
		shapes[ownIndex].setPosition(posX,posY);
		sendMouse();
	}

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

	if(pickers.size()>0)
	{
		for(int i = 0; i < pickers.size();i++)
		{
			moveCard(pickers[i],pickings[i]);
			checkHandAreas(pickings[i]);
		}
	}
}

void Client::sendMouse()
{
	if(_sendTimer.getElapsedTime().asMilliseconds()>20)
	{

	packet.clear();

	packetID = MOVE_SHIT;

	packet<<packetID<<ownIndex<<posX<<posY;

	TCPsocket.send(packet);

	_sendTimer.restart();

	}
}

void Client::receiveTCP()
{
	packet.clear();

	packetID = EMPTY;

	TCPsocket.receive(packet);

	packet>>packetID;

	sf::Int16 playerID,cardID,x,y;

	sf::FloatRect tempFR;

	switch(packetID)
	{
	case MOVE_SHIT:
			
		sf::Int16 tempX, tempY;
		packet>>playerID>>tempX>>tempY;

		//std::cout<<"Received moves: "<<playerNames[playerIndex]<<". X: "<<tempX<<" Y: "<<tempY<<std::endl;

		if(playerID > ownIndex)
			playerID--;

		otherPlayersMousePos[playerID] = sf::Vector2f(tempX,tempY);

		break;
	case AREA:
		float aX,aY,w,h;
		packet>>playerID>>aX>>aY>>w>>h;

		std::cout<<"AREA: x: "<<aX<<" y: "<<aY<<" W: "<<w<<" H: "<<h;
		std::cout<<" from "<<playerNames[playerID]<<std::endl;

		tempFR = sf::FloatRect(aX,aY,w,h);
		makeHandArea(playerID,tempFR);
		break;
	case SHUFFLE:
		//FUNKTIO TÄLLE PLZ, eri dekeille vois omat ja kaikkeee
		sf::Int16 seed;
		packet>>seed;
		std::srand(seed);
		std::random_shuffle(cards.begin(), cards.end());
		cardPicked = false;
		pickers.clear();
		pickings.clear();
		for(int i = 0; i < cards.size(); i++)
		{
			cards[i]._sprite.setPosition(0,0);
			cards[i]._sprite.setRotation(0);
			cards[i].backSideUp();
		}
		break;
	case PICK_UP_CARD:
		//saaattaa räjähtää mutta ei kuitenkaan räjähä
		packet>>playerID>>cardID>>x>>y;
		std::cout <<"player "<<playerNames[playerID]<<" picked "<<cardID<<" from X: "<<x<<" Y: "<<y<<std::endl;
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
		std::cout <<"player "<<playerNames[playerID]<<" dropped that shit to X: "<<x<<" Y: "<<y<<std::endl;
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
		std::cout <<"player "<<playerNames[playerID]<<" turned "<<cardID<<std::endl;
		putCardOnTop(cardID);
		cards[0].swapTexture();
		break;
	case ROTATE_CARD:
		packet>>playerID>>cardID>>x>>y;
		std::cout <<"player "<<playerNames[playerID]<<" rotated "<<cardID<<std::endl;
		putCardOnTop(cardID);
		rotateCard(cardID);
		if(playerID > ownIndex)
			playerID--;
		otherPlayersMouseDist[playerID] = sf::Vector2f(x,y);
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

void Client::checkGameInput(sf::Event Event)
{
	switch(Event.type)
	{
		case sf::Event::KeyPressed:
			if(Event.key.code == sf::Keyboard::R)
			{
				packet.clear();
				packetID = SHUFFLE;
				packet<<packetID;
				TCPsocket.send(packet);
			}
		
			if(Event.key.code == sf::Keyboard::Space)
			{
				sf::Int16 cardID = checkClick(sf::Mouse::getPosition(window)), distanceX, distanceY;

				if(cardID != 1337)
				{
					rotateCard(cardID);
				
					distance = sf::Vector2f(posX,posY)-cards[0]._sprite.getPosition();
					distanceX = distance.x;
					distanceY = distance.y;

					packet.clear();
					packetID = ROTATE_CARD;
					packet<<packetID<<cardID<<distanceX<<distanceY;
					TCPsocket.send(packet);
				}
			}
			break;

		case sf::Event::MouseWheelMoved:
			if(!menuOn)
				zoomzoom(Event.mouseWheel.delta);
			break;

		case sf::Event::MouseButtonPressed:

		if(clickTimer.getElapsedTime().asMilliseconds()>100)
		{
				
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)  && !cardPicked && !menuOn)
		{
			sf::Int16 distanceX,distanceY,cardID = checkClick(sf::Mouse::getPosition(window));

			if(cardID != 1337)
			{
			std::cout<<"I picks card";
			cardPicked = true;
			checkCardOwnage(cardID);
			pickers.push_back(ownIndex);
			pickings.push_back(cardID);
			distance = sf::Vector2f(posX,posY)-cards[0]._sprite.getPosition();
			packet.clear();
			packetID = PICK_UP_CARD;

			std::cout<<"PosX: "<<posX<<" PosY: "<<posY<<" SpriteX: "<<cards[0]._sprite.getPosition().x<<" SpriteY: "<<cards[0]._sprite.getPosition().y<<std::endl;
			distanceX = distance.x;
			distanceY = distance.y;
			std::cout<<" from X: "<<distanceX<<" Y: "<<distanceY<<std::endl;
			packet<<packetID<<cardID<<distanceX<<distanceY;
			TCPsocket.send(packet);
			}
		}

			if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && !menuOn)
			{
				sf::Int16 cardID = checkClick(sf::Mouse::getPosition(window));

				if(cardID != 1337)
				{
					if(!cards[0].getHanded())
					{
						cards[0].swapTexture();
				
						packet.clear();
						packetID = TURN_CARD;
						packet<<packetID<<cardID;
						TCPsocket.send(packet);
					}
				}
			}
			clickTimer.restart();
				
			}
		

		break;

		case sf::Event::MouseButtonReleased:
		
		if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			dropCard();
		}

		break;
		}
}

void Client::checkDownloadInput(sf::Event Event)
{
	switch(Event.type)
	{
	case sf::Event::KeyPressed:

		if(Event.key.code == sf::Keyboard::Space)
		{
			packet.clear();
			packetID = CONTINUE;
			packet<<packetID;
			TCPsocket.send(packet);
			std::cout<<"Sending continue"<<std::endl;
		}

		if(Event.key.code == sf::Keyboard::Num1)
			{
				std::cout<<"Sending upload request"<<std::endl;
				fileName = "vesa.png";
				cardAmount = 10;
				cardSizeX = 170;
				cardSizeY = 340;

				if(!assLoad.check(fileName))
				{
					assLoad.newImage(fileName);
					std::cout<<"Added new image to ass"<<std::endl;
				}
				makeDeck(fileName,cardAmount,sf::Vector2f(cardSizeX,cardSizeY));

				packet.clear();
				packetID = REQUEST_UPLOAD;
				packet<<packetID<<fileName<<cardAmount<<cardSizeX<<cardSizeY;
				TCPsocket.send(packet);
			}
			if(Event.key.code == sf::Keyboard::Num2)
			{
				std::cout<<"Sending upload request"<<std::endl;
				cardAmount = 10;
				cardSizeX = 170;
				cardSizeY = 340;
				fileName = "karjalainen.png";

				if(!assLoad.check(fileName))
				{
					assLoad.newImage(fileName);
					std::cout<<"Added new image to ass"<<std::endl;
				}
				makeDeck(fileName,cardAmount,sf::Vector2f(cardSizeX,cardSizeY));

				packet.clear();
				packetID = REQUEST_UPLOAD;
				packet<<packetID<<fileName<<cardAmount<<cardSizeX<<cardSizeY;
				TCPsocket.send(packet);
			}
			if(Event.key.code == sf::Keyboard::Num3)
			{
				std::cout<<"Sending upload request"<<std::endl;
				cardAmount = 57;
				cardSizeX = 256;
				cardSizeY = 256;
				fileName = "Jigsaw.png";

				if(!assLoad.check(fileName))
				{
					assLoad.newImage(fileName);
					std::cout<<"Added new image to ass"<<std::endl;
				}
				makeDeck(fileName,cardAmount,sf::Vector2f(cardSizeX,cardSizeY));

				packet.clear();
				packetID = REQUEST_UPLOAD;
				packet<<packetID<<fileName<<cardAmount<<cardSizeX<<cardSizeY;
				TCPsocket.send(packet);
			}
			break;
	}
}

void Client::checkConnectionInput(sf::Event Event)
{
	switch(Event.type)
	{
	case sf::Event::KeyPressed:
		if(Event.key.code == sf::Keyboard::Space)
		{
			packet.clear();
			packetID = CONTINUE;
			packet<<packetID;
			TCPsocket.send(packet);
			std::cout<<"Sending continue"<<std::endl;
		}
		break;
	}
}

void Client::checkInput()
{
	sf::Event Event;


	while(window.pollEvent(Event))
	{
		
		posX = sf::Mouse::getPosition(window).x;
		posY = sf::Mouse::getPosition(window).y;
		
		switch(currentPhase)
		{

		case GAME:
			if(!drawMode)
				checkGameInput(Event);
			else
				areaTool(Event);
				//joku funktio

			break;
		case DOWNLOADS:
			checkDownloadInput(Event);
			break;
		case CONNECTIONS:
			checkConnectionInput(Event);
			break;
		}

		switch(Event.type)
		{

		case sf::Event::Closed:
			window.close();
			std::exit(0);
			break;
		case sf::Event::KeyPressed:
			if(Event.key.code == sf::Keyboard::Escape)
				toolMenu();
			break;
		case sf::Event::MouseButtonPressed:
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && menuOn)
			{
				buttonStuff();
			}
			break;
		}
	}
}

void Client::buttonStuff()
{
	sf::Vector2i mouse = sf::Mouse::getPosition(window);
	mouse.x+=window.getSize().x*0.333f;
	int pushTheButton = tools.checkButtons(mouse);

	switch(pushTheButton)
	{
	case -1:
		break;
	case 0:
		if(currentPhase == GAME)
		{
			drawMode = !drawMode;
			toolMenu();
		}
		break;
	case 1:
		window.close();
		std::exit(0);
		break;
	}
}

void Client::areaTool(sf::Event Event)
{	
	
	switch(Event.type)
	{

	case sf::Event::MouseButtonPressed:
		
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !makingArea)
		{
			std::cout<<tempRect.getPosition().x<<" "<<tempRect.getPosition().y<<std::endl;
			makingArea = true;
			tempRect.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
		}
		
	break;

	case sf::Event::MouseButtonReleased:

		if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) && makingArea)
		{
			makingArea = false;
			makeHandArea(ownIndex,tempRect.getGlobalBounds());

			packet.clear();
			packetID = AREA;
			float x = tempRect.getGlobalBounds().left;
			float y = tempRect.getGlobalBounds().top;
			float w = tempRect.getGlobalBounds().width;
			float h = tempRect.getGlobalBounds().height;
			packet<<packetID<<x<<y<<w<<h;
			TCPsocket.send(packet);

			tempRect.setSize(sf::Vector2f(0,0));
			drawMode = false;
		}
		
		break;
	}

	if(makingArea)
		{
			
			tempRect.setSize(sf::Vector2f(sf::Mouse::getPosition(window))-tempRect.getPosition());
			std::cout<<"Size X: "<<tempRect.getSize().x<<"Size Y: "<<tempRect.getSize().y<<std::endl;
			if(tempRect.getSize().x>300)
				tempRect.setSize(sf::Vector2f(300,tempRect.getSize().y));
			if(tempRect.getSize().y>200)
				tempRect.setSize(sf::Vector2f(tempRect.getSize().x,200));
			if(tempRect.getSize().x<-300)
				tempRect.setSize(sf::Vector2f(-300,tempRect.getSize().y));
			if(tempRect.getSize().y<-200)
				tempRect.setSize(sf::Vector2f(tempRect.getSize().x,-200));
		}
}

void Client::makeHandArea(int playerIndex, sf::FloatRect floatRect)
{
	sf::RectangleShape rect;
	rect.setPosition(floatRect.left,floatRect.top);
	rect.setSize(sf::Vector2f(floatRect.width,floatRect.height));
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(playerColors[playerIndex]);
	rect.setOutlineThickness(2.0f);

	for(int i = 0; i < handAreas.size();i++)
	{
		if(handAreas[i].getOutlineColor()==playerColors[playerIndex])
			{
				handAreas.erase(handAreas.begin()+i);
				break;
			}
	}
	handAreas.push_back(rect);
}

void Client::checkHandAreas(int cardID)
{
	for(int i = 0; i < cards.size(); i++)
	{
		if(cardID == cards[i].getID())
		{
			sf::FloatRect floatRect = cards[i]._sprite.getGlobalBounds();

			std::vector<sf::Vector2f> corners;
			corners.push_back(sf::Vector2f(floatRect.left,floatRect.top));
			corners.push_back(sf::Vector2f(floatRect.left+floatRect.width, floatRect.top));
			corners.push_back(sf::Vector2f(floatRect.left, floatRect.top+floatRect.height));
			corners.push_back(sf::Vector2f(floatRect.left+floatRect.width, floatRect.top+floatRect.height));

			bool inArea;

			for(int j = 0; j < handAreas.size(); j++)
			{
				inArea = true;
				for(int k = 0; k < corners.size(); k++)
				{
					if(!handAreas[j].getGlobalBounds().contains(corners[i]))
					{
						inArea = false;
						break;
					}
				}
				if(inArea)
				{
					if(handAreas[j].getOutlineColor() == playerColors[ownIndex])
						cards[i].inHand(true);
					else
						cards[i].inHand(false);

					break;
				}
				else
					cards[i].remember();
			}

			break;
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

sf::Int16 Client::checkClick(sf::Vector2i mousepos)
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
			//cardPicked = true;
			//pickedCard = cards[0].getID();
			return cards[0].getID();
		}
	}

	sf::Int16 nothing = 1337;
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

void Client::dropCard()
{
	if(cardPicked)
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
	sf::Int16 x,y;
	x = cards[0]._sprite.getPosition().x;
	y = cards[0]._sprite.getPosition().y;
	
	packet<<packetID<<x<<y;
	TCPsocket.send(packet);

	}
}

void Client::moveCard(sf::Int16 playerID,sf::Int16 cardID)
{
	for(int i = 0; i < cards.size(); i++)
	{
		if(cardID == cards[i].getID())
		{
			CardObject tempCard = cards[i];
			tempCard._sprite.setRotation(cards[i]._sprite.getRotation());

			if(playerID != ownIndex)
			{
				if(playerID > ownIndex)
					tempCard._sprite.setPosition(shapes[playerID].getPosition()-otherPlayersMouseDist[playerID-1]);
				else
					tempCard._sprite.setPosition(shapes[playerID].getPosition()-otherPlayersMouseDist[playerID]);
			}

			else
			{
				tempCard._sprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(window))-distance);
			}
		
			if(checkBoundaries(tempCard._sprite.getGlobalBounds()))
				cards[i]._sprite.setPosition(tempCard._sprite.getPosition());

			break;
		}
	}

}

bool Client::checkBoundaries(sf::FloatRect floatRect)
{
	std::vector<sf::Vector2f> corners;
	corners.push_back(sf::Vector2f(floatRect.left,floatRect.top));
	corners.push_back(sf::Vector2f(floatRect.left+floatRect.width, floatRect.top));
	corners.push_back(sf::Vector2f(floatRect.left, floatRect.top+floatRect.height));
	corners.push_back(sf::Vector2f(floatRect.left+floatRect.width, floatRect.top+floatRect.height));
	
	for(int i = 0; i < corners.size();i++)
	{
		if(!windowRect.contains(corners[i]))
			return false;
	}
	return true;

}

void Client::sendImageFile(std::string filename)
{
	int packetCounter = 0;
	std::fstream inputFile(filename, std::ios::binary|std::ios::in);

	if(inputFile)
	{
		char buffer[61440];
		std::string sendString;
		bool done = false;
		int i;

		packetID = UPLOAD;

		while(!done)
		{
			packet.clear();
			packet<<packetID;

			i = 0;

			while(i < 61440 && inputFile.peek() != EOF)
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
	packet.clear();
	packetID = UPLOAD_DONE;
	packet<<packetID;
	TCPsocket.send(packet);
	TCPsocket.setBlocking(false);
}

void Client::receiveImageFile(std::string filename,sf::Int16 amount,sf::Int16 x,sf::Int16 y)
{
	sf::Clock uploadTime;
	int packetCounter = 0;

	std::fstream *outputFile = new std::fstream;

	*outputFile = std::fstream(filename, std::ios::binary|std::ios::out);

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
			if(!assLoad.check(filename))
			{
				assLoad.newImage(filename);
				std::cout<<"Added new image to ass"<<std::endl;
			}
			makeDeck(filename,cardAmount,sf::Vector2f(cardSizeX,cardSizeY));
			break;
		}
	}
}

void Client::writeImageFile(std::string filename, std::string data, std::fstream* output)
{
	if(*output)
	{
		char buffer[61440];

		int dataStringSize = data.size();

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
	texture = assLoad.getTexture(filename);

	if(texture != NULL)
	{
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
	else
		std::cout<<"Texture is so fucking NULL"<<std::endl;
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

void Client::rotateCard(int cardID)
{
	for(int i = 0; i < cards.size(); i++)
	{
		if(cards[i].getID() == cardID)
		{
			sf::Vector2f diipadaapa;
			int rotation = cards[i]._sprite.getRotation();
			switch(rotation)
			{
			case 0:
				diipadaapa = sf::Vector2f(cards[i]._sprite.getGlobalBounds().height*0.75f,cards[i]._sprite.getGlobalBounds().width*0.5f);
				break;
			case 90:
				diipadaapa = sf::Vector2f(-cards[i]._sprite.getGlobalBounds().height*0.5f,cards[i]._sprite.getGlobalBounds().width*0.75f);
				break;
			case 180:
				diipadaapa = sf::Vector2f(-cards[i]._sprite.getGlobalBounds().height*0.75f,-cards[i]._sprite.getGlobalBounds().width*0.5f);
				break;
			case 270:
				diipadaapa = sf::Vector2f(cards[i]._sprite.getGlobalBounds().height*0.5f,-cards[i]._sprite.getGlobalBounds().width*0.75f);
				break;
			}
			cards[i]._sprite.rotate(90);
			cards[i]._sprite.move(diipadaapa);
			break;
		}
	}
}

void Client::toolMenu()
{
	if(window.getView().getCenter()==window.getDefaultView().getCenter())
	{		
		sf::View view(window.getView());
		view.move(window.getSize().x*0.333f,0);
		window.setView(view);
		window.setMouseCursorVisible(true);
		if(shapes.size()>0)
			shapes[ownIndex].setFillColor(sf::Color::Transparent);
		dropCard();
		menuOn = true;
	}
	else
	{	
		if(shapes.size()>0)
		{
			shapes[ownIndex].setFillColor(playerColors[ownIndex]);
			sf::Mouse::setPosition(sf::Vector2i(shapes[ownIndex].getPosition()), window);
		}
		window.setView(window.getDefaultView());
		window.setMouseCursorVisible(false);
		menuOn = false;
	}

}

void Client::draw()
{
	window.clear(sf::Color(50,135,50,255));

	for(int i = 0; i < handAreas.size();i++)
	{
		window.draw(handAreas[i]);
		//std::cout<<handAreas.size()<<std::endl;
	}

	for(int i = cards.size()-1; i >= 0;i--)
	{
		cards[i].draw(window);
	}
	for(int i = 0; i < shapes.size(); i++)
	{
		window.draw(shapes[i]);
	}
	
	tools.draw(window);
	
	if(makingArea)
		window.draw(tempRect);

	window.display();
}

Client::~Client(void)
{

}