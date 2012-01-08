#include "Case.hxx"

Case::Case(int i) {
  //  Image im;
  texture.Create(10,10);
  sprite.SetTexture(texture);

  texturePath = "src/ressources/images/blue.png";
  im.LoadFromFile(texturePath);
  texture.Update(im);

  number = i;
  SetConstructible(true);
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
}

void Case::UnSelect()
{
  sprite.SetColor(Color(255,255,255,255));
}


// change le sprite de la case + est constructible ou non

void Case::SetTexturePath(string path, bool cons) 
{

  SetConstructible(cons);

  texturePath = path;
  im.LoadFromFile(texturePath);
  
  
  texture.Update(im);
  
  cout<<"texture changed to "<<texturePath<<" for case n° "<<number<<endl;
}
