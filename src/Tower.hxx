#ifndef TOW_H
#define TOW_H

#include <SFML/Graphics.hpp>
#include "Batiment.hxx"

using namespace sf;

using namespace std;

class Tower : public Batiment
{

public:
  Tower(RenderWindow&,Vector2f,int,int);  
};

#endif
