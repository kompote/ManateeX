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
  
  //Bresenham(400,300);
  _dead = false;
  _hp=2000;
  _id = numero;
  //  std::cout<<"create: "<<_id<<std::endl;  
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
		

void Mob::AStar(Map& map,int x, int y)
{
  _path.clear();
  _hasPath=false;

  //  int self_x = map.GetSquarePixel(_pos.x , _pos.y).GetPosition().x;
  //  int self_y = map.GetSquarePixel(_pos.x , _pos.y).GetPosition().y;
  //Vector2f toto = map.GetSquarePixel(_pos.x,_pos.y).GetPosition();
  int self_x = (_pos.x-(int)_pos.x%10)/10;
  int self_y = ((_pos.y-30)-(int)_pos.y%10)/10;

  std::cout<<"org: "<<self_x<<":"<<self_y<<"  dest: "<<x<<":"<<y<<endl<<endl;
  

  //std::vector<int> node;
  std::vector<_node> open;
  std::vector<Square*> close;
  std::vector<_node> successor;
  _node test[80][57];
  
  //  std::vector<Square*> close;
  Square* tmp;
  _node tmp_node;

  // on rempli la liste ouverte avec toutes les cases possible et les couts  
  for(int i=0;i<80;i++) 
    for(int j=0;j<57;j++)

      {
	tmp = map.GetSquare(i,j);
	if (tmp->IsConstructible())
	  {
	    test[i][j].x=i;
	    test[i][j].y=j;
	    // On travaille au carre de la distance (plus rapide)
	    test[i][j].costtodest = (x-i)*(x-i) + (y-j)*(y-j);
	    // attention! x et y = numero des cases!!
	    test[i][j].costfromorg = (i-self_x)*(i-self_x) + (j-self_y)*(j-self_y);
	    test[i][j].totalcost = test[i][j].costtodest + test[i][j].costfromorg;
	    test[i][j].current=tmp;
	  }
	else
	  {
	    std::cout<<i<<":"<<j<<" not constructible"<<endl;
	    
	    test[i][j].costtodest=0xFFFFFFFF;
	  }
	
	
      }
  int kk = 0;
  
  while (kk<200)
    {
      
      unsigned int low = 0xFFFFFFF0;  
      int cost_tmp;
      _node node_tmp;
      // int k=-1;
      // int z=-1;
      // if (self_x==0)      
      // 	k=0;
      // if (self_y==0)
      // 	z=0;
      

      for (int k=-1;k<=1;k++)
	for (int z=-1;z<=1;z++)
	  {
	    if ((self_x==0)&&(k==-1)) continue;
	    if ((self_y==0)&&(z==-1)) continue;

	    if (!k&&!z) continue;
	    cost_tmp = test[self_x+k][self_y+z].costtodest;
	    std::cout<<"choice : "<<cost_tmp<<"  ";
	    if (cost_tmp<low)
	      {
		low = cost_tmp;
		node_tmp = test[self_x+k][self_y+z];
		
		//	std::cout<<low<<" ! ";
	      }
	    
	  }
      std::cout<<"selected: "<<node_tmp.x<<":"<<node_tmp.y<<"  ctd: "<<node_tmp.costtodest<<"  cfo: "<<node_tmp.costfromorg<<endl;
      close.insert(close.end(),node_tmp.current);
      _path.insert(_path.end(),new Vector2f((float)node_tmp.x*10+5,(float)node_tmp.y*10+35));
      
      self_x = node_tmp.x;
      self_y = node_tmp.y;
      kk++;
      if ((self_x==x)&&(self_y==y)) {
	break;
	
      }
      
    }

  for(std::vector<Square*>::iterator SqIt = close.begin();SqIt!=close.end();SqIt++)
    {
      (*SqIt)->Select();
      
    }
  _it=_path.begin();
  _hasPath=true;

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
    //    std::cout<<"dead: "<<_id<<std::endl;
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
