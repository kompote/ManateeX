#ifndef MAP_H
#define MAP_H

#include "Case.hxx"

class Map {

private:
  Case* grid[60][80];
		
public:
  Map();
  void Redraw(RenderTarget& target) const;
  
  Case* getCase(int i, int j);
  Case* getCasePixel(int x, int y);
};

#endif
