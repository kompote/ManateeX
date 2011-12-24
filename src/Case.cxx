#include "Case.hxx"

Case::Case(int i) {
  texturePath = "src/ressources/images/blue.png";
  texture.LoadFromFile(texturePath);
  sprite.SetTexture(texture);

  
  number = i;
  SetConstructible(false);
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

void Case::Select()
{
  sprite.SetColor(Color(0,255,0,255));
  cout<<number<<" selected"<<endl;
}

void Case::UnSelect()
{
  sprite.SetColor(Color(255,255,255,255));
}


// change le sprite de la case + est constructible ou non

void Case::SetTexturePath(string path, bool cons) 
{

  SetConstructible(true);
  texturePath = path;
  texture.LoadFromFile(texturePath);
  sprite.SetTexture(texture);
  cout<<"texture changed to "<<texturePath<<" for case n° "<<number<<endl;

}
