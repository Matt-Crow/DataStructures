#include <iostream>

using namespace std;

struct frame{
    frame* next;
    int value;
};

void push(frame* &top, int val);
frame* pop(frame* &top);
void printFrame(frame* top);

string toBase(int i, int b);
char toChar(int i);

int main(){
    int ip = 0;
    int base = 2;

    while(ip >= 0 && base > 0){
        cout << "Enter a number: (negative to quit) ";
        cin >> ip;

        if(ip >= 0){
            cout << "Enter the base to convert it to: (negative or zero to quit) ";
            cin >> base;

            if(base > 0){
                cout << ip << " in base " << base << " is " << toBase(ip, base) << endl;
            }
        }
    }

    return 0;
}

void push(frame* &top, int val){
    frame* newFrame = new frame;
    newFrame->next = top;
    newFrame->value = val;
    top = newFrame;
}

frame* pop(frame* &top){
    frame* ret = top;
    if(top->next){
        top = top->next;
        ret->next = 0;
    } else {
        top = 0;
    }
    return ret;
}

void printFrame(frame* top){
    frame* current = top;

    while(current){
        cout << current->value << endl;
        current = current->next;
    }
}

string toBase(int i, int b){
    frame* myStack = 0;
    string ret = "";

    int remainder = i;
    frame* current = myStack;

    while(remainder > 0){
        push(current, remainder % b);
        remainder = remainder / b;
    }

    while(current){
        ret+= toChar(pop(current)->value);
    }

    return ret;
}

char toChar(int i){
    char ret = (char)(48 + i);
    if(i >= 10){
        ret = (char)(65 + i - 10);
    }
    return ret;
}
