#include "Mob.hxx"

Mob::Mob(int i, int x, int y) {
  texturePath_ = "src/ressources/images/mob.png";
  texture_.LoadFromFile(texturePath_);
  SpriteMob.SetTexture(texture_);
  SpriteMob.SetPosition(x,y);
  
  Number = i;
  posX_ = 50;
  posY_ = 50;
  
  dead_ = false;
  
}

bool Mob::IsDead() 
{
  return dead_;
}


void Mob::Hit(int k) 
{
  pv_-=k;
  if (pv_<0) {
    dead_ = true;
    return;
  }
  
}

void Mob::Move(int x, int y) 
{
  posX_ = x;
  posY_ = y;
  //  int m[2];
  //m[0] = x;
  //m[1] = y;
  
  //  SpriteMob.SetPosition(x,y);
  cout<<"Debut Thread Trajectoire"<<endl;
  
  Thread thread(&Mob::MoveTo,this);
  thread.Launch();

  return;
  
}
//((sf::priv::ThreadFunctor<void (Mob::*)()>*)this)->sf::priv::ThreadFunctor<void (Mob::*)()>::myFunctor (...)
//(... ->* ((sf::priv::ThreadFunctor<void (Mob::*)()>*)this)->sf::priv::ThreadFunctor<void (Mob::*)()>::myFunctor) (...)


void Mob::MoveTo() 
{
  // Algo de Bresenham
  //  int *d =(int*)data;
  
  int dx, dy;
  int e;

  Vector2i v = (Vector2i) SpriteMob.GetPosition();
  
  int x1 = v.x, y1 = v.y, x2=posX_, y2=posY_;
  cout<<x1<<":"<<y1<<" "<<x2<<":"<<y2<<endl;
  
  e = x2 - x1;
  dx = e*2;
  dy = (y2 - y1) * 2;
  while (x1 < x2) 
    {
      SpriteMob.SetPosition(x1,y1);
      x1++;
      if ((e=e-dy)<=0) 
  	{
  	  y1++;
  	  e=e+dx;
  	}
      usleep(50000);
      //cout<<"move @"<<x1<<":"<<y1<<endl;     
    }
  cout<<"Fin thread trajectoire"<<endl; 
  
}



int Mob::GetPV() {
  return pv_;
}

int Mob::GetPosX() 
{
  return posX_;
}

int Mob::GetPosY() {
  return posY_;
}

string Mob::getTexturePath() {
  return texturePath_;
}


// change le sprite de la case + est constructible ou non

void Mob::SetTexturePath(string path, bool cons) 
{
  texturePath_ = path;
  texture_.LoadFromFile(texturePath_);
  SpriteMob.SetTexture(texture_);
  cout<<"texture changed to "<<texturePath_<<" for case n° "<<Number<<endl;
}
