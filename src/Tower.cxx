#include "Tower.hxx"

Tower::Tower(sf::RenderWindow& aWindow, Vector2f pos, int i, int t):
  Building(aWindow)
{
	htarget = false;
  canshoot = false;
  texturePath = "src/ressources/images/turret.png";
  texture.LoadFromFile(texturePath);
  sprite.SetTexture(texture);
	sprite.SetOrigin(12.5,12.5);
  
  position.x=((int)((pos.x/10)*10)+5);
  position.y=((int)((pos.y/10)*10)+5);
  number = i;
  type = t;
  sprite.SetPosition(position);


  std::cout<<"tour cree : "<<position.x+10<<":"<<position.y+10<<std::endl;
  switch(type  )
    {
    case 1:
      range=100;
      reloadtime=2;
      
      break;
    case 2:
      range=200;
      reloadtime=12;
    }
  
}

bool Tower::InRange(Vector2f p)
{
  if ((p.x<position.x-range)||(p.x>position.x+range)) return false;
  if ((p.y<position.y-range)||(p.y>position.y+range)) return false;
  return true;
}

int Tower::GetType()
{
  return type;
}

bool Tower::HasTarget()
{
  return htarget;
}

Mob* Tower::GetTarget()
{
  return target;
}

void Tower::SetTarget(Mob* t)
{
  target = t;
  htarget=true;
  
}
void Tower::ReleaseTarget()
{
  htarget=false;
}

bool Tower::CanShoot()
{
  if (tries>=reloadtime)
    {
      tries = 0;
      return true;
    }
  
  tries++;
  return false;
  
}

void Tower::FaceTarget()
{
	//sprite.SetOrigin(15,15);
	if(this->HasTarget())
	{
		Vector2f tpos = target->GetPosition();
		sprite.SetRotation(90);
	}
	else sprite.SetRotation(0);
}
