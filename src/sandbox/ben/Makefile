all: test

test: main map case
	g++ -o test Main.o Map.o Case.o -lsfml-graphics -lsfml-window

main: Main.cxx Map.hxx
	g++ -c Main.cxx

map: Map.cxx Map.hxx Case.hxx
	g++ -c Map.cxx

case: Case.cxx Case.hxx
	g++ -c Case.cxx
