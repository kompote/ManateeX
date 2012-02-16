#include "Particle.hxx"

Particle::Particle(sf::RenderWindow& aWindow, Vector2f position, int t, Vector2f ci, int nci) :
_window(aWindow)
{
  _pos = position;
  _target = ci;
  _done = false;
  _tarNbr = nci;
  
  _hasPath=false;
  _type = t;
  // Different _type de tirs, donc de tours
  switch(_type)
    {
    case 1:
      _circle.SetRadius(2);
      _circle.SetFillColor(Color::Red);
      _circle.SetPosition(_pos);
      _power = 200;
      
      break;
      
    case 2:
      _circle.SetRadius(3);
      _circle.SetFillColor(Color::Blue);
      _circle.SetPosition(_pos);
      _power = 400;
      
      break;
    }

  Bresenham(_target.x,_target.y);
  
  
}

Particle::~Particle()
{
  // les deletes...
}

void Particle::SetPosition(sf::Vector2f aPos)
{
  // inutile
  _pos = aPos;
}


sf::Vector2f Particle::GetPosition(void)
{
  // inutile
  return _pos;
}

bool Particle::IsDone()
{
  return _done;
}

int Particle::GetTargetNbr()
{
  return _tarNbr;
}

int Particle::GetPower()
{
  return _power;
}

void Particle::Bresenham(int x, int y)
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


void Particle::Render()
{
  _window.Draw(_circle);	      
}

void Particle::Update()
{
  // ne fait rien si pas encore de _path
  if (!_hasPath) return;
  // boucle le _path, on pourrait ajouter un timer entre les boucles
  if(_it==_path.end()) _done = true;
  if (!_done) 
    {
      
      // vitesse....
      int x=(*_it)->x;
      int y=(*_it)->y;
      if (_type == 2) 
	{
	  x+=2;
	  y+=2;
	}
      
      _circle.SetPosition(x,y);
      _it++;
    }
  
}
