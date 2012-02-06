#ifndef MAP_H
#define MAP_H

#include "Square.hxx"

class Map {

private:
  Square* _grid[60][80];
  Square* _lastSelected;
  
		
public:
  Map();
  void Redraw(RenderTarget& target) const;
  
  Square* GetSquare(int i, int j);
  Square* GetSquarePixel(int x, int y);
  void Select(Square*);
  
};

#endif
