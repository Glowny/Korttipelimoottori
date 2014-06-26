#include "PopUp.h"


PopUp::PopUp(sf::Font font,std::string message,sf::Vector2f position,sf::Vector2f size,int time)
{
	_font = new sf::Font;
	wantsToDie = false;
	_time = time;
	*_font = font;
	_text.setFont(*_font);
	_text.setString(message);
	trigger = 0;
	
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
	delay = 0.15f;

	_explosions.push_back(Explosion(sf::Vector2f(_shape.getPosition().x+_shape.getSize().x*0.5f,_shape.getPosition().y+_shape.getSize().y*0.5f)));
	
}

bool PopUp::draw(sf::RenderWindow &window)
{

	if(_timer2.getElapsedTime().asSeconds()>delay && trigger == 0)
	{
		_explosions.push_back(Explosion(sf::Vector2f(_shape.getPosition().x+_shape.getSize().x,_shape.getPosition().y+_shape.getSize().y*0.5f)));
		trigger = 1;
		_timer2.restart();
	}
	if(_timer2.getElapsedTime().asSeconds()>delay && trigger == 1)
	{
		_explosions.push_back(Explosion(sf::Vector2f(_shape.getPosition().x,_shape.getPosition().y+_shape.getSize().y*0.5f)));
	_timer2.restart();
	trigger = 3;
	}
	if(_timer2.getElapsedTime().asSeconds()>delay && trigger == 3)
	{

	}


	if(_timer.getElapsedTime().asSeconds()>_time && time != 0)
	{
		wantsToDie = true;
		return wantsToDie;
	}

	for(int i = 0; i < _explosions.size();i++)
	{
		if(_explosions[i].update())
			_explosions[i].draw(window);
		else
			_explosions.erase(_explosions.begin()+i);
	}

	window.draw(_shape);
	window.draw(_text);

	return wantsToDie;
	
}

PopUp::~PopUp(void)
{
}
