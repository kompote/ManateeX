#include "Building.hxx"


Building::Building(RenderWindow& aWindow):
  window(aWindow)
 {
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

