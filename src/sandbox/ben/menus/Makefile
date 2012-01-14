all: menus

menus: main menu mainmenu options
	g++ Main.o Menu.o MainMenu.o OptionMenu.o -lsfml-graphics -lsfml-window -lsfml-system

main: Main.cxx MainMenu.hxx
	g++ -c Main.cxx

menu: Menu.cxx Menu.hxx
	g++ -c Menu.cxx

mainmenu: MainMenu.cxx MainMenu.hxx Menu.hxx
	g++ -c MainMenu.cxx

options: OptionMenu.cxx OptionMenu.hxx Menu.hxx
	g++ -c OptionMenu.cxx
