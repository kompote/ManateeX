#ifndef MOB_H
#define MOB_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;


class Mob {
public:
  Mob(RenderWindow&,Vector2f,int);
  ~Mob();

	
  void SetPosition(Vector2f pos);

  Vector2f GetPosition(void);
  
  void Hit(int);
  bool IsDead();
  int GetID();
  
  void Bresenham(int,int);
  
  void Render();
  void Update(int);
  
private:
  RenderWindow& _window;
  Vector2f _pos;
  Vector2f _target;
  CircleShape _circle;
  std::vector <Vector2f *> _path;
  std::vector <Vector2f *>::iterator _it;
  int _type;
  int _hp;
  bool _dead;
  bool _hasPath;
  int _id;
  
};

#endif
