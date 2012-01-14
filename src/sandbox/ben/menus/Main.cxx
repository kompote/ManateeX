#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Menu.hxx"
#include "MainMenu.hxx"
#include "OptionMenu.hxx"

using namespace sf;

int main(void) {

    RenderWindow window(VideoMode(800, 600), "ManateeX Project");

    MainMenu mainMenu;
	OptionMenu optionMenu;
	Menu *currentMenu = &mainMenu;
    

    while(window.IsOpened()) {
		Event event;
		while (window.PollEvent(event)) {
			// Window closed
			if (event.Type == Event::Closed) window.Close();
			// Button clicked
			if (event.Type == Event::MouseButtonPressed) {
				for(int i=0;i<5;i++) {
					if(currentMenu->button[i].GetGlobalBounds().Contains(event.MouseButton.X,event.MouseButton.Y)) {
						if(currentMenu->button[i].GetString()=="Options") currentMenu = &optionMenu;
						if(currentMenu->button[i].GetString()=="Retour") currentMenu = &mainMenu;
						if(currentMenu->button[i].GetString()=="Quitter") window.Close();
					}
				}
			}
		}
		usleep(10000);
		// Update the window
		window.Clear();
		currentMenu->Affiche(window);
       	window.Display();
	}

	window.Clear();
	window.Close();

    return (EXIT_SUCCESS);
}
