#include "Batiment.hxx"


Batiment::Batiment(RenderWindow& aWindow):
  window(aWindow)
 {
   htarget = false;
   canshoot = false;
   
 }

Vector2f Batiment::GetPos()
{
  return position;
}


void Batiment::Select()
{
  sprite.SetColor(Color(0,255,0,255));
}

void Batiment::UnSelect()
{
  sprite.SetColor(Color(255,255,255,255));
}

void Batiment::render()
{
  window.Draw(sprite);	      
}

bool Batiment::InRange(Vector2f p)
{
  if ((p.x<position.x-range)||(p.x>position.x+range)) return false;
  if ((p.y<position.y-range)||(p.y>position.y+range)) return false;
  return true;
}

int Batiment::GetType()
{
  return type;
}

bool Batiment::HasTarget()
{
  return htarget;
}

Mob* Batiment::GetTarget()
{
  return target;
}

void Batiment::SetTarget(Mob* t)
{
  target = t;
  htarget=true;
  
}
void Batiment::ReleaseTarget()
{
  htarget=false;
}

bool Batiment::CanShoot()
{
  if (tries>=reloadtime)
    {
      tries = 0;
      return true;
    }
  
  tries++;
  return false;
  
}

