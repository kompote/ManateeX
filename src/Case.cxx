#include "Case.hxx"

Case::Case(int i) {
  texturePath = "src/ressources/images/blue.png";
  texture.LoadFromFile(texturePath);
  sprite.SetTexture(texture);
  number = i;
  SetConstructible(false);
}

void Case::setPosition(int x, int y) 
{
  transform.SetPosition(x,y);
}

void Case::draw(RenderTarget& target) const
{
  target.Draw(sprite,transform.GetTransform());
  
}

void Case::Select()
{
  sprite.SetColor(Color(0,255,0,255));
}

void Case::UnSelect()
{
  sprite.SetColor(Color(255,255,255,255));
}

bool Case::isConstructible() {
  return constructible;
}

void Case::SetConstructible(bool b) 
{
  constructible = b;
}

int Case::getContent() {
  return content;
}

string Case::getTexturePath() {
  return texturePath;
}

void Case::SetTexturePath(string path, bool cons) 
{

  SetConstructible(cons);
  texturePath = path;
  texture.LoadFromFile(texturePath);
  sprite.SetTexture(texture);
  cout<<"texture changed to "<<texturePath<<" for case n° "<<number<<endl;

}
