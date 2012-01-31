#ifndef BAT_H
#define BAT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

class Batiment
{
  

public:
  RenderWindow& window;
  string texturePath;
  Texture texture;
  Sprite sprite;
  int number;
  int type;
  int range;
  
  Vector2f position;
  


  Batiment(RenderWindow&);

  Vector2f GetPos();
  bool InRange(Vector2f);
  int GetType();
  
  void Select();
  void UnSelect();
  void render();  
  
};

#endif
