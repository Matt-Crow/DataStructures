#include <iostream>
#include "Stack.h"

using namespace std;

int main()
{
    Stack<int> intStack = Stack<int>();
    intStack.push(2);
    intStack.push(3);
    intStack.push(4444);
    cout << "Hello world!" << endl;
    return 0;
}
