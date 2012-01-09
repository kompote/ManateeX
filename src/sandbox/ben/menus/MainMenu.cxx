#include "MainMenu.hxx"

MainMenu::MainMenu() {
    imgfond.LoadFromFile("fondmenu.png");

    background.SetTexture(imgfond);
    background.SetPosition(0,0);
}

void MainMenu::Affiche(RenderTarget& target) const {
    target.Draw(background);  
}
