#include "Mob.hxx"

#include <iostream>
#include <cmath>

Mob::Mob(sf::RenderWindow& aWindow, Vector2f position, int numero) :
_window(aWindow)
{
  _pos=position;
  
  _hasPath=false;
  _circle.SetRadius(2*numero);
  _circle.SetFillColor(Color::Black);
  _circle.SetPosition(_pos);
  Bresenham(400,300);
  _dead = false;
  _hp=5000;
  _id = numero;
  std::cout<<"create: "<<_id<<std::endl;  
}

Mob::~Mob()
{
  // les deletes...
}

void Mob::SetPosition(sf::Vector2f aPos)
{
  // inutile
	_pos = aPos;
}


sf::Vector2f Mob::GetPosition(void)
{
  // inutile
	return _pos;
}

bool Mob::IsDead() 
{
  return _dead;
}

int Mob::GetID()
{
  return _id;
}


void Mob::Bresenham(int x, int y)
{
  // TODO: les deletes a chaque recalcul
  _path.clear();
  _hasPath=false;
  int x1 = _pos.x, y1 = _pos.y, x2=x, y2=y;
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
	  _path.insert(_path.end(),new Vector2f((float)x1,(float)y1));
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
	  _path.insert(_path.end(),new Vector2f((float)x1,(float)y1));
        }
    }
  _it=_path.begin();
  _hasPath=true;
}

void Mob::Hit(int k)
{
  _hp=_hp-k;
  if (_hp<=0) {
    _dead = true;
    std::cout<<"dead: "<<_id<<std::endl;
  }
  
  
}


void Mob::Render()
{
  _window.Draw(_circle);	      
}

void Mob::Update()
{
  
  // ne fait rien si pas encore de _path
  if (!_hasPath) return;
  // boucle le _path, on pourrait ajouter un timer entre les boucles
  if(_it==_path.end()) _it=_path.begin();
  // vitesse....
  _pos.x=(*_it)->x;
  _pos.y=(*_it)->y;

  _circle.SetPosition(_pos);
  _it++;
}
