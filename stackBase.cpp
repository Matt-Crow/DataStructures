#include <iostream>

using namespace std;

struct baseStack{
    baseStack* belowThis;
    int value;
};

void toBase(int i, int b);
void printFrame(baseStack* top);

//how convert from 2digit to letter?

int main(){
    toBase(10, 2);
    return 0;
}

void toBase(int i, int b){
    baseStack* myStack = new baseStack;
    myStack->belowThis = 0;

    int remainder = i;
    baseStack* current = myStack;

    baseStack* temp;

    while(remainder > 0){
        current->value = remainder % b;
        remainder = remainder / b;
        if(remainder > 0){
            temp = new baseStack;
            temp->belowThis = current;
            current = temp;
        }
    }
    printFrame(current);
}

void printFrame(baseStack* top){
    baseStack* current = top;

    while(current){
        cout << current->value << endl;
        current = current->belowThis;
    }
}
