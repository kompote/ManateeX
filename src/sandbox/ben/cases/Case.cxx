#include "Case.hxx"

Case::Case() {texturePath="texture.png";}

bool Case::isConstructible() {
return constructible;
}

int Case::getContent() {
return content;
}

string Case::getTexturePath() {
return texturePath;
}
