SRC=src/
BIN=bin/
LFLAGS= -Wall -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS= -v -Wall -ansi -pedantic

all: ManateeX

ManateeX: $(BIN)Particle.o $(BIN)Case.o $(BIN)Map.o $(BIN)Main.o
	g++ -o ManateeX $(BIN)Main.o $(BIN)Map.o $(BIN)Case.o $(BIN)Particle.o $(LFLAGS)

$(BIN)Main.o: $(SRC)Main.cxx
	g++ -o $(BIN)Main.o -c $(SRC)Main.cxx $(CFLAGS)

$(BIN)Map.o: $(SRC)Map.cxx $(SRC)Map.hxx $(BIN)Case.o
	g++ -o $(BIN)Map.o -c $(SRC)Map.cxx $(CFLAGS)

$(BIN)Case.o: $(SRC)Case.cxx $(SRC)Case.hxx 
	g++ -o $(BIN)Case.o -c $(SRC)Case.cxx $(CFLAGS)

$(BIN)Particle.o: $(SRC)Particle.cxx $(SRC)Particle.hxx 
	g++ -o $(BIN)Particle.o -c $(SRC)Particle.cxx $(CFLAGS)

