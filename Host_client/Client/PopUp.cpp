#include "PopUp.h"


PopUp::PopUp(sf::Font font,std::string message,sf::Vector2f position,sf::Vector2f size,int time)
{
	_font = new sf::Font;
	wantsToDie = false;
	_time = time;
	*_font = font;
	_text.setFont(*_font);
	_text.setString(message);
	
	
	_shape.setSize(size);
	_text.setCharacterSize(size.y*0.5f);
	_shape.setPosition(position);
	_text.setPosition(position);
	_text.setColor(sf::Color::Black);
	_shape.setOutlineThickness(2.0f);
	_shape.setOutlineColor(sf::Color::Black);
	
	float ratiox = _shape.getGlobalBounds().width/_text.getGlobalBounds().width;
	float ratioy = _shape.getGlobalBounds().height/_text.getGlobalBounds().height;
	ratioy*=0.5f;
	_text.setScale(ratiox,ratioy);
	
}

bool PopUp::draw(sf::RenderWindow &window)
{
	if(_timer.getElapsedTime().asSeconds()>_time)
	{
		wantsToDie = true;
		return wantsToDie;
	}
	
	window.draw(_shape);
	window.draw(_text);
	return wantsToDie;

	
}

PopUp::~PopUp(void)
{
}
