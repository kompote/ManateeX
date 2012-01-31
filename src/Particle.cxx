#include "Particle.hxx"

#include <iostream>
#include <cmath>

Particle::Particle(sf::RenderWindow& aWindow, Vector2f position, int t, Vector2f ci, int nci) :
window(aWindow)
{
  pos = position;
  cible = ci;
  done = false;
  ncible = nci;
  
  hasPath=false;
  type = t;
  // Different type de tirs, donc de tours
  switch(type)
    {
    case 1:
      circle.SetRadius(4);
      circle.SetFillColor(Color::Blue);
      circle.SetPosition(pos);
      power = 200;
      
      break;
      
    case 2:
      circle.SetRadius(2);
      circle.SetFillColor(Color::Red);
      circle.SetPosition(pos);
      power = 100;
      
      break;
    }

  Bresenham(cible.x,cible.y);
  
  
}

Particle::~Particle()
{
  // les deletes...
}

void Particle::setPosition(sf::Vector2f aPos)
{
  // inutile
	pos = aPos;
}


sf::Vector2f Particle::getPosition(void)
{
  // inutile
	return pos;
}

bool Particle::isDone()
{
  return done;
}

int Particle::GetCibleNbr()
{
  return ncible;
}

int Particle::GetPower()
{
  return power;
}




void Particle::Bresenham(int x, int y)
{
  // TODO: les deletes a chaque recalcul
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
  // ne fait rien si pas encore de path
  if (!hasPath) return;
  // boucle le path, on pourrait ajouter un timer entre les boucles
  if(it==path.end()) done = true;
  if (!done) 
    {
      
      // vitesse....
      int x=(*it)->x;
      int y=(*it)->y;
      if (type == 2) 
	{
	  x+=2;
	  y+=2;
	}
      
      circle.SetPosition(x,y);
      it++;
    }
  
}
