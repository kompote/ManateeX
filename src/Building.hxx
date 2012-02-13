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
  int type;
  int range;
  bool htarget;
  Mob *target;
  bool canshoot;
  int reloadtime;
  int tries;
  int hp;
  bool dead;
  
  
  Vector2f position;
  


  Building(RenderWindow&);

  Vector2f GetPos();
  bool InRange(Vector2f);
  int GetType();
  
  void Select();
  void UnSelect();
  void Render();  

  Mob* GetTarget();
  void SetTarget(Mob*);
  bool HasTarget();
  void ReleaseTarget();
  bool CanShoot();
  
  
};

#endif
