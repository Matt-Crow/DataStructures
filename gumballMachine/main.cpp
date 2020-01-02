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
    Transition tf[5][3] = {};
    for(int i = q0; i <= q20; i++)
    {
        //                      don't include QUIT: we don't need it
        for(int j = NICKEL; j < QUIT; j++)
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

    //all the dime stuff
    tf[q0][DIME] = T(q10, NONE);
    tf[q5][DIME] = T(q15, NONE);
    tf[q10][DIME] = T(q20, NONE);
    tf[q15][DIME] = T(q15, RETURN);
    tf[q20][DIME] = T(q20, RETURN);

    //buying
    tf[q0][BUY] = T(q0, MESSAGE);
    tf[q5][BUY] = T(q5, MESSAGE);
    tf[q10][BUY] = T(q10, MESSAGE);
    tf[q15][BUY] = T(q15, MESSAGE);
    tf[q20][BUY] = T(q0, GUMBALL);

    //end Matt's code

    cout << PROMPT_STRING;
    cin >> input;

    while(input != I_STRINGS[QUIT])
    {

        ///assign output and q based on current state and input
        //begin Matt's code
        isTransitioning = true;
        if(input.compare("NICKEL") == 0)
        {
            currTransition = tf[q][NICKEL];
        }
        else if(input.compare("DIME") == 0)
        {
            currTransition = tf[q][DIME];
        }
        else if(input.compare("BUY") == 0)
        {
            currTransition = tf[q][BUY];
        }
        else
        {
            output = O_STRINGS[INVALID];
            isTransitioning = false;
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
