#include "Tower.hxx"

Tower::Tower(sf::RenderWindow& aWindow, Vector2f pos, int i, int t):
  Building(aWindow)
{
  texturePath = "src/ressources/images/tower1.png";
  texture.LoadFromFile(texturePath);
  sprite.SetTexture(texture);
  sprite.SetPosition(pos);
  position.x=pos.x+5;
  position.y=pos.y+5;
  number = i;
  type = t;

  std::cout<<"tour cree : "<<position.x<<":"<<position.y<<std::endl;
  switch(type  )
    {
    case 1:
      range=100;
      reloadtime=2;
      
      break;
    case 2:
      range=400;
      reloadtime=12;
    }
  
}
