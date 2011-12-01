#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;


int main()
{
  // Create the main window
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
  // Load a sprite to display
  sf::Texture texture;
  if (!texture.LoadFromFile("protoman.png"))
    return EXIT_FAILURE;
  sf::Sprite sprite(texture);
  // Create a graphical text to display
  sf::Font font;
  if (!font.LoadFromFile("FreeMono.ttf"))
    return EXIT_FAILURE;
  //  sf::Text text("Hello SFML", font, 50);
  // Load a music to play
  // sf::Music music;
  // if (!music.OpenFromFile("toto.ogg"))
  //   return EXIT_FAILURE;
   // Play the music
  //  music.Play();
  // Start the game loop

  
  while (window.IsOpened())
    {
      // Process events
      sf::Event event;
      while (window.PollEvent(event))
	{
	  // Window closed
	  if (event.Type == sf::Event::Closed)
	    window.Close();
	  // q key pressed
	  if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Keyboard::Q))
	    window.Close();
	  
	  // recupere coordonnees souri et bouge le sprite
	  if (event.Type == sf::Event::MouseButtonPressed)
	    {
	      sf::Vector2i position = sf::Mouse::GetPosition(window);
	      int x = position.x;
	      int y = position.y;
	      cout<<x<<","<<y<<endl;
	      sprite.SetPosition(x,y);
	    }
	}

      // une pause c'est mieux
      usleep(10000);
      // Clear screen
      window.Clear();
      // Draw the sprite
      window.Draw(sprite);
      // Draw the string
      //  window.Draw(text);
      // Update the window
      window.Display();
    }
  return EXIT_SUCCESS;
}
