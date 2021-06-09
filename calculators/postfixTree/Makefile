CXX = gcc

BIN = ./bin
OBJ = ./obj
INC = ./include
SRC = ./src

calculator : main.o parser.o evaluator.o common.o | $(BIN)
	gcc $(OBJ)/* -o $(BIN)/calculator

main.o : $(SRC)/main.c | $(OBJ)
	gcc -c $(SRC)/main.c -I $(INC) -o $(OBJ)/main.o

parser.o : $(SRC)/parser.c | $(OBJ)
	gcc -c $(SRC)/parser.c -I $(INC) -o $(OBJ)/parser.o

evaluator.o : $(SRC)/evaluator.c | $(OBJ)
	gcc -c $(SRC)/evaluator.c -I $(INC) -o $(OBJ)/evaluator.o

common.o : $(SRC)/common.c | $(OBJ)
	gcc -c $(SRC)/common.c -I $(INC) -o $(OBJ)/common.o

$(BIN) :
	mkdir $(BIN)

$(OBJ) :
	mkdir $(OBJ)

clean :
	rm -r $(BIN)
	rm -r $(OBJ)
