#include "Map.hxx"

Map::Map() {
  int z =0;
  
  for(int i=0;i<60;i++)
    for(int j=0;j<80;j++) 
      {
	grid[i][j] = new Case(z);	
	grid[i][j]->setPosition(j*10,i*10);
	z++;
	      
      }
  lastSelected = NULL;
  
}
void Map::Redraw(RenderTarget& target) const 
{
  for(int i=0;i<60;i++)
    for(int j=0;j<80;j++) 
      {
	grid[i][j]->draw(target);
      }

}


Case* Map::getCase(int i, int j) {
  return grid[j][i];
}

Case* Map::getCasePixel(int x, int y) {
  return grid[(y-y%10)/10][(x-x%10)/10];
}

void Map::Select(Case* s) 
{
  if (lastSelected)
    lastSelected->UnSelect();
  
  s->Select();
  lastSelected = s;
  

}
