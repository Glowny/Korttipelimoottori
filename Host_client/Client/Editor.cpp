#include "Editor.h"


Editor::Editor():_window(sf::RenderWindow(sf::VideoMode(800,600,32), "Editor"))
{
	_window.setActive(false);
	_window.setVisible(false);
	_font = new sf::Font;
	_font->loadFromFile("comic.ttf");
	_dropDowns.push_back(DropDown(_window,"asd",*_font,sf::Vector2f(100,50),sf::Vector2f(0,0)));
	_dropDowns[0].pushOption("derp");
	_dropDowns[0].pushOption("herp");
	_dropDowns[0].pushOption("durr");
	_dropDowns[0].pushOption("hurr");

}

void Editor::checkMouseClick(sf::Vector2i mousepos)
{
	for(int i = 0; i < _dropDowns.size();i++)
	{
		if(_dropDowns[i].isActive())
		{
			for(int j = 0; j < _dropDowns[i].size();j++)
				{
					if(_dropDowns[i].getBounds(j).contains(sf::Vector2f(mousepos)))
					{
						_dropDowns[i].makeSelection(j);
						_dropDowns[i].setPassive();
					}
				}
		}
	}
}

void Editor::checkMouseHover(sf::Vector2i mousepos)
{
	for(int i = 0; i < _dropDowns.size();i++)
	{

		if(_dropDowns[i].getBounds().contains(sf::Vector2f(mousepos)))
		{
				_dropDowns[i].setActive();
		}

		if(_dropDowns[i].isActive())
		{
			bool outOfOption = true;
			for(int j = 0; j < _dropDowns[i].size();j++)
				{
					if(_dropDowns[i].getBounds(j).contains(sf::Vector2f(mousepos)))
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
	while(_window.pollEvent(Event))
	{
		checkMouseHover(sf::Mouse::getPosition(_window));

		switch(Event.type)
		{
			
		case sf::Event::Closed:
			_window.close();
			case sf::Event::MouseButtonPressed:

			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					checkMouseClick(sf::Mouse::getPosition(_window));
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
		_dropDowns[i].draw();
	}
	
	_window.display();
	_window.clear();
}

Editor::~Editor(void)
{
}
