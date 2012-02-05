all: menus

menus: main menu mainmenu options popup
	g++ Main.o Menu.o MainMenu.o OptionMenu.o PopupMenu.o -lsfml-graphics -lsfml-window -lsfml-system

main: Main.cxx MainMenu.hxx
	g++ -c Main.cxx

menu: Menu.cxx Menu.hxx
	g++ -c Menu.cxx

mainmenu: MainMenu.cxx MainMenu.hxx Menu.hxx
	g++ -c MainMenu.cxx

options: OptionMenu.cxx OptionMenu.hxx Menu.hxx
	g++ -c OptionMenu.cxx

popup: PopupMenu.cxx PopupMenu.hxx Menu.hxx
	g++ -c PopupMenu.cxx
