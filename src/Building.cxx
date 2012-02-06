#include "Building.hxx"


Building::Building(RenderWindow& aWindow):
  window(aWindow)
 {
   htarget = false;
   canshoot = false;
   
 }

Vector2f Building::GetPos()
{
  return position;
}


void Building::Select()
{
  sprite.SetColor(Color(0,255,0,255));
}

void Building::UnSelect()
{
  sprite.SetColor(Color(255,255,255,255));
}

void Building::Render()
{
  window.Draw(sprite);	      
}

bool Building::InRange(Vector2f p)
{
  if ((p.x<position.x-range)||(p.x>position.x+range)) return false;
  if ((p.y<position.y-range)||(p.y>position.y+range)) return false;
  return true;
}

int Building::GetType()
{
  return type;
}

bool Building::HasTarget()
{
  return htarget;
}

Mob* Building::GetTarget()
{
  return target;
}

void Building::SetTarget(Mob* t)
{
  target = t;
  htarget=true;
  
}
void Building::ReleaseTarget()
{
  htarget=false;
}

bool Building::CanShoot()
{
  if (tries>=reloadtime)
    {
      tries = 0;
      return true;
    }
  
  tries++;
  return false;
  
}

