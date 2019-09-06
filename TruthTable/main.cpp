#include <iostream>
#include <iomanip>
#include "parser.h"
using namespace std;

#define MAX_ROWS 8
#define MAX_COLS 10


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
    //this is really strange, but it works
    bool currVals[] = {true, true, true}; // the values the next row should have
    int twoPow; // how many times each symbol (t/f) will repeat before switching
    for(int row = 0; row < 8; row++){
        twoPow = 4; //start at 4
        for(int col = 0; col < 3; col++){
            table[row][col] = currVals[col];
            if((row + 1) % twoPow == 0){
                // alternate if the current symbol has repeated enough times
                currVals[col] = !currVals[col];
            }
            twoPow /= 2; // symbols alternate twice as fast with each column
        }
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
    //headers
    for(int i = 0; i < numProps; i++){
        cout << setw(symbols[i].size() + 2) << symbols[i];
    }

    cout << endl << endl;

    //body
    for(int row = 0; row < MAX_ROWS; row++){
        for(int col = 0; col < numProps; col++){
            cout << setw(symbols[col].size() + 2) << ((table[row][col]) ? "T" : "F");
        }
        cout << endl;
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
    //begin Matt's code
    symbols[numProps] = statement;
    for(int row = 0; row < MAX_ROWS; row++){
        table[row][numProps] = evaluate(table[row][0], table[row][1], table[row][2], statement);
    }
    //end Matt's code
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
    //first, how many of the propositions are just our variables?
    //we already know this from the assignment, but this is how I would check if I didn't
    int numVars = 0;
    int twoToSomePow = MAX_ROWS;
    while(twoToSomePow != 1){
        twoToSomePow /= 2;
        numVars++;
    }
    //number of variables is Log base 2 of MAX_ROWS

    bool valid = true;
    bool hypsTrue; //all hypotheses thus far are true
    for(int row = 0; valid && row < MAX_ROWS; row++){
        //break once the conclusion is false
        hypsTrue = true; //reset each row, as we are testing new variable values
        for(int col = numVars; hypsTrue && col < numProps; col++){
            //skip over the variables, go through each hypothesis.
            //break once I encounter a false hypothesis
            if(col == numProps - 1){
                //on the conclusion
                valid = table[row][col];
            } else {
                hypsTrue = table[row][col];
            }
        }
    }
    return valid;
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
