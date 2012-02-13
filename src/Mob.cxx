#include "Mob.hxx"

#include <iostream>
#include <cmath>
#include <list>


Mob::Mob(sf::RenderWindow& aWindow, Vector2f position, int numero) :
_window(aWindow)
{
  _pos=position;
  
  _hasPath=false;
  _circle.SetRadius(3);
  _circle.SetFillColor(Color::Blue);
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


void Mob::AStar(Map& map, int x, int y) {
    _path.clear();
  //_hasPath=false;

  int self_x = (_pos.x-(int)_pos.x%10)/10;
  int self_y = ((_pos.y-30)-(int)_pos.y%10)/10;
  std::cout<<"org: "<<self_x<<":"<<self_y<<"  dest: "<<x<<":"<<y<<endl<<endl;
  //  _node open[80][57];
  list<_node*> open;
  list<_node*> close;
  _node* node_tmp;
  Square* tmp;
  bool flag=false;
  
  int i,j,xtmp,ytmp,limit=0;

  int coutorg,coutdest,coutot;
  //remplissage de ouverts initial
  // for(i=self_x-1;i<=self_x+1;i++){
  //   for(j=self_y-1;j<=self_y+1;j++) {
  //     if ((j<0)||(i<0)) continue;
  //     tmp = map.GetSquare(i,j);
  //     if (!(tmp->IsConstructible())||((i==self_x)&&(j==self_y))) continue;
  node_tmp=new _node();
      
  node_tmp->x=self_x;
  node_tmp->y=self_y;
  //     node_tmp->parent_x=self_x;
  //     node_tmp->parent_y=self_y;
	
  //     //      coutdest= (x-i)*(x-i) + (y-j)*(y-j);
  //     //coutorg=(i-self_x)*(i-self_x) + (j-self_y)*(j-self_y);
  //     coutdest = 16*sqrt((i-x)*(i-x)+(j-y)*(j-y));
  //     coutorg = 16*sqrt((i-self_x)*(i-self_x)+(j-self_y)*(j-self_y));
  //     coutot=coutdest+coutorg;
	
  node_tmp->costtodest = 16*sqrt((self_x-x)*(self_x-x)+(self_y-y)*(self_y-y));
  node_tmp->costfromorg = 0;
  node_tmp->totalcost = node_tmp->costtodest ;
  //     node_tmp->voisin=tmp;
  open.insert(open.end(),node_tmp);
  //   }
  // }
  _node* parent_node;

  while((!open.empty())&&(!flag)&&(limit<100))
    {
      limit ++;
      
      unsigned int low = 0xFFFFFFF0;
      int cost_tmp;
      for (list<_node*>::iterator it = open.begin();it!=open.end();it++)
	{
	  cost_tmp = (*it)->costtodest;
	  //	  std::cout<<"choice : "<<cost_tmp<<"  ";
	  if (cost_tmp<low)
	    {
	      low = cost_tmp;
	      parent_node = *it;
	      //  std::cout<<low<<" ! ";
	    }
	}
      std::cout<<endl<<"Select: "<<parent_node->x<<":"<<parent_node->y<<endl;
      if ((parent_node->x==x)&&(parent_node->y==y)) flag=true;

    

      else {
	xtmp=parent_node->x;
	ytmp=parent_node->y;
	open.remove(parent_node);
	close.insert(close.begin(),parent_node);
	_node* voisin_node;
	bool find_close = false, find_open = false;
	for(i=xtmp-1;i<=xtmp+1;i++) {
	  for(j=ytmp-1;j<=ytmp+1;j++) {

	    if ((j<0)||(i<0)) continue;
	    if ((j>57)||(i>80)) continue;
	    if ((j==ytmp)&&(i==xtmp)) continue;
	    tmp = map.GetSquare(i,j);
	    if (!tmp->IsConstructible()) continue;

	    // euclide
	    coutorg = 16*sqrt((i-xtmp)*(i-xtmp)+(j-ytmp)*(j-ytmp))+parent_node->costfromorg;;
	    coutdest = 16*sqrt((i-x)*(i-x)+(j-y)*(j-y));
	    std::cout<<endl<<"voisins : "<<i<<":"<<j<<" cfo: "<<coutorg<<" ctd: "<<coutdest<<"  ";
	    find_close=false;	  
	    find_open=false;			  

	    coutot=coutdest+coutorg;

	    for (list<_node*>::iterator it = open.begin();it!=open.end();it++)
	      {
		if (((*it)->x==i)&&((*it)->y==j)) 
		  {
		    find_open = true;
		    voisin_node = *it;
		  }
	      }
	    if(find_open) {

	      if(voisin_node->totalcost > coutot) {
		 voisin_node->parent_x=xtmp;
		 voisin_node->parent_y=ytmp;
		 voisin_node->costfromorg = coutorg;
		 voisin_node->totalcost = coutot;
		 voisin_node->costtodest = coutdest;
		 //std::cout<<" remove open "<<endl;

		 //open.remove(voisin_node);
		continue;
		
	      }
	      else continue;
	    }
	    for (list<_node*>::iterator it = close.begin();it!=close.end();it++)
	      {
		if (((*it)->x==i)&&((*it)->y==j)) 
		  {
		    find_close = true;
		    voisin_node = *it;
		  }
	      }

	    if (find_close)

	      {
		if (voisin_node->costfromorg > coutorg)
		  {
		     voisin_node->parent_x = xtmp;
		     voisin_node->parent_y = ytmp;
		     voisin_node->costfromorg = coutorg;
		     voisin_node->totalcost = coutot;
		     voisin_node->costtodest = coutdest;
		    std::cout<<" remove close "<<endl;
		    close.remove(voisin_node);
		    open.insert(open.end(),voisin_node);
		    continue;
		    
		  }
		continue;
	      }
	    if(!find_open&&!find_close) {
	      voisin_node = new _node();
	      voisin_node->x=i;
	      voisin_node->y=j;
	      voisin_node->parent_x=xtmp;
	      voisin_node->parent_y=ytmp;
	      voisin_node->costtodest = coutdest;
	      voisin_node->costfromorg = coutorg;
	      voisin_node->totalcost = coutot;
	      std::cout<<" add open "<<endl;
	      open.insert(open.end(),voisin_node);
	      continue;
	    }
	    else {
	    }
	  }
	}
      }
    
    }
  close.reverse();
  _xtmp = _pos.x;
  _ytmp = _pos.y;
  
  for (list<_node*>::iterator it = close.begin();it!=close.end();it++)
    {
      //    std::cout<<(*it)->x<<":"<<(*it)->y<<"  cost: "<<(*it)->costtodest<<"  ";
      Bresenham((*it)->x*10+5,(*it)->y*10+35);
      _xtmp = (*it)->x*10+5;
      _ytmp = (*it)->y*10+35;
      
      //_path.insert(_path.end(),new Vector2f((float)(*it)->x*10+5,(float)(*it)->y*10+35));
      //map.Select((*it)->voisin);
      
    }
  
  std::cout<<endl;
  _it=_path.begin();
  _hasPath=true;
  //  std::exit(1);
   
}



void Mob::Bresenham(int x, int y)
{
  // TODO: les deletes a chaque recalcul
  //  _path.clear();
  //_hasPath=false;
  //int x1 = _pos.x, y1 = _pos.y, x2=x, y2=y;
  int x1 = _xtmp, y1 = _ytmp, x2=x, y2=y;
  std::cout<<"bresen from "<<x1<<":"<<y1<<" to "<<x2<<":"<<y2<<endl;
  
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
  //_it=_path.begin();
  //_hasPath=true;
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
