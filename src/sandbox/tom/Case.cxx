#include "Case.hxx"

Case::Case(int i) {
  texturePath = "texture.png";
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
