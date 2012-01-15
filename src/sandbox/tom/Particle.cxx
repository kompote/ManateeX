#include "Particle.hxx"

#include <iostream>
#include <cmath>

Particle::Particle(sf::RenderWindow& aWindow) :
window(aWindow),
pos(320.f, 240.f)

{
  circle.SetRadius(2);
  circle.SetFillColor(Color::Red);
  circle.SetPosition(pos);
  hasPath=false;
  
}

Particle::~Particle()
{

}

void Particle::setPosition(sf::Vector2f aPos)
{
	pos = aPos;
}


sf::Vector2f Particle::getPosition(void)
{
	return pos;
}


void Particle::Bresenham(int x, int y)
{

  path.clear();
  hasPath=false;
  int x1 = pos.x, y1 = pos.y, x2=x, y2=y;
  int delta_x(x2 - x1);
  signed char ix((delta_x > 0) - (delta_x < 0));
  delta_x = std::abs(delta_x) << 1;
  int delta_y(y2 - y1);
  signed char iy((delta_y > 0) - (delta_y < 0));
  delta_y = std::abs(delta_y) << 1;
  if (delta_x >= delta_y)
    {
      int error(delta_y - (delta_x >> 1));
      while (x1 != x2)
        {
	  if (error >= 0)
            {
	      if (error || (ix > 0))
                {
		  y1 += iy;
		  error -= delta_x;
                }
            }
	  x1 += ix;
	  error += delta_y;
	  path.insert(path.end(),new Vector2f((float)x1,(float)y1));
        }
    }
  else
    {
      int error(delta_x - (delta_y >> 1));
      while (y1 != y2)
        {
	  if (error >= 0)
            {
	      if (error || (iy > 0))
                {
		  x1 += ix;
		  error -= delta_y;
                }
            }
	  y1 += iy;
	  error += delta_x;
	  path.insert(path.end(),new Vector2f((float)x1,(float)y1));
        }
    }
  it=path.begin();
  hasPath=true;
}


void Particle::render()
{
  window.Draw(circle);	      
}

void Particle::update()
{
  if (!hasPath) return;
  
  if(it==path.end()) it=path.begin();
  
  circle.SetPosition(**it);
  it++;
}
