#include <iostream>
#include <math.h>

#define COLS 4
#define ROWS (int)std::pow(2, COLS)

void initTable(bool table[ROWS][COLS]);
bool isRowSat(bool row[COLS]);
void printRow(bool row[COLS]);

using namespace std;

int main(){
    bool table[ROWS][COLS];

    initTable(table);

    for(int i = 0; i < ROWS; i++){
        if(isRowSat(table[i])){
            printRow(table[i]);
        }
    }
    return 0;
}

void initTable(bool table[ROWS][COLS]){
    bool nextSymbol;
    int switchingPoint = ROWS / 2;

    for(int col = 0; col < COLS; col++){
        nextSymbol = true;
        for(int row = 0; row < ROWS; row++){
            if(row % switchingPoint == 0 && row != 0){
                nextSymbol = !nextSymbol;
            }
            table[row][col] = nextSymbol;
        }
        switchingPoint /= 2;
    }
}
bool isRowSat(bool row[COLS]){
    return true;
}
void printRow(bool row[COLS]){
    for(int i = 0; i < COLS; i++){
        cout << ((row[i]) ? 'T' : 'F') << ' ';
    }
    cout << endl;
}
