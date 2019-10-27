#include <iostream>
#include <string>

using namespace std;

struct Transition
{
    char newState;
    char newVal;
    bool moveRight;
};
Transition* T(char newState, char newVal, bool moveRight); //constructor

class TransitionFunction{
public:
    TransitionFunction(int numStates, char* states, int numSymbols, char* symbols);
    void set(char state, char symbol, Transition* t);
    Transition* get(char state, char symbol);
    ~TransitionFunction();
    void print();
private:
    char* states;
    int numStates;
    char* symbols;
    int numSymbols;
    Transition*** transitions;
};

int indexOf(char val, char* a, int len);
void print(char* a, int len);

bool runTuringMachine(
    TransitionFunction t,
    char* states,
    int numStates,
    char* tapeSymbols,
    int numTapeSymbols,
    char acceptState,
    char rejectState,
    char initialState,
    int initialPosition,
    char* tape,
    int tapeLen
);

int main()
{
    char ss[] = {'0', '1', 'a', 'r'};
    char sy[] = {'a', 'b', '*'};
    TransitionFunction t = TransitionFunction(4, ss, 3, sy);
    t.set('0', 'a', T('0', 'a', true));
    t.set('0', 'b', T('1', 'b', true));
    t.set('0', '*', T('r', '*', true));
    t.set('1', 'a', T('1', 'a', true));
    t.set('1', 'b', T('a', 'b', true));
    t.set('1', '*', T('r', '*', true));
    t.print();

    char tape[] = {'a', 'a', 'b', 'b', '*'};

    bool result = runTuringMachine(
        t,
        ss,
        4,
        sy,
        3,
        'a',
        'r',
        '0',
        0,
        tape,
        5
    );
    cout << "Turning machine returned " << result << endl;

    return 0;
}

Transition* T(char newState, char newVal, bool moveRight)
{
    Transition* t = (Transition*)malloc(sizeof(Transition));
    t->newState = newState;
    t->newVal = newVal;
    t->moveRight = moveRight;
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
    TransitionFunction t,
    char* states,
    int numStates,
    char* tapeSymbols,
    int numTapeSymbols,
    char acceptState,
    char rejectState,
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
    Transition* currTransition;

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
        currTransition = t.get(currState, tape[currPos]);
        if(currTransition == nullptr)
        {
            ret = false;
            break;
        }
        currState = currTransition->newState;
        tape[currPos] = currTransition->newVal;
        if(currTransition->moveRight)
        {
            currPos++;
        }
        else
        {
            currPos--;
        }

        cout << "CURRENT STATE: " << currState << endl;
        cout << "CURRENT POS:   " << currPos << endl;
        print(tape, tapeLen);
    }

    return ret;
}

TransitionFunction::TransitionFunction(int numStates, char* states, int numSymbols, char* symbols)
{
    this->numStates = numStates;
    this->numSymbols = numSymbols;
    this->states = (char*)malloc(numStates * sizeof(char));
    this->symbols = (char*)malloc(numSymbols * sizeof(char));
    for(int i = 0; i < numStates; i++){
        this->states[i] = states[i];
    }
    for(int i = 0; i < numSymbols; i++){
        this->symbols[i] = symbols[i];
    }

    this->transitions = (Transition***)malloc(sizeof(Transition**) * numStates);
    for(int i = 0; i < numStates; i++)
    {
        this->transitions[i] = (Transition**)malloc(sizeof(Transition*) * numSymbols);
    }
    for(int i = 0; i < numStates; i++)
    {
        for(int j = 0; j < numSymbols; j++)
        {
            this->transitions[i][j] = (Transition*)nullptr;
        }
    }
}

void TransitionFunction::set(char state, char symbol, Transition* t)
{
    int i = indexOf(state, this->states, this->numStates);
    int j = indexOf(symbol, this->symbols, this->numSymbols);
    if(i == -1)
    {
        cerr << "Invalid state: " << state << endl;
        return;
    }
    if(j == -1)
    {
        cerr << "Invalid symbol: " << symbol << endl;
        return;
    }
    this->transitions[i][j] = t;
}

Transition* TransitionFunction::get(char state, char symbol)
{
    int i = indexOf(state, this->states, this->numStates);
    int j = indexOf(symbol, this->symbols, this->numSymbols);
    if(i == -1)
    {
        cerr << "Invalid state: " << state << endl;
        return nullptr;
    }
    if(j == -1)
    {
        cerr << "Invalid symbol: " << symbol << endl;
        return nullptr;
    }
    return this->transitions[i][j];
}

void TransitionFunction::print()
{
    Transition t;
    cout << "TRANSITION FUNCTION IS" << endl;
    cout << "Q | I | q | i | r" << endl;
    cout << "-----------------" << endl;
    for(int i = 0; i < this->numStates; i++)
    {
        for(int j = 0; j < this->numSymbols; j++)
        {
            cout << this->states[i] << " | " << this->symbols[j] << " | ";
            if(this->transitions[i][j] == nullptr)
            {
                cout << "  |   |  ";
            }
            else
            {
                t = *(this->transitions[i][j]);
                cout << t.newState << " | " << t.newVal << " | " << ((t.moveRight) ? 'R' : 'L');
            }
            cout << endl;
        }
    }
}

TransitionFunction::~TransitionFunction()
{
    delete this->states;
    delete this->symbols;
    delete this->transitions;
}
