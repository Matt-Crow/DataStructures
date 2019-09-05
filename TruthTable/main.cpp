#include <iostream>
#include <iomanip>
#include "parser.h"
using namespace std;

#define MAX_ROWS 8
#define MAX_COLS 10

const bool DEBUG = true;

void printTable(string symbols[], bool table[MAX_ROWS][MAX_COLS], int numProps);


///Initialize the table for all possible truth values of p, q, and r
///Give each symbol its own column, as we have done in class
///You can assign truth values manually or use nested loops.  I used a triple nested loop.
///returns the number of columns currently in the table (3)
int initTable(string symbols[], bool table[MAX_ROWS][MAX_COLS])
{
    symbols[0] = "p";
    symbols[1] = "q";
    symbols[2] = "r";

    ///assign table
    //begin Matt's code
    bool vals[] = {true, false};


    //this doesn't work
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++){
                table[j][i] = vals[k];
            }
        }
    }

    //try this instead?
    bool currVals[] = {true, true, true};
    for(int row = 0; row < 8; row++){

    }


    if(DEBUG){
        printTable(symbols, table, 3);
        cout << endl << "Table has inited" << endl;
    }

    //end Matt's code
    return 3;
}

///output the contents of the table with number of columns equal to numProps
///the table should contain p, q, r, each hypothesis, and the conclusion in the last column
///I would recommend using cout << setw(symbols[j].size() + 2) to set the width of each column
void printTable(string symbols[], bool table[MAX_ROWS][MAX_COLS], int numProps)
{
    //begin Matt's code
    for(int i = 0; i < numProps; i++){
        cout << setw(symbols[i].size() + 1) << symbols[i];
        if(i == numProps - 1){
            cout << endl;
        }else{
            cout << "|";
        }
    }
    for(int row = 0; row < MAX_ROWS; row++){
        for(int col = 0; col < numProps; col++){
            cout << setw(symbols[col].size() + 1) << ((table[row][col]) ? "T" : "F");
            if(col == numProps - 1){
                cout << endl;
            } else {
                cout << "|";
            }
        }
    }

    if(DEBUG){
        return;
        cout << endl;
        cout << numProps << endl;
        for(int i = 0; i < MAX_ROWS; i++){
            for(int j = 0; j < numProps; j++){
                cout << i << "," << j << ": " << ((table[i][j]) ? "T" : "F") << endl;
            }
        }
    }

    //end Matt's code
}

///Append a new column to the table.  Returns the new total number of columns.
///Assign the statement to the next column in symbols to act as a column header
///loop through each row and plug the current row's values for p, q, and r into evaluate
///Assign the return value from evaluate to the corresponding new cell in the table
int appendColumn(string statement, string symbols[], bool table[MAX_ROWS][MAX_COLS], int numProps)
{
    ///fill in the column header and truth values

    numProps++;
    return numProps;
}

///Determine if the argument represented by the truth table is valid or invalid
///As described in class, an argument is valid if when all the hypotheses are true, the conclusion is also true
///If there is a case where each hypothesis is true but the conclusion is false, the argument is invalid
///Use nested loops to examine each row.  If you find a row where all hypotheses are T and conclusion is F, return false
///If your code makes it through the loop without returning false, then return true
bool isValid(bool table[MAX_ROWS][MAX_COLS], int numProps)
{
    //begin Matt's code
    return false;
    //end Matt's code
}

///This one is done, no need to change it.
void printro()
{
    cout << "Welcome to the truth table generator" << endl;
    cout << "Valid symbols are p, q, and r" << endl;
    cout << "Valid operators are \\/, /\\, ~, =>, and <=>" << endl;
    cout << "Whitespace is ignored" << endl;
    cout << "Example:  (p \\/ q) => r" << endl;
}

///main is done, no changes needed.
int main()
{
    bool table[MAX_ROWS][MAX_COLS];
    string symbols[MAX_COLS];

    int numProps = initTable(symbols, table);

    printro();

    string statement = "";
    cout << "Enter a hypothesis or type \"therefore\" when done: ";
    getline(cin, statement);

    while(statement != "therefore")
    {
        numProps = appendColumn(statement, symbols, table, numProps);
        printTable(symbols, table, numProps);
        cout << "Enter a hypothesis or type \"therefore\" when done: ";
        getline(cin, statement);
    }

    cout << "Enter the conclusion: ";
    getline(cin, statement);
    numProps = appendColumn(statement, symbols, table, numProps);
    printTable(symbols, table, numProps);

    bool valid = isValid(table, numProps);
    if(valid) cout << "The argument IS valid" << endl;
    else cout << "The argument is NOT valid" << endl;

    return 0;
}
