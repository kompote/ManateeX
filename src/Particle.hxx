#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;


class Particle {
public:
  Particle(RenderWindow&,Vector2f,int,Vector2f,int);
  ~Particle();

  bool IsDone();
  int GetTargetNbr();
  int GetPower();
  
  void SetPosition(Vector2f pos);

  Vector2f GetPosition(void);
  
  void Bresenham(int,int);
  
  void Render();
  void Update();
  
private:
  RenderWindow& _window;
  Vector2f _pos;
  Vector2f _target;
  CircleShape _circle;
  std::vector <Vector2f *> _path;
  std::vector <Vector2f *>::iterator _it;
  int _type;
  int _tarNbr;
  int _power;
  
  bool _done;
  bool _hasPath;
};

#endif
