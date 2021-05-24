CXX = gcc
HEADERS = ./include
SRC = ./src
BIN = ./bin
OBJ = ./obj

pathfinding: main.o | $(OBJ) $(BIN)
	$(CXX) $(OBJ)/* -o $(BIN)/pathfinding

main.o: $(SRC)/main.c | $(OBJ)
	$(CXX) -c $(SRC)/main.c -I $(HEADERS) -o $(OBJ)/main.o


$(HEADERS):
	mkdir $(HEADERS)

$(SRC):
	mkdir $(SRC)

$(BIN):
	mkdir $(BIN)

$(OBJ):
	mkdir $(OBJ)
