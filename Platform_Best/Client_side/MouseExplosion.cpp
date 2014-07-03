#include "MouseExplosion.h"


MouseExplosion::MouseExplosion(sf::Vector2f pos,sf::Color color1,sf::Color color2)
{
	int particlecount = 100;

	sf::Vector2f randpos;
	//std::srand(unsigned(std::time(NULL)));

	for(int i = 0; i < particlecount;i++)
	 {
		 int x = std::rand()%21-10;
		 int y = std::rand()%21-10;

		
		 int x2 = std::rand()%11;
		 int y2 = std::rand()%11;
		 x2*=0.2f;
		 y2*=0.2;

		 randpos.x = x;
		 randpos.y = y;
		 x*=x2;
		 y*=y2;

		 _speeds.push_back(sf::Vector2f(x,y));
		 _speeds.push_back(sf::Vector2f(y,x));
		 
		 

		 randpos+=pos;

		_particles.append(sf::Vertex(randpos,color1));
		_particles.append(sf::Vertex(randpos,color2));

	}
	
	_particles.setPrimitiveType(sf::PrimitiveType::Quads);

}

MouseExplosion::~MouseExplosion(void)
{

}

void MouseExplosion::draw(sf::RenderWindow &window)
{
	window.draw(_particles);
}

void MouseExplosion::checkWindowCollision(sf::RenderWindow &window)
{
	for(int i = 0; i < _particles.getVertexCount();i++)
		if(_particles[i].position.x <0)
			_speeds[i].x*=-1;
		else if(_particles[i].position.x>window.getSize().x)
			_speeds[i].x*=-1;
		else if(_particles[i].position.y<0)
			_speeds[i].y*=-1;
		else if(_particles[i].position.y>window.getSize().y)
			_speeds[i].y*=-1;
			
}

bool MouseExplosion::update()
{
	if(_timer.getElapsedTime().asSeconds()>0.01f)
	{
		for(int i = 0; i < _particles.getVertexCount();i++)
		{
			//_particles[i].color.b+=1;
			//_particles[i].color.g-=1;
		float lel = 0.9f;
		if(_particles[i].color.a>5)
		_speeds[i]*=lel;
		_particles[i].position+=sf::Vector2f(_speeds[i].x,_speeds[i].y);
		}
	_timer.restart();
	}
	if(_timer2.getElapsedTime().asSeconds()>0.02f)
		{
			for(int i = 0;i < _particles.getVertexCount();i++)
			{
				_particles[i].color.a-=1;
				if(_particles[i].color.a==16)
					_speeds[i]*=-1.f;
			}
			_timer2.restart();

		}
	
	if(_particles[_particles.getVertexCount()-1].color.a == 0)
		{
			return false;
		}
	else
		return true;

}