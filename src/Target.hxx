#ifndef TAR_H
#define TAR_H

#include <SFML/Graphics.hpp>
#include "Building.hxx"

using namespace sf;

using namespace std;

class Target : public Building
{

public:
  Target(RenderWindow&);  
  void Hit(int);
  bool IsDead();
  int GetHP();
  
};

#endif
