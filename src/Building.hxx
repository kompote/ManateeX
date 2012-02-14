#ifndef BUILD_H
#define BUILD_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Mob.hxx"

using namespace sf;
using namespace std;

class Building
{
  

public:
  RenderWindow& window;
  string texturePath;
  Texture texture;
  Sprite sprite;
  int number;

  int hp;
  bool dead;
  
  
  Vector2f position;
  


  Building(RenderWindow&);

  Vector2f GetPos();
  
  void Select();
  void UnSelect();
  void Render();  

  
  
};

#endif
