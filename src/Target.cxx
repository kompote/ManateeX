#include "Target.hxx"

Target::Target(sf::RenderWindow& aWindow):
  Building(aWindow)
{
  //  std::cout<<"toto"<<endl;
  texturePath = "src/ressources/images/dewgong.png";
  texture.LoadFromFile(texturePath);
  sprite.SetTexture(texture);
  position.x=385;
  position.y=320;
  sprite.SetPosition(position);

  range = 0;
  number = 0;
  type = 0;
  reloadtime = 0;
  tries = 0;
  dead = false;
  hp = 50000;
}


void Target::Hit(int k)
{
  hp=hp-k;
  if (hp<=0) {
    dead = true;
  }
}

bool Target::IsDead()
{
  return dead;
}
