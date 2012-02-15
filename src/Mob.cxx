#include "Mob.hxx"

#include <iostream>
#include <cmath>
#include <list>

/**
 * \fn  Mob::Mob(sf::RenderWindow& aWindow, Vector2f position, int numero)
 * \brief Constructeur
 * \param aWindow le contexte graphique
 * \param position la position initiale
 * \param numero un id
 */
Mob::Mob(sf::RenderWindow& aWindow, Vector2f position, int numero) :
_window(aWindow)
{
  _pos=position;
  
	_arrived=false;
  _hasPath=false;
  _circle.SetRadius(3);
  _circle.SetFillColor(Color::Black);
  _circle.SetPosition(_pos);
  _dead = false;
  _hp=2000;
  _id = numero;
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

int Mob::GetHP()
{
  return _hp;
}


int Mob::GetID()
{
  return _id;
}

bool Mob::HasArrived()
{
  return _arrived;
}


void Mob::AStar(Map& map, int x, int y) {
  _path.clear();
  _target.x = x*10+5;
  _target.y = y*10+35;
  
  int self_x = (_pos.x+3-(int)_pos.x%10)/10;
  int self_y = ((_pos.y+3-30)-(int)_pos.y%10)/10;
  std::cout<<"org: "<<self_x<<":"<<self_y<<"  dest: "<<x<<":"<<y<<endl<<endl;
  list<_node*> open;
  list<_node*> close;
  _node* node_tmp;
  Square* tmp;
  bool flag=false;
  int i,j,xtmp,ytmp,limit=0;
  int coutorg,coutdest,coutot;
  // Le noeud de depart
  node_tmp=new _node();
  node_tmp->x=self_x;
  node_tmp->y=self_y;
  node_tmp->costtodest = 16*sqrt((self_x-x)*(self_x-x)+(self_y-y)*(self_y-y));
  node_tmp->costfromorg = 0;
  node_tmp->totalcost = node_tmp->costtodest ;
  open.insert(open.end(),node_tmp);

  _node* parent_node;

  while((!open.empty())&&(!flag)&&(limit<100))
    {
      limit ++;
      // le noeud le plus leger dans la liste ouverte      
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
      //      std::cout<<endl<<"Select: "<<parent_node->x<<":"<<parent_node->y<<endl;
      //      s'il est final on arrete
      if ((parent_node->x==x)&&(parent_node->y==y)) flag=true;

      else {
	xtmp=parent_node->x;
	ytmp=parent_node->y;
	open.remove(parent_node);
	close.insert(close.begin(),parent_node);
	_node* voisin_node;
	bool find_close = false, find_open = false;
	// pour chaque voisin
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
	    coutot=coutdest+coutorg;
	    //	    std::cout<<endl<<"voisins : "<<i<<":"<<j<<" cfo: "<<coutorg<<" ctd: "<<coutdest<<"  ";
	    find_close=false;	  
	    find_open=false;			  
	    // cherche s'il existe dans la liste ouverte
	    for (list<_node*>::iterator it = open.begin();it!=open.end();it++)
	      {
		if (((*it)->x==i)&&((*it)->y==j)) 
		  {
		    find_open = true;
		    voisin_node = *it;
		  }
	      }
	    // si oui et si meilleur chemin alors on met a jour
	    if(find_open) {
	      if(voisin_node->totalcost > coutot) {
		 voisin_node->parent_x=xtmp;
		 voisin_node->parent_y=ytmp;
		 voisin_node->costfromorg = coutorg;
		 voisin_node->totalcost = coutot;
		 voisin_node->costtodest = coutdest;
		 //open.remove(voisin_node);
		continue;
	      }
	      else continue;
	    }
	    // cherche s'il existe dans la liste fermee
	    for (list<_node*>::iterator it = close.begin();it!=close.end();it++)
	      {
		if (((*it)->x==i)&&((*it)->y==j)) 
		  {
		    find_close = true;
		    voisin_node = *it;
		  }
	      }
	    // si oui et si meilleur alors il existe un meilleur chemin -> on enleve
	    if (find_close)
	      {
		if (voisin_node->costfromorg > coutorg)
		  {
		     voisin_node->parent_x = xtmp;
		     voisin_node->parent_y = ytmp;
		     voisin_node->costfromorg = coutorg;
		     voisin_node->totalcost = coutot;
		     voisin_node->costtodest = coutdest;
		     //		    std::cout<<" remove close "<<endl;
		    close.remove(voisin_node);
		    open.insert(open.end(),voisin_node);
		    continue;
		    
		  }
		continue;
	      }
	    // s'il nexiste pas on le creer
	    if(!find_open&&!find_close) {
	      voisin_node = new _node();
	      voisin_node->x=i;
	      voisin_node->y=j;
	      voisin_node->parent_x=xtmp;
	      voisin_node->parent_y=ytmp;
	      voisin_node->costtodest = coutdest;
	      voisin_node->costfromorg = coutorg;
	      voisin_node->totalcost = coutot;
	      //	      std::cout<<" add open "<<endl;
	      open.insert(open.end(),voisin_node);
	      continue;
	    }
	    else {
	    }
	  }
	}
      }
    
    }
  std::cout<<"limit: "<<limit<<endl;
  
  // inverse la liste
  close.reverse();
  _xtmp = _pos.x+3;
  _ytmp = _pos.y+3;
  // smooth path
  for (list<_node*>::iterator it = close.begin();it!=close.end();it++)
    {
      //  std::cout<<(*it)->x<<":"<<(*it)->y<<"  cost: "<<(*it)->costtodest<<"  ";
      Bresenham((*it)->x*10+5,(*it)->y*10+35);
      _xtmp = (*it)->x*10+5;
      _ytmp = (*it)->y*10+35;
    }
  _path.insert(_path.end(),&_target);  
  _it=_path.begin();
  _hasPath=true;
}



void Mob::Bresenham(int x, int y)
{
  // TODO: les deletes a chaque recalcul
  int x1 = _xtmp, y1 = _ytmp, x2=x, y2=y;
  //  std::cout<<"bresen from "<<x1<<":"<<y1<<" to "<<x2<<":"<<y2<<endl;
  
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
	  //std::cout<<"  "<<x1<<":"<<y1<<"  ";
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
	  //	  std::cout<<"  "<<x1<<":"<<y1<<"  ";
        }
    }
  
  

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
  if (_pos == _target ) {
    _arrived = true;
    //    _dead = true;
    return;
  }
  
  // vitesse....
  _pos.x=(*_it)->x;
  _pos.y=(*_it)->y;

  _circle.SetPosition(_pos);
  _it++;
}
