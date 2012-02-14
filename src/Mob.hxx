#ifndef MOB_H
#define MOB_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Map.hxx"
using namespace sf;

typedef struct 
  {
    int x;
    int y;
    int parent_x;
    int parent_y;
    int costtodest;
    int costfromorg;
    int totalcost;
    Square* current;
  } _node;


class Mob {
public:
  Mob(RenderWindow&,Vector2f,int);
  ~Mob();
  void SetPosition(Vector2f pos);
  Vector2f GetPosition(void);
  void Hit(int);
  bool IsDead();
  int GetID();
  int GetHP();
  int FindPath (int startingX, int startingY, int targetX, int targetY, bool stepByStep);
  bool HasArrived();
  void AStar(Map&,int,int);
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
  int _hp;
  bool _dead;
  bool _hasPath;
  int _id;
  int _xtmp;
  int _ytmp;
  bool _arrived;
  //  pair<int,int>   
};

#endif
