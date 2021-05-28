CXX = gcc
HEADERS = ./include
SRC = ./src
BIN = ./bin
OBJ = ./obj

pathfinding: main.o travelInfo.o pathStack.o pathHeap.o graph.o | $(OBJ) $(BIN)
	$(CXX) $(OBJ)/* -o $(BIN)/pathfinding

main.o: $(SRC)/main.c | $(OBJ)
	$(CXX) -c $(SRC)/main.c -I $(HEADERS) -o $(OBJ)/main.o

travelInfo.o: $(SRC)/travelInfo.c | $(OBJ)
	$(CXX) -c $(SRC)/travelInfo.c -I $(HEADERS) -o $(OBJ)/travelInfo.o

pathStack.o: $(SRC)/pathStack.c | $(OBJ)
	$(CXX) -c $(SRC)/pathStack.c -I $(HEADERS) -o $(OBJ)/pathStack.o

pathHeap.o: $(SRC)/pathHeap.c | $(OBJ)
	$(CXX) -c $(SRC)/pathHeap.c -I $(HEADERS) -o $(OBJ)/pathHeap.o

graph.o: $(SRC)/graph.c | $(OBJ)
	$(CXX) -c $(SRC)/graph.c -I $(HEADERS) -o $(OBJ)/graph.o

$(HEADERS):
	mkdir $(HEADERS)

$(SRC):
	mkdir $(SRC)

$(BIN):
	mkdir $(BIN)

$(OBJ):
	mkdir $(OBJ)
