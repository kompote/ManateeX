#ifndef CASE_H
#define CASE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

using namespace sf;

using namespace std;

class Case {
  
private:
  bool constructible;
  int content;
  string texturePath;
  Texture texture;
  Image im;

public:
  Sprite sprite;
  int number;
  
  Case(int);
  bool isConstructible();
  void SetConstructible(bool);
  void Select();
  void UnSelect();
  
  int getContent();
  string getTexturePath();
  void SetTexturePath(string path,bool );
  
};

#endif
