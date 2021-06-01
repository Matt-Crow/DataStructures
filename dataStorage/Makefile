CXX = gcc
CXXFLAGS = -Wall -g
HEADERS = ./headers
SRC = ./src
BIN = ./bin
OBJ = ./obj

main: main.o stack.o queue.o linkedList.o tree.o avlTree.o hashArray.o heap.o linkedHashTable.o core.o | $(BIN)
	$(CXX) $(CXXFLAGS) -o $(BIN)/main $(OBJ)/*

core.o: $(SRC)/main.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/core.c -o $(OBJ)/core.o -I $(HEADERS)

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

avlTree.o: $(SRC)/avlTree.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/avlTree.c -o $(OBJ)/avlTree.o -I $(HEADERS)

hashArray.o: $(SRC)/hashArray.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/hashArray.c -o $(OBJ)/hashArray.o -I $(HEADERS)

heap.o: $(SRC)/heap.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/heap.c -o $(OBJ)/heap.o -I $(HEADERS)

linkedHashTable.o: $(SRC)/linkedHashTable.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/linkedHashTable.c -o $(OBJ)/linkedHashTable.o -I $(HEADERS)

$(BIN):
	mkdir $(BIN)

$(OBJ):
	mkdir $(OBJ)

clean:
	rm -r $(BIN)
	rm -r $(OBJ)
