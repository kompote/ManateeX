#ifndef PROJ_H
#define PROJ_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

using namespace sf;

using namespace std;

class Proj {
  
private:
  int pv_;
  string texturePath_;
  Texture texture_;
  int posX_;
  int posY_;
  bool dead_;
  
  
  
public:
  Sprite SpriteProj;
  int Number;
  
  Proj(int,int,int,int);

  bool IsDead();
  void Move(int,int);
  
  void MoveTo();
  void Bresenham();
  
  void Hit(int);
  int GetPV();
  int GetPosX();
  int GetPosY();
  string getTexturePath();
  void SetTexturePath(string path,bool );
  
};

#endif
