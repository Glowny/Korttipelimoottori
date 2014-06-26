#include "DropDown.h"


DropDown::DropDown(sf::RenderWindow &window,std::string name,sf::Font &font, sf::Vector2f size, sf::Vector2f position) : _window(window),_font(font)
{
	float thickness = 2;
	_active = false;
	_shapes.push_back(sf::RectangleShape(size));
	_shapes[0].setOutlineThickness(thickness);
	_shapes[0].setOutlineColor(sf::Color::Red);
	_shapes[0].setOrigin(position.x-thickness,position.y-thickness);
	_shapes[0].setSize(size);
	_shapes[0].setPosition(position);
	
	
	
	_texts.push_back(sf::Text(name,font,size.y));
	_texts[0].setPosition(position);
	_texts[0].setColor(sf::Color::Black);

	arrange(_texts[0],_shapes[0]);
}

void DropDown::arrange(sf::Text &text,sf::RectangleShape &shape)
{
	float ratiox = shape.getGlobalBounds().width/text.getGlobalBounds().width;
	float ratioy = (shape.getGlobalBounds().height/text.getGlobalBounds().height);
	ratioy*=0.5f;
	text.scale(ratiox,ratioy);
}

void DropDown::makeSelection(int index)
{
	_texts[0].setString(_texts[index].getString());
	arrange(_texts[0],_shapes[0]);
}

void DropDown::makeBlue(int index, bool hover)
{
	if(hover)
	{
	_shapes[index].setFillColor(sf::Color(215,235,255,255));
	}
	else
	{
	_shapes[index].setFillColor(sf::Color::White);
	}
}


void DropDown::draw()
{
	_window.draw(_shapes[0]);
	_window.draw(_texts[0]);

	if(_active)
	{
		for(int i = 1; i < _shapes.size();i++)
		{
		_window.draw(_shapes[i]);
		_window.draw(_texts[i]);
		}
	}

}

void DropDown::pushOption(std::string name)
{
	int valipikseli = 4;
	_shapes.push_back(_shapes[0]);
	int index = _shapes.size()-1;
	_shapes[index].setPosition(_shapes[index-1].getPosition().x,
				_shapes[index-1].getPosition().y+_shapes[0].getSize().y+valipikseli);
	_texts.push_back(sf::Text(name,_font,_shapes[0].getSize().y));
	_texts[index].setPosition(_shapes[index].getPosition());
	_texts[index].setColor(sf::Color::Black);

	arrange(_texts[index],_shapes[index]);
}


DropDown::~DropDown(void)
{
}
