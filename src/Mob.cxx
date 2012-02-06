#include "Mob.hxx"

#include <iostream>
#include <cmath>

Mob::Mob(sf::RenderWindow& aWindow, Vector2f position, int numero) :
window(aWindow)
{
  pos=position;
  
  hasPath=false;
  circle.SetRadius(6);
  circle.SetFillColor(Color::Black);
  circle.SetPosition(pos);
  Bresenham(400,300);
  dead = false;
  PV=5000;
  ID = numero;
  
}

Mob::~Mob()
{
  // les deletes...
}

void Mob::setPosition(sf::Vector2f aPos)
{
  // inutile
	pos = aPos;
}


sf::Vector2f Mob::getPosition(void)
{
  // inutile
	return pos;
}

bool Mob::IsDead() 
{
  return dead;
}

int Mob::GetID()
{
  return ID;
}


void Mob::Bresenham(int x, int y)
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

void Mob::Hit(int k)
{
  PV=PV-k;
  if (PV<=0) dead = true;
  //  std::cout<<"hiit: "<<PV<<std::endl;
  
}


void Mob::render()
{
  window.Draw(circle);	      
}

void Mob::update(int i)
{
  ID = i;
  
  // ne fait rien si pas encore de path
  if (!hasPath) return;
  // boucle le path, on pourrait ajouter un timer entre les boucles
  if(it==path.end()) it=path.begin();
  // vitesse....
  pos.x=(*it)->x;
  pos.y=(*it)->y;

  circle.SetPosition(pos);
  it++;
}
