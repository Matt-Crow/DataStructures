CXX = g++
CXXFLAGS = -Wall -g
HEADERS = ./headers
SRC = ./src
BIN = ./bin
OBJ = ./obj

main: main.o stack.o queue.o | $(BIN)
	$(CXX) $(CXXFLAGS) -o $(BIN)/main $(OBJ)/*

main.o: $(SRC)/main.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/main.cpp -o $(OBJ)/main.o -I $(HEADERS)

stack.o: $(SRC)/stack.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/stack.cpp -o $(OBJ)/stack.o -I $(HEADERS)

queue.o: $(SRC)/queue.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/queue.cpp -o $(OBJ)/queue.o -I $(HEADERS)

$(BIN):
	mkdir $(BIN)

$(OBJ):
	mkdir $(OBJ)

clean:
	rm -r $(BIN)
	rm -r $(OBJ)
