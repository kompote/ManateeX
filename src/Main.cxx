#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Map.hxx"
#include "Case.hxx"
#include "Mob.hxx"

using namespace sf;


Map m;
Mob enn(1000,234,456);
bool run = true;
RenderWindow window;

void disp() 
{

  window.Create(VideoMode(800, 600), "SFML window");
  cout<<"test"<<endl;  
  window.Display();
  cout<<"test"<<endl;
  while(run)
    {

      for(int i=0;i<60;i++) {
	for(int j=0;j<80;j++) {
	  Case* tmp = m.getCase(j,i);
	  window.Draw(tmp->sprite);
	}
      }
      window.Draw(enn.SpriteMob);
      
      // Update the window
      window.Display();

      usleep(10000);
    }
}



int main (void) {


  int x,y;

	
  Thread ttt(&disp);
  ttt.Launch();
  usleep(50000);
  
  cout<<window.IsOpened()<<endl;

  while(window.IsOpened()) {
    Event event;
    while (window.PollEvent(event)) {

      if (event.Type == Event::Closed) window.Close();

      if (event.Type == Event::MouseButtonReleased) 
	{
	  cout<<"catching mouse event"<<endl;
	  
	  // change le sprite
	  Vector2i pos = Mouse::GetPosition(window);
	  x = pos.x;
	  y = pos.y;
			    
	  std::cout<<"("<<pos.x<<":"<<pos.y<<")"<<endl;
	  Case* tmp = m.getCasePixel(pos.x,pos.y);
	  std::cout<<"case n° "<<tmp->number<<endl;
	  tmp->SetTexturePath("src/ressources/images/blue.png",true);
	  enn.Move(x,y);
	  cout<<"Reprise Event watch"<<endl;
	  
	  
	}
      if (event.Type == Event::KeyPressed) 
	{
	  switch(event.Key.Code)
	    {
	      // info sur la derniere case selectionnee (debug)
	    case Keyboard::I:
	      Case* tmp2 = m.getCasePixel(x,y);
	      std::cout<<tmp2->getTexturePath()<<" for case n° "<<tmp2->number<<" "<<tmp2->isConstructible()<<endl;
	      if (tmp2->isConstructible()) 
		std::cout<<"true"<<endl;
				
	      break;
	    }
	}

    }


    usleep(20000);

  }
  run = false;
  
}


