CXX = gcc
CXXFLAGS = -Wall -g
HEADERS = ./headers
SRC = ./src
BIN = ./bin
OBJ = ./obj

$(BIN)/main: main.o radixPrioritySort.o sorting.o util.o | $(BIN)
	$(CXX) $(CXXFLAGS) -o $(BIN)/main $(OBJ)/*

main.o: $(SRC)/main.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/main.c -o $(OBJ)/main.o -I $(HEADERS)

radixPrioritySort.o: $(SRC)/radixPrioritySort.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/radixPrioritySort.c -o $(OBJ)/radixPrioritySort.o -I $(HEADERS)

sorting.o: $(SRC)/sorting.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/sorting.c -o $(OBJ)/sorting.o -I $(HEADERS)

util.o: $(SRC)/util.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/util.c -o $(OBJ)/util.o -I $(HEADERS)


$(BIN):
	mkdir $(BIN)

$(OBJ):
	mkdir $(OBJ)

clean:
	rm -r $(BIN)
	rm -r $(OBJ)
