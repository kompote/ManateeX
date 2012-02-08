#include "Map.hxx"

Map::Map() {
  int z =0;
  
  for(int i=0;i<57;i++)
    for(int j=0;j<80;j++) 
      {
	_grid[i][j] = new Square(z);	
	_grid[i][j]->SetPosition(j*10,i*10+30);
	z++;
	//	std::cout<<j<<":"<<i<<std::endl;
	
      }
  _lastSelected = NULL;
  
}

void Map::Redraw(RenderTarget& target) const 
{
  for(int i=0;i<57;i++)
    for(int j=0;j<80;j++) 
      {
	_grid[i][j]->Draw(target);
      }

}

Square* Map::GetSquare(int i, int j) {
  return _grid[j][i];
}

Square* Map::GetSquarePixel(int x, int y) {
  return _grid[((y-30)-y%10)/10][(x-x%10)/10];
}

void Map::Select(Square* s) 
{
  if (_lastSelected)
    _lastSelected->UnSelect();
  
  s->Select();
  _lastSelected = s;
}
