#include <iostream>
#include <string>
using namespace std;

enum Q{q0, q5, q10, q15, q20};
enum O{GUMBALL, RETURN, MESSAGE, NONE, INVALID};
enum I{NICKEL, DIME, BUY, QUIT};

const string Q_STRINGS[] = {"q0", "q5", "q10", "q15", "q20"};
const string O_STRINGS[] = {"Gumball dispensed.  Have a nice day.\n",
                            "Exact change required.  Returning coin.\n",
                            "Insufficient funds.  Cannot buy.\n",
                            "",
                            "Invalid input.\n"};
const string I_STRINGS[] = {"NICKEL", "DIME", "BUY", "QUIT"};

const string PROMPT_STRING = "NICKEL, DIME, BUY, or QUIT: ";

//begin Matt's code
struct Transition
{
    Q newState;
    O output;
};
Transition T(Q newState, O output); //constructor
//end Matt's code

int main()
{
    Q q = q0;
    string input = "";
    string output = "";
    //begin Matt's code
    Transition currTransition;
    bool isTransitioning;
    //initialize transition function,
    //set all to invalid first
    Transition tf[5][4] = {};
    for(int i = q0; i <= q20; i++)
    {
        for(int j = NICKEL; j <= QUIT; j++)
        {
            tf[i][j] = T((Q)i, INVALID);
        }
    }

    //all the nickel stuff
    tf[q0][NICKEL] = T(q5, NONE);
    tf[q5][NICKEL] = T(q10, NONE);
    tf[q10][NICKEL] = T(q15, NONE);
    tf[q15][NICKEL] = T(q20, NONE);
    tf[q20][NICKEL] = T(q20, RETURN);
    //end Matt's code

    cout << PROMPT_STRING;
    cin >> input;

    while(input != I_STRINGS[QUIT])
    {

        ///assign output and q based on current state and input
        //begin Matt's code
        isTransitioning = false;
        if(input.compare("NICKEL") == 0){
            currTransition = tf[q][NICKEL];
            isTransitioning = true;
        } else {
            output = O_STRINGS[INVALID];
        }

        if(isTransitioning)
        {
            q = currTransition.newState;
            output = O_STRINGS[currTransition.output];
        }
        //end Matt's code
        cout << output << endl;
        cout << "Current state: " << Q_STRINGS[q] << endl;
        cout << PROMPT_STRING;
        cin >> input;
    }

    return 0;
}

//begin Matt's code
Transition T(Q q, O o)
{
    Transition t;
    t.newState = q;
    t.output = o;
    return t;
}
//end Matt's code
