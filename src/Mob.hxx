#ifndef MOB_H
#define MOB_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

using namespace sf;

using namespace std;

class Mob {
  
private:
  int pv_;
  string texturePath_;
  Texture texture_;
  int posX_;
  int posY_;
  bool dead_;
  
  
  
public:
  Sprite SpriteMob;
  int Number;
  
  Mob(int,int,int);

  bool IsDead();
  void Move(int,int);
  
  void MoveTo();
  
  void Hit(int);
  int GetPV();
  int GetPosX();
  int GetPosY();
  string getTexturePath();
  void SetTexturePath(string path,bool );
  
};

#endif
