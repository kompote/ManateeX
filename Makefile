SRC=src/
BIN=bin/
LFLAGS= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS= -ansi -pedantic

all: ManateeX

ManateeX: $(BIN)Particle.o $(BIN)Square.o $(BIN)Map.o $(BIN)Main.o $(BIN)Menu.o $(BIN)MainMenu.o $(BIN)OptionMenu.o $(BIN)PopupMenu.o $(BIN)Mob.o $(BIN)Building.o $(BIN)Tower.o $(BIN)Target.o
	g++ -o ManateeX $(BIN)Main.o $(BIN)Map.o $(BIN)Square.o $(BIN)Particle.o $(BIN)Menu.o $(BIN)MainMenu.o $(BIN)OptionMenu.o $(BIN)PopupMenu.o $(BIN)Mob.o $(BIN)Building.o $(BIN)Tower.o $(BIN)Target.o $(LFLAGS)

$(BIN)Main.o: $(SRC)Main.cxx
	g++ -o $(BIN)Main.o -c $(SRC)Main.cxx $(CFLAGS)

$(BIN)Map.o: $(SRC)Map.cxx $(SRC)Map.hxx
	g++ -o $(BIN)Map.o -c $(SRC)Map.cxx $(CFLAGS)

$(BIN)Square.o: $(SRC)Square.cxx $(SRC)Square.hxx 
	g++ -o $(BIN)Square.o -c $(SRC)Square.cxx $(CFLAGS)

$(BIN)Particle.o: $(SRC)Particle.cxx $(SRC)Particle.hxx 
	g++ -o $(BIN)Particle.o -c $(SRC)Particle.cxx $(CFLAGS)

$(BIN)Menu.o: $(SRC)Menu.cxx $(SRC)Menu.hxx 
	g++ -o $(BIN)Menu.o -c $(SRC)Menu.cxx $(CFLAGS)

$(BIN)Mob.o: $(SRC)Mob.cxx $(SRC)Mob.hxx 
	g++ -o $(BIN)Mob.o -c $(SRC)Mob.cxx $(CFLAGS)

$(BIN)Building.o: $(SRC)Building.cxx $(SRC)Building.hxx
	g++ -o $(BIN)Building.o -c $(SRC)Building.cxx $(CFLAGS)

$(BIN)Tower.o: $(SRC)Tower.cxx $(SRC)Tower.hxx 
	g++ -o $(BIN)Tower.o -c $(SRC)Tower.cxx $(CFLAGS)

$(BIN)MainMenu.o: $(SRC)MainMenu.cxx $(SRC)MainMenu.hxx 
	g++ -o $(BIN)MainMenu.o -c $(SRC)MainMenu.cxx $(CFLAGS)

$(BIN)OptionMenu.o: $(SRC)OptionMenu.cxx $(SRC)OptionMenu.hxx 
	g++ -o $(BIN)OptionMenu.o -c $(SRC)OptionMenu.cxx $(CFLAGS)

$(BIN)PopupMenu.o: $(SRC)PopupMenu.cxx $(SRC)PopupMenu.hxx 
	g++ -o $(BIN)PopupMenu.o -c $(SRC)PopupMenu.cxx $(CFLAGS)

$(BIN)Target.o: $(SRC)Target.cxx $(SRC)Target.hxx 
	g++ -o $(BIN)Target.o -c $(SRC)Target.cxx $(CFLAGS)
