#include "Proj.hxx"

Proj::Proj(int i, int x, int y, int life) {
  texturePath_ = "src/ressources/images/red.png";
  texture_.LoadFromFile(texturePath_);
  SpriteProj.SetTexture(texture_);
  SpriteProj.SetPosition(x,y);
  
  Number = i;
  posX_ = x;
  posY_ = y;
  pv_ = life;
  

  dead_ = false;
  
}

bool Proj::IsDead() 
{
  return dead_;
}


void Proj::Hit(int k) 
{
  pv_-=k;
  if (pv_<=0) {
    dead_ = true;
    return;
  }
  cout<<"Hit! still :"<<pv_<<endl;
  
  
}

void Proj::Move(int x, int y) 
{
  posX_ = x;
  posY_ = y;
  //  int m[2];
  //m[0] = x;
  //m[1] = y;
  
  //  SpriteProj.SetPosition(x,y);
  cout<<"Debut Thread Trajectoire"<<endl;
  
  Thread thread(&Proj::Bresenham,this);
  thread.Launch();

  return;
  
}

void Proj::MoveTo() 
{
  // Algo de Bresenham
  //  int *d =(int*)data;
  
  int dx, dy;
  int e;

  Vector2i v = (Vector2i) SpriteProj.GetPosition();
  
  int x1 = v.x, y1 = v.y, x2=posX_, y2=posY_;
  cout<<x1<<":"<<y1<<" to "<<x2<<":"<<y2<<endl;
  
  e = x2 - x1;
  dx = e*2;
  dy = (y2 - y1) * 2;
  while (x1 < x2) 
    {
      SpriteProj.SetPosition(x1,y1);
      x1++;
      if ((e=e-dy)<=0) 
  	{
  	  y1++;
  	  e=e+dx;
  	}
      usleep(20000);
      cout<<"move @"<<x1<<":"<<y1<<endl;     
    }
  cout<<"Fin thread trajectoire"<<endl; 
  
}


void Proj::Bresenham()
{

  Vector2i v = (Vector2i) SpriteProj.GetPosition();
  
  int x1 = v.x, y1 = v.y, x2=posX_, y2=posY_;

  
  // if x1 == x2 or y1 == y2, then it does not matter what we set here
  int delta_x(x2 - x1);
  signed char ix((delta_x > 0) - (delta_x < 0));
  delta_x = std::abs(delta_x) << 1;
  int delta_y(y2 - y1);
  signed char iy((delta_y > 0) - (delta_y < 0));
  delta_y = std::abs(delta_y) << 1;
  SpriteProj.SetPosition(x1,y1);
      //  plot(x1, y1);
  if (delta_x >= delta_y)
    {
      // error may go below zero
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
	      // else do nothing
            }
	  // else do nothing
	  x1 += ix;
	  error += delta_y;
	  SpriteProj.SetPosition(x1,y1);
	  //	  plot(x1, y1);
	  usleep(2000);
        }
    }
  else
    {
      // error may go below zero
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
	      // else do nothing
            }
	  // else do nothing
	  y1 += iy;
	  error += delta_x;
	  SpriteProj.SetPosition(x1,y1);
	  //	  plot(x1, y1);
	  usleep(2000);
        }
    }
}




int Proj::GetPV() {
  return pv_;
}

int Proj::GetPosX() 
{
  return posX_;
}

int Proj::GetPosY() {
  return posY_;
}

string Proj::getTexturePath() {
  return texturePath_;
}


// change le sprite de la case + est constructible ou non

void Proj::SetTexturePath(string path, bool cons) 
{
  texturePath_ = path;
  texture_.LoadFromFile(texturePath_);
  SpriteProj.SetTexture(texture_);
  cout<<"texture changed to "<<texturePath_<<" for case n° "<<Number<<endl;
}
