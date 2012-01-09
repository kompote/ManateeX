all: menus

menus: main mainmenu
	g++ Main.o MainMenu.o -lsfml-graphics -lsfml-window

main: Main.cxx MainMenu.hxx
	g++ -c Main.cxx

mainmenu: MainMenu.cxx MainMenu.hxx
	g++ -c MainMenu.cxx
