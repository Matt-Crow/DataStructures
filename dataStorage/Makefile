CXX = gcc
CXXFLAGS = -Wall -g
HEADERS = ./headers
SRC = ./src
BIN = ./bin
OBJ = ./obj

main: main.o stack.o queue.o linkedList.o tree.o hashArray.o | $(BIN)
	$(CXX) $(CXXFLAGS) -o $(BIN)/main $(OBJ)/*

main.o: $(SRC)/main.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/main.c -o $(OBJ)/main.o -I $(HEADERS)

stack.o: $(SRC)/stack.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/stack.c -o $(OBJ)/stack.o -I $(HEADERS)

queue.o: $(SRC)/queue.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/queue.c -o $(OBJ)/queue.o -I $(HEADERS)

linkedList.o: $(SRC)/linkedList.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/linkedList.c -o $(OBJ)/linkedList.o -I $(HEADERS)

tree.o: $(SRC)/tree.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/tree.c -o $(OBJ)/tree.o -I $(HEADERS)

hashArray.o: $(SRC)/hashArray.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/hashArray.c -o $(OBJ)/hashArray.o -I $(HEADERS)


$(BIN):
	mkdir $(BIN)

$(OBJ):
	mkdir $(OBJ)

clean:
	rm -r $(BIN)
	rm -r $(OBJ)
