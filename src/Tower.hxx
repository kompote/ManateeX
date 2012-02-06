#ifndef TOW_H
#define TOW_H

#include <SFML/Graphics.hpp>
#include "Building.hxx"

using namespace sf;

using namespace std;

class Tower : public Building
{

public:
  Tower(RenderWindow&,Vector2f,int,int);  
};

#endif
