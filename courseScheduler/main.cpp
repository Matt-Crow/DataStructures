#include <iostream>
#include <math.h>

//Don't change these, as the assignment requires specific values
#define CLASS_COUNT 5
#define COLS CLASS_COUNT * 2
#define ROWS (int)std::pow(2, COLS)

void initTable(bool table[ROWS][COLS]);
bool isRowSat(bool row[COLS]);
void printRow(bool row[COLS]);

using namespace std;

int main()
{
    bool table[ROWS][COLS];

    initTable(table);

    for(int i = 0; i < ROWS; i++)
    {
        if(isRowSat(table[i]))
        {
            printRow(table[i]);
        }
    }
    return 0;
}

void initTable(bool table[ROWS][COLS])
{
    bool nextSymbol;
    int switchingPoint = ROWS / 2;

    for(int col = 0; col < COLS; col++)
    {
        nextSymbol = true;
        for(int row = 0; row < ROWS; row++)
        {
            if(row % switchingPoint == 0 && row != 0)
            {
                nextSymbol = !nextSymbol;
            }
            table[row][col] = nextSymbol;
        }
        switchingPoint /= 2;
    }
}
bool isRowSat(bool row[COLS])
{
    //cannot be in the same class room: (A, B), (B, E), (D, C), (C, E)
    //DeMorgan's Law makes this so much faster
    bool satisfiable = !(
        (row[0] && row[2])
        || (row[1] && row[3])
        || (row[2] && row[8])
        || (row[3] && row[9])
        || (row[4] && row[6])
        || (row[5] && row[7])
        || (row[4] && row[8])
        || (row[5] && row[9])
    );
    for(int col = 0; col < COLS && satisfiable; col += 2)
    {
        //since column x signifies the class will be room 1,
        //and x + 1 signifies the class will be in room 2...
        //             in at least 1 room           not in multiple
        satisfiable = (row[col] || row[col + 1]) && !(row[col] && row[col + 1]);
        //these are technically && together, as the loop will exit once it evaluates to false
    }
    return satisfiable;
}
void printRow(bool row[COLS])
{
    for(int i = 0; i < COLS; i++)
    {
        cout << ((row[i]) ? 'T' : 'F') << ' ';
    }
    cout << endl;
}
