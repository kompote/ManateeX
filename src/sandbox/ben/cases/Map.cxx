#include "Map.hxx"

Map::Map() {
for(int i=0;i<60;i++)
for(int j=0;j<80;j++)
grid[i][j] = new Case();
}

Case Map::getCase(int i, int j) {
return *grid[j][i];
}

Case Map::getCasePixel(int x, int y) {
return *grid[(y-y%10)/10][(x-x%10)/10];
}
