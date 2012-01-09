#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "MainMenu.hxx"

using namespace sf;

int main(void) {

    RenderWindow window(VideoMode(800, 600), "ManateeX Project");

    MainMenu menuPrincipal;

    

    while(window.IsOpened()) {
	Event event;
	while (window.PollEvent(event)) {
	  	// Window closed
	  	if (event.Type == Event::Closed) window.Close();
	}
	usleep(10000);
      	// Update the window
		window.Clear();
		menuPrincipal.Affiche(window);
      	window.Display();
	}

	window.Clear();
	window.Close();

    return (EXIT_SUCCESS);
}

