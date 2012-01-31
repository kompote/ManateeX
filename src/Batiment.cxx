#include "Batiment.hxx"
#include <cmath>

Batiment::Batiment(RenderWindow& aWindow):
  window(aWindow)
 {
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
