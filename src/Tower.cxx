#include "Tower.hxx"

Tower::Tower(sf::RenderWindow& aWindow, Vector2f pos, int i, int t):
  Building(aWindow)
{
  texturePath = "src/ressources/images/tower1.png";
  texture.LoadFromFile(texturePath);
  sprite.SetTexture(texture);

  position.x=((int)((pos.x/10)*10)+5)-10;
  position.y=((int)((pos.y/10)*10)+5)-10;
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
      range=400;
      reloadtime=12;
    }
  
}
