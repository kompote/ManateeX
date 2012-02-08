#include "Square.hxx"

Square::Square(int i) {
  _texturePath = "src/ressources/images/blue.png";
  _texture.LoadFromFile(_texturePath);
  sprite.SetTexture(_texture);
  number = i;
  SetConstructible(false);
  sprite.SetColor(Color(100,100,100,255));
}

void Square::SetPosition(int x, int y) 
{
  _transform.SetPosition(x,y);
}

void Square::Draw(RenderTarget& target) const
{
  target.Draw(sprite,_transform.GetTransform());
  
}

void Square::Select()
{
  sprite.SetColor(Color(0,255,0,255));
}

void Square::UnSelect()
{
  sprite.SetColor(Color(100,100,100,255));
  //  sprite.SetColor(Color(255,255,255,255));
}

bool Square::IsConstructible() {
  return _free;
}

void Square::SetConstructible(bool b) 
{
  _free = b;
}

int Square::GetContent() {
  return _content;
}

string Square::GetTexturePath() {
  return _texturePath;
}

void Square::SetTexturePath(string path, bool cons) 
{

  SetConstructible(cons);
  _texturePath = path;
  _texture.LoadFromFile(_texturePath);
  sprite.SetTexture(_texture);
  cout<<"texture changed to "<<_texturePath<<" for case n° "<<number<<endl;

}
