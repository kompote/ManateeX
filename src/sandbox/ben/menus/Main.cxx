#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Menu.hxx"
#include "MainMenu.hxx"
#include "OptionMenu.hxx"
#include "PopupMenu.hxx"

using namespace sf;

int main(void) {

    RenderWindow window(VideoMode(800, 600), "ManateeX Project");

    MainMenu mainMenu;
	OptionMenu optionMenu;
	Menu *currentMenu = &mainMenu;
	PopupMenu popup(0,0);
	bool isPopped = false;
    
	while(window.IsOpen()) {
		Event event;
		while (window.PollEvent(event)) {
			// Window closed
			if (event.Type == Event::Closed) window.Close();
			// Button clicked
			if (event.Type == Event::MouseButtonPressed) {
				// Left click
				if(event.MouseButton.Button == Mouse::Left) {
					
					// If popup menu button clicked
					for(int i=0;i<5;i++) {
						if(popup.button[i].GetGlobalBounds().Contains(event.MouseButton.X,event.MouseButton.Y)) {
							if(popup.button[i].GetString()=="Options") currentMenu = &optionMenu;
							if(popup.button[i].GetString()=="Retour") currentMenu = &mainMenu;
							if(popup.button[i].GetString()=="Quitter") window.Close();
						}
					}
					
					// If menu button clicked
					for(int i=0;i<5;i++) {
						if(currentMenu->button[i].GetGlobalBounds().Contains(event.MouseButton.X,event.MouseButton.Y)) {
							if(currentMenu->button[i].GetString()=="Options") currentMenu = &optionMenu;
							if(currentMenu->button[i].GetString()=="Retour") currentMenu = &mainMenu;
							if(currentMenu->button[i].GetString()=="Quitter") window.Close();
						}
					}

					isPopped=false;
				}
				//Right click
				else if(event.MouseButton.Button == Mouse::Right) {
					popup.setPosition(event.MouseButton.X,event.MouseButton.Y);
					isPopped = true ;
				}
			}
		}
		usleep(10000);
		// Update the window
		window.Clear();
		currentMenu->Affiche(window);
		if(isPopped) popup.Affiche(window);
       	window.Display();
	}

	window.Clear();
	window.Close();

    return (EXIT_SUCCESS);
}
