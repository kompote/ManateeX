#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Map.hxx"
#include "Particle.hxx"

using namespace sf;

RenderWindow window(VideoMode(800, 600), "SFML window");
Particle p(window);

void updatePos() 
{
  std::cout<<"update"<<std::endl;
  while(42) 
    {
      p.update();
      usleep(1000);
    }
}


int main (void) {
  
  Map m;
  int x,y;

  Thread tt(&updatePos);


  tt.Launch();
  
  while(window.IsOpen()) {
    Event event;
    m.Redraw(window);
    p.render();
    
    while (window.PollEvent(event)) {
      // Window closed
      if (event.Type == Event::Closed) window.Close();

      if (event.Type == Event::MouseButtonReleased) 
	{

	  Vector2i pos = Mouse::GetPosition(window);
	  x = pos.x;
	  y = pos.y;
	  p.Bresenham(x,y);
	  std::cout<<"("<<pos.x<<":"<<pos.y<<")"<<endl;
	  Case* tmp = m.getCasePixel(pos.x,pos.y);
	  std::cout<<"case n° "<<tmp->number<<endl;

	  m.Select(tmp);
	}

      if (event.Type == Event::KeyPressed) 
	{
	  switch(event.Key.Code)
	    {
	    case Keyboard::I:

	      break;
	     
	    case Keyboard::M:

	      
	      break;
	     }

	}

    }

    usleep(20000);

    window.Display();
  }
}
