#ifndef CASE_H
#define CASE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

using namespace sf;

using namespace std;

class Case
{
  
private:
  bool constructible;
  int content;
  string texturePath;
  Texture texture;
  Transformable transform;
  

public:
  Sprite sprite;
  int number;
  void setPosition(int,int);
  
  void draw(RenderTarget& target) const;
  

  Case(int);
  bool isConstructible();
  void SetConstructible(bool);
  
  int getContent();
  string getTexturePath();
  void SetTexturePath(string path, bool);
  
};

#endif
