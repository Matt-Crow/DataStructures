#include <iostream>

void initTable(bool table[1024][10]);
bool isRowSat(bool row[10]);
void printRow(bool row[10]);

using namespace std;

int main(){
    bool table[1024][10];

    initTable(table);

    for(int i = 0; i < 1024; i++){
        if(isRowSat(table[i])){
            printRow(table[i]);
        }
    }
    return 0;
}

void initTable(bool table[1024][10]){
    bool nextSymbol;
    int switchingPoint = 1024 / 2;

    for(int col = 0; col < 10; col++){
        nextSymbol = true;
        for(int row = 0; row < 1024; row++){
            if(row % switchingPoint == 0 && row != 0){
                nextSymbol = !nextSymbol;
            }
            table[row][col] = nextSymbol;
        }
        switchingPoint /= 2;
    }
}
bool isRowSat(bool row[10]){
    return true;
}
void printRow(bool row[10]){
    for(int i = 0; i < 10; i++){
        cout << ((row[i]) ? 'T' : 'F') << ' ';
    }
    cout << endl;
}
