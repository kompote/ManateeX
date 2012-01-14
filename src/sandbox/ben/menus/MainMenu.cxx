#include "MainMenu.hxx"

MainMenu::MainMenu() {

	font.LoadFromFile("/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf");
	
	title.SetString("ManateeX Project");
	title.SetFont(font);
	title.SetCharacterSize(60);
	title.SetPosition(400-title.GetGlobalBounds().Width/2,20);
	title.SetColor(Color::Black);
}

void MainMenu::Affiche(RenderTarget& target) const {
    target.Draw(bgSprite);
	target.Draw(title);
}
