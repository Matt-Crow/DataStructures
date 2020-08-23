CXX = gcc
CXXFLAGS = -Wall -g
HEADERS = ./headers
SRC = ./src
BIN = ./bin
OBJ = ./obj

main: main.o radixPrioritySort.o | $(BIN)
	$(CXX) $(CXXFLAGS) -o $(BIN)/main $(OBJ)/*

main.o: $(SRC)/main.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/main.c -o $(OBJ)/main.o -I $(HEADERS)

radixPrioritySort.o: $(SRC)/radixPrioritySort.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/radixPrioritySort.c -o $(OBJ)/radixPrioritySort.o -I $(HEADERS)


$(BIN):
	mkdir $(BIN)

$(OBJ):
	mkdir $(OBJ)

clean:
	rm -r $(BIN)
	rm -r $(OBJ)
