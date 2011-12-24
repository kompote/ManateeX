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
  window.Display();

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

  Case* last = NULL;
  
  
  while(window.IsOpened()) {
    Event event;
    while (window.PollEvent(event)) {

      if (event.Type == Event::Closed) window.Close();

      if (event.Type == Event::MouseButtonReleased) 
	{
	  // Select case
	  cout<<"catching mouse event\033[32m"<<endl;
	  Vector2i pos = Mouse::GetPosition(window);
	  x = pos.x;
	  y = pos.y;
	  std::cout<<"("<<pos.x<<":"<<pos.y<<")"<<endl;
	  Case* tmp = m.getCasePixel(pos.x,pos.y);
	  std::cout<<"case n° "<<tmp->number<<" selected"<<endl;
	  tmp->Select();
	  if (last)
	    last->UnSelect();
	  last = tmp;
	  
	  // si click droit
	  if (event.MouseButton.Button == Mouse::Right) 
	    {
	      cout<<"menu contex"<<endl;

	    }
	  
	  
	  //si click gauche
	  if (event.MouseButton.Button == Mouse::Left)
	    {
	      cout<<"information on case n° "<<tmp->number<<endl;
	      Color cl = tmp->sprite.GetColor();
	      cout<<(int)cl.r<<" "<<(int)cl.g<<" "<<(int)cl.b<<" "<<(int)cl.a<<endl;
	  	      // Bonus
	      //	      enn.Move(x,y);
	    }
	  
	  cout<<"\033[0mReprise event watch"<<endl;
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


