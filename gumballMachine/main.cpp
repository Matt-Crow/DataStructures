#include <iostream>
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

int main()
{
    Q q = q0;
    string input = "";
    string output = "";
    //begin Matt's code
    //end Matt's code

    cout << PROMPT_STRING;
    cin >> input;

    while(input != I_STRINGS[QUIT])
    {

        ///assign output and q based on current state and input

        cout << output << endl;
        cout << "Current state: " << Q_STRINGS[q] << endl;
        cout << PROMPT_STRING;
        cin >> input;
    }

    return 0;
}
