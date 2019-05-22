#include <iostream>
#include "misc.h"
#include "stack.h"

using namespace std;

string convertNumToBase(int num, int base);



int useStack(){
    //make sure to initialize as a null pointer
    stack<int>* s = 0; //LoL. Stack on the heap
    int ip = 0;
    cout << "===STACK===" << endl;
    while(ip != -1){
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Choose an option: " << endl;
        cout << "0: print the stack" << endl;
        cout << "1: push to the stack" << endl;
        cout << "2: pop the top" << endl;
        cout << "3: convert a number from base 10 to another base" << endl;
        cout << "-1: quit" << endl;
        cin >> ip;
        switch(ip){
        case 0:
            print(s, cout);
            break;
        case 1:
            cout << "Enter value to push to the stack: ";
            cin >> ip;
            push(s, ip);
            ip = 1;
            break;
        case 2:
            if(s == 0){
                cout << "Nothing to pop" << endl;
            } else {
                ip = pop(s);
                cout << "Popped " << ip << endl;
                ip = 2;
            }
            break;
        case 3:
            int base;
            cout << "Enter number to convert: ";
            cin >> ip;
            cout << "Enter the base to convert to: ";
            cin >> base;
            cout << ip << " in base " << base << " is " << convertNumToBase(ip, base) << endl;
            ip = 3;
            break;
        }
    }

    s = 0;
    delete s;

    return 0;
}



template <typename T>
void push(stack<T>* &top, T value){
    stack<T>* newFrame = new stack<T>;
    newFrame->next = top;
    newFrame->value = value;
    top = newFrame;
    newFrame = 0;
    delete newFrame;
}

template <typename T>
T pop(stack<T>* &top){
    T ret = 0;
    if(top){
        ret = top->value;
        if(top->next){
            top = top->next;
        } else {
            top = 0;
        }
    }
    return ret;
}

template <typename T>
void print(stack<T>* top, ostream &out){
    stack<T>* curr = top;
    out << "Stack is: " << endl;
    while(curr){
        out << '\t' << curr->value << endl;
        curr = curr->next;
    }
    delete curr; //is 0 at this point
}

string convertNumToBase(int num, int base){
    stack<int>* myStack = 0;
    string ret = "";

    int remainder = num;
    stack<int>* curr = myStack;

    while(remainder > 0){
        push(curr, remainder % base);
        remainder = remainder / base;
    }
    while(curr){
        ret += toChar(pop(curr));
    }

    return ret;
}
