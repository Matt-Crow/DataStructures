#include <iostream>

using namespace std;

struct baseStack{
    baseStack* belowThis;
    int value;
};

void toBase(int i, int b);
void printFrame(baseStack* top);
char toChar(int i);

int main(){
    for(int i = 0; i <= 20; i++){
        cout << endl << i;
        for(int j = 2; j <= 16; j+=2){
            cout << endl << "In base " << j << ": ";
            toBase(i, j);
        }
    }
    return 0;
}

void toBase(int i, int b){
    baseStack* myStack = new baseStack;
    myStack->belowThis = 0;
    myStack->value = 0;

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
        cout << toChar(current->value);
        current = current->belowThis;
    }
}

char toChar(int i){
    char ret = (char)(48 + i);
    if(i >= 10){
        ret = (char)(65 + i - 10);
    }
    return ret;
}
