SRC=src/
BIN=bin/
LFLAGS= -Wall -lsfml-graphics -lsfml-window
CFLAGS= -Wall -ansi -pedantic

all: ManateeX

ManateeX: $(BIN)Proj.o $(BIN)Mob.o $(BIN)Case.o $(BIN)Map.o $(BIN)Main.o
	g++ -o ManateeX $(BIN)Main.o $(BIN)Map.o $(BIN)Case.o $(BIN)Mob.o $(BIN)Proj.o $(LFLAGS)

$(BIN)Main.o: $(SRC)Main.cxx $(BIN)Map.o $(BIN)Case.o $(BIN)Mob.o $(BIN)Proj.o
	g++ -o $(BIN)Main.o -c $(SRC)Main.cxx $(CFLAGS)

$(BIN)Map.o: $(SRC)Map.cxx $(SRC)Map.hxx $(BIN)Case.o
	g++ -o $(BIN)Map.o -c $(SRC)Map.cxx $(CFLAGS)

$(BIN)Case.o: $(SRC)Case.cxx $(SRC)Case.hxx 
	g++ -o $(BIN)Case.o -c $(SRC)Case.cxx $(CFLAGS)

$(BIN)Mob.o: $(SRC)Mob.cxx $(SRC)Mob.hxx 
	g++ -o $(BIN)Mob.o -c $(SRC)Mob.cxx $(CFLAGS)

$(BIN)Proj.o: $(SRC)Proj.cxx $(SRC)Proj.hxx
	g++ -o $(BIN)Proj.o -c $(SRC)Proj.cxx $(CFLAGS)

