#include "Explosion.h"


Explosion::Explosion(sf::Vector2f pos)
{
	trigger = false;
	std::srand(unsigned(std::time(NULL)));
	for(int i = 0; i < 100;i++)
	_particles.append(sf::Vertex(pos,sf::Color(255,0,0,30)));

	for(int i = 0; i < 100;i++)
	_particles.append(sf::Vertex(pos,sf::Color(255,255,0,30)));
	
	
	_particles.setPrimitiveType(sf::PrimitiveType::Lines);

	for(int i = 0; i < _particles.getVertexCount();i++)
	 {
		 int x = std::rand()%5-2;
		 int y = std::rand()%5-2;

		
		 int x2 = std::rand()%10;
		 int y2 = std::rand()%10;
		 x2*=0.2f;
		 y2*=0.2f;

		 x*=x2;
		 y*=y2;

		  _speeds.push_back(sf::Vector2f(x,y));

		 }

		

	}

	//for(int i = 0; i < _particles.getVertexCount();i++)
	// {
	//	 float x = std::rand()%10;
	//	 float y = std::rand()%10;
	//	 x*0.1f;
	//	 y*0.1f;


	//	 _speeds[i].x*=x;
	//	 _speeds[i].y*=y;
	//}


bool Explosion::update()
{
	if(_timer.getElapsedTime().asSeconds()>0.01f)
	{
		for(int i = 0; i < _particles.getVertexCount();i++)
		{
		if(_timer2.getElapsedTime().asSeconds()>0.5)
		{
			//for(int i = 0; i < _particles.getVertexCount();i++)
			_speeds[i]*=0.99f;
			_particles[i].color.a-=1;
			//_timer2.restart();
		}
		
		_particles[i].position+=sf::Vector2f(_speeds[i].x,_speeds[i].y);

		if(_particles[i].color.a!=0)
		{
				//_particles[i].color.g++;
				//_particles[i].color.b+=4;
				
		}
	}

	/*if(_timer2.getElapsedTime().asSeconds()>1)
			{
				if(!trigger)
				{
					for(int i = 0;i < _particles.getVertexCount();i++)
					{
					_speeds[i].x*=-1;
					_speeds[i].y*=-1;
					trigger = true;
					}
				}
			}*/
	_timer.restart();
	}
	if(_particles[_particles.getVertexCount()-1].color.a == 0)
		{
			return false;
		}
	else
		return true;
}


void Explosion::draw(sf::RenderWindow &window)
{
	window.draw(_particles);
}

Explosion::~Explosion(void)
{
}
