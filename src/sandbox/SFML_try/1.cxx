#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream>
using namespace std;


using namespace sf;




int main()
{
  // Create the main window
  RenderWindow window(VideoMode(800, 600), "SFML window");
  // Load a sprite to display
  Texture texture;
  if (!texture.LoadFromFile("protoman.png"))
    return EXIT_FAILURE;
  Sprite sprite(texture);
  sprite.SetPosition(400,300);
  
  // Create a graphical text to display

  int sco = 0;

  
  Font font;
  if (!font.LoadFromFile("ARCADE_I.TTF"))
    return EXIT_FAILURE;
  Text text("0000", font, 25);
    /// Load a music to play
   Music music;
   if (!music.OpenFromFile("toto.ogg"))
     return EXIT_FAILURE;
   // Play the music
    music.Play();
  // Start the game loop
  bool sens=true;
  
  
  while (window.IsOpened())
    {


      //movement clavier fluide
      int x = 0;
      int y = 0;

      int spx = sprite.GetPosition().x;
      int spy = sprite.GetPosition().y;
      
      if ((spy>=0) &&(spy<=500) )
	{
	  
	  if (Keyboard::IsKeyPressed(Keyboard::Down)) y=15;
	  if (Keyboard::IsKeyPressed(Keyboard::Up)) y=-15;

	}

      
      if ((spy+y<0)||(spy+y>500)) y=0;

      
      //move auto (H)
      if (sens) {
	sprite.FlipX(true);
	
	if (sprite.GetPosition().x<700) x=3;
	else sens=!sens;

      }
      else 
	{
	  sprite.FlipX(false);
	  
	  if (sprite.GetPosition().x>0) x=-5;
	  else sens=!sens;
	}
      


      sprite.Move(x,y);


      // Process events
      Event event;
      while (window.PollEvent(event))
	{
	  // Window closed
	  if (event.Type == Event::Closed)
	    window.Close();

	  if (event.Type == Event::KeyPressed)
	    {
	      switch (event.Key.Code)
	  	{
	  	case Keyboard::Q : window.Close();
	  	  break;
			  
	  	}
	    }
	  
	  
	  // recupere coordonnees souri et bouge le sprite
	  if (event.Type == Event::MouseButtonPressed)
	    {
	      sco++;
	      //pour avoir un beau score sur 4 digits ^^
	      ostringstream oss;
	      if (sco < 10)
		oss << 0 << 0 << 0 <<sco ;
	      else if (sco<100)
		oss << 0 << 0 << sco;
	      else if (sco<1000)
		oss << 0 << sco;
	      else oss << sco;
	      
	      text.SetString( oss.str());
	      cout<<sco<<endl;
	      
	      
	      Vector2i position = Mouse::GetPosition(window);
	      int x = position.x;
	      int y = position.y;

	      
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
      window.Draw(text);
      // Update the window
      window.Display();
    }
  return EXIT_SUCCESS;
}
