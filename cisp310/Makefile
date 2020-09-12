CXX = gcc
CXXFLAGS = -Wall -g
HEADERS = ./headers
SRC = ./src
BIN = ./bin
OBJ = ./obj

main: main.o baseConverter.o binary.o hexadecimal.o base.o | $(BIN)
	$(CXX) $(CXXFLAGS) -o $(BIN)/main $(OBJ)/*

main.o: $(SRC)/main.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/main.c -o $(OBJ)/main.o -I $(HEADERS)

baseConverter.o: $(SRC)/baseConverter.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/baseConverter.c -o $(OBJ)/baseConverter.o -I $(HEADERS)

binary.o: $(SRC)/binary.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/binary.c -o $(OBJ)/binary.o -I $(HEADERS)

hexadecimal.o: $(SRC)/hexadecimal.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/hexadecimal.c -o $(OBJ)/hexadecimal.o -I $(HEADERS)

base.o : $(SRC)/base.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $(SRC)/base.c -o $(OBJ)/base.o -I $(HEADERS)

$(BIN):
	mkdir $(BIN)

$(OBJ):
	mkdir $(OBJ)

clean:
	rm -r $(BIN)
	rm -r $(OBJ)
