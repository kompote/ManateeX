#ifndef SQR_H
#define SQR_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

using namespace sf;

using namespace std;

class Square
{
  
private:
  bool _free;
  int _content;
  string _texturePath;
  Texture _texture;
  Transformable _transform;
  

public:
  Sprite sprite;
  int number;
  void SetPosition(int,int);
  Vector2f GetPosition() const;
  
  void Draw(RenderTarget& target) const;
  void Select();
  void UnSelect();
  

  Square(int);
  bool IsConstructible();
  void SetConstructible(bool);
  
  int GetContent();
  string GetTexturePath();
  void SetTexturePath(string path, bool);
  
};

#endif
