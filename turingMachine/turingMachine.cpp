#include <iostream>
#include <string>

using namespace std;

struct Transition
{
    char newState;
    char newVal;
    bool moveRight;
};
Transition T(char newState, char newVal, bool moveRight); //constructor

int indexOf(char val, char* a, int len);
void print(char* a, int len);

bool runTuringMachine(
    char* states,
    int numStates,
    char* tapeSymbols,
    int numTapeSymbols,
    char acceptState,
    char rejectState,
    Transition** transitionFunction,
    char initialState,
    int initialPosition,
    char* tape,
    int tapeLen
);

int main()
{
    Transition** tf = (Transition**)malloc(12 * sizeof(Transition));
    tf[0][0] = T('0', 'a', true);
    tf[0][1] = T('1', 'b', true);
    tf[0][2] = T('r', '*', true);
    tf[1][0] = T('1', 'a', true);
    tf[1][1] = T('a', 'b', true);
    tf[1][2] = T('r', '*', true);
    char ss[] = {'0', '1', 'a', 'r'};
    char sy[] = {'a', 'b', '*'};
    bool result = runTuringMachine(
        ss,
        4,
        sy,
        3,
        'a',
        'r',
        tf,
        '0',
        0,
        "abba*",
        5
    );
    cout << "Turning machine returned " << result << endl;
    //need to write a function for creating the transition function
    /*
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
    */

    return 0;
}

Transition T(char newState, char newVal, bool moveRight)
{
    Transition t;
    t.newState = newState;
    t.newVal = newVal;
    t.moveRight = moveRight;
    return t;
}

int indexOf(char val, char* a, int len)
{
    int ret = -1;
    for(int i = 0; i < len && ret == -1; i++)
    {
        if(a[i] == val){
            ret = i;
        }
    }
    return ret;
}

void print(char* a, int len)
{
    for(int i = 0; i < len; i++){
        cout << a[i] << " ";
    }
    cout << endl;
}

//either move some stuff to structs, or validate before running
bool runTuringMachine(
    char* states,
    int numStates,
    char* tapeSymbols,
    int numTapeSymbols,
    char acceptState,
    char rejectState,
    Transition** transitionFunction, //validate this beforehand
    char initialState,
    int initialPosition,
    char* tape, //validate this beforehand
    int tapeLen
)
{
    char currState = initialState;
    int currPos = initialPosition;
    bool running = true;
    bool ret = false;
    char input;
    Transition currTransition;

    cout << "CURRENT STATE: " << currState << endl;
    cout << "CURRENT POS:   " << currPos << endl;
    print(tape, tapeLen);
    while(running)
    {
        if(currPos < 0 || currPos >= tapeLen){
            ret = false;
            break;
        }
        input = tape[currPos];
        //                                  need to find index
        currTransition = transitionFunction[indexOf(currState, states, numStates)][indexOf(input, tapeSymbols, numTapeSymbols)];
        currState = currTransition.newState;
        tape[currPos] = currTransition.newVal;
        (currTransition.moveRight) ? currPos++ : currPos--;

        cout << "CURRENT STATE: " << currState << endl;
        cout << "CURRENT POS:   " << currPos << endl;
        print(tape, tapeLen);
    }

    return ret;
}
