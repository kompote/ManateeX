#include "Map.hxx"

Map::Map() {
  int z =0;
  
  for(int i=0;i<60;i++)
    for(int j=0;j<80;j++) 
      {
	grid[i][j] = new Case(z);	
	grid[i][j]->sprite.SetPosition(j*10,i*10);
	z++;
	      
      }
	
}

Case* Map::getCase(int i, int j) {
  return grid[j][i];
}

Case* Map::getCasePixel(int x, int y) {
  return grid[(y-y%10)/10][(x-x%10)/10];
}
