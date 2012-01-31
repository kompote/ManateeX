#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;


class Particle {
public:
  Particle(RenderWindow&,Vector2f,int,Vector2f,int);
  ~Particle();

  bool isDone();
  int GetCibleNbr();
  int GetPower();
  
  void setPosition(Vector2f pos);

  Vector2f getPosition(void);
  
  void Bresenham(int,int);
  
  void render();
  void update();
  
private:
  RenderWindow& window;
  Vector2f pos;
  Vector2f cible;
  CircleShape circle;
  std::vector <Vector2f *> path;
  std::vector <Vector2f *>::iterator it;
  int type;
  int ncible;
  int power;
  
  bool done;
  bool hasPath;
};

#endif
