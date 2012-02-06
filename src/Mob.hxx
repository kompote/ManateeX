#ifndef MOB_H
#define MOB_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;


class Mob {
public:
  Mob(RenderWindow&,Vector2f,int);
  ~Mob();

	
  void setPosition(Vector2f pos);

  Vector2f getPosition(void);
  
  void Hit(int);
  bool IsDead();
  int GetID();
  
  void Bresenham(int,int);
  
  void render();
  void update(int);
  
private:
  RenderWindow& window;
  Vector2f pos;
  Vector2f cible;
  CircleShape circle;
  std::vector <Vector2f *> path;
  std::vector <Vector2f *>::iterator it;
  int type;
  int PV;
  bool dead;
  bool hasPath;
  int ID;
  
};

#endif
