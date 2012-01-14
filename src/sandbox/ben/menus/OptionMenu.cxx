#include "OptionMenu.hxx"

OptionMenu::OptionMenu() {
	
	font.LoadFromFile("/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf");
	
	title.SetString("Options");
	title.SetFont(font);
	title.SetCharacterSize(60);
	title.SetPosition(400-title.GetGlobalBounds().Width/2,20);
	title.SetColor(Color::Black);
}

void OptionMenu::Affiche(RenderTarget& target) const {
    target.Draw(bgSprite);
	target.Draw(title);
}
