#include "Editor.h"


Editor::Editor():_window(sf::RenderWindow(sf::VideoMode(800,600,32), "Editor"))
{
	_window.setActive(false);
	_window.setVisible(false);
	_window.setFramerateLimit(60);
	_font = new sf::Font;
	_font->loadFromFile("comic.ttf");
	sf::Vector2f buttonSize(30,25);
	plusButton.setSize(buttonSize);
	_viewOffset.x = 0;
	_viewOffset.y = 0;

	_minus = new sf::Text;
	_plus = new sf::Text;
	_minus->setString("minus");
	_plus->setString("plus");
	_minus->setFont(*_font);
	_plus->setFont(*_font);
	plusButton.setText(_plus);

	plusButton.setPosition(sf::Vector2f(200,200));

}

void Editor::newRule()
{
	DropDown d = DropDown(_window,"Select Rule",*_font,sf::Vector2f(100,50),sf::Vector2f(0,0));
	_dropDowns.push_back(d);
	
	int index = _dropDowns.size()-1;
	_dropDowns[index].pushOption("ValueComparison");
	_dropDowns[index].pushOption("AmountComparison");
	_dropDowns[index].pushOption("ExceptionalRule");

	ButtonObject b;
	_minuses.push_back(b);
	_minuses[_minuses.size()-1].setSize(sf::Vector2f(30,25));
	_minuses[_minuses.size()-1].setText(_minus);

	arrangeDropDowns();
}

void Editor::scrollDown(int amount)
{
	sf::Vector2f movement(0,amount);
	_viewOffset+=movement;

	_window.setView(sf::View(_window.getView().getCenter()+movement,sf::Vector2f(_window.getSize())));

}

void Editor::scrollUp(int amount)
{
	sf::Vector2f movement(0,-amount);
	_viewOffset+=movement;

	_window.setView(sf::View(_window.getView().getCenter()+movement,sf::Vector2f(_window.getSize())));

}


void Editor::arrangeDropDowns()
{	
	for(int i = 0; i < _dropDowns.size();i++)
	{

	_dropDowns[i].setPosition(sf::Vector2f(0,i*_dropDowns[i].getBounds().height*2));

	float x = _dropDowns[i].getBounds().left+_dropDowns[i].getBounds().width;
	float y = _dropDowns[i].getBounds().top+_dropDowns[i].getBounds().height*0.5f;
	sf::Vector2f buttonpos = sf::Vector2f(x,y);

	_minuses[i].setPosition(buttonpos);
		
	}

	
	std::cout<< _dropDowns.size();

}

void Editor::checkMouseClick(sf::Vector2i mousepos)
{

	sf::Vector2f mouserealpos = sf::Vector2f(mousepos)+_viewOffset;


	std::cout<<mouserealpos.x<<" "<<mouserealpos.y<<std::endl;

	for(int i = 0; i < _dropDowns.size();i++)
	{
		if(_dropDowns[i].isActive())
		{
			for(int j = 0; j < _dropDowns[i].size();j++)
				{
					if(_dropDowns[i].getBounds(j).contains(sf::Vector2f(mouserealpos)))
					{
						_dropDowns[i].makeSelection(j);
						_dropDowns[i].setPassive();
					}
				}
		}
	}

	if(plusButton.getArea().contains(sf::Vector2f(mouserealpos)))
	{
		newRule();
	}
	for(int i = 0; i < _minuses.size();)
	{
		if(_minuses[i].getArea().contains(mouserealpos))
		{
			std::cout<<"erased Dropdowntop"<<_dropDowns[i].getBounds().top<<"index:"<<i<<std::endl;
			_dropDowns.erase(_dropDowns.begin()+i);

			std::cout<<"erased minuses top"<<_minuses[i].getArea().top<<"index"<<i<<std::endl;
			_minuses.erase(_minuses.begin()+i);
		}
		else
		i++;

	//arrangeDropDowns();
	
		
	}


	
}

sf::Vector2f Editor::getViewOffset()
{
	//std::cout<<_viewOffset.x<<" "<<_viewOffset.y<<std::endl;
	return _viewOffset;
	
}


void Editor::checkMouseHover(sf::Vector2i mousepos)
{
	sf::Vector2f mouserealpos = sf::Vector2f(mousepos)+_viewOffset;



	if(_window.getSize().y-mousepos.y < 40 && _window.getSize().y-mousepos.y > 0)
		scrollDown(3);
	if(mousepos.y<40 && mousepos.y > 0)
		if(mouserealpos.y>20)
		scrollUp(3);


	for(int i = 0; i < _dropDowns.size();i++)
	{
	
			if(_dropDowns[i].getBounds().contains(sf::Vector2f(mouserealpos)))
			{
				if(i>0)
				{
				  if(!_dropDowns[i-1].isActive())
					_dropDowns[i].setActive();
				}
				else
					_dropDowns[i].setActive();
			}
		

		if(_dropDowns[i].isActive())
		{
			bool outOfOption = true;
			for(int j = 0; j < _dropDowns[i].size();j++)
				{
					if(_dropDowns[i].getBounds(j).contains(sf::Vector2f(mouserealpos)))
					{
						outOfOption = false;
						_dropDowns[i].makeBlue(j,true);
					}
					else
						_dropDowns[i].makeBlue(j,false);
				}
			if(outOfOption)
				_dropDowns[i].setPassive();
		}
	}
}


void Editor::run()
{
	sf::Event Event;
	while(true)
	{
		

		checkMouseHover(sf::Mouse::getPosition(_window));

		while(_window.pollEvent(Event))
		{
		
			switch(Event.type)
			{
			
			case sf::Event::Closed:
				_window.close();
				case sf::Event::MouseButtonPressed:
				
					if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						checkMouseClick(sf::Mouse::getPosition(_window));
					}

				case sf::Event::KeyPressed:

					if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					{
						scrollDown(20);
					}

						if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					{
						scrollUp(20);
					}
			}
		}


			draw();
		}
	}



void Editor::initialize()
{
	_window.setActive(true);
	_window.setVisible(true);
}

void Editor::draw()
{
	for(int i = 0; i < _dropDowns.size();i++)
	{
		if(!_dropDowns[i].isActive())
		_dropDowns[i].draw();
	}

	for(int i = 0; i < _minuses.size();i++)
	{
		_minuses[i].draw(_window);
	}

	plusButton.draw(_window);

	for(int i = 0; i < _dropDowns.size();i++)
	{
		if(_dropDowns[i].isActive())
		_dropDowns[i].draw();
	}
	


	_window.display();
	_window.clear(sf::Color(0,100,0,255));
}

Editor::~Editor(void)
{
}
