#include <iostream>
#include <fstream>

using namespace std;

struct frame{
    frame* next;
    int value;
};

void push(frame* &top, int val);
frame* pop(frame* &top);
void printFrame(frame* top);

int toInt(char c);

int main(){
    fstream in = fstream("input.txt");
    frame* nums = 0;
    char token;
    frame* op1;
    frame* op2;
    int val1;
    int val2;

    cout << "Before: ";
    while(in >> token){
        cout << token;
        if(isdigit(token)){
            push(nums, toInt(token));
        } else {
            op1 = pop(nums);
            op2 = pop(nums);
            val1 = op1->value;
            val2 = op2->value;
            delete op1;
            delete op2;

            switch(token){
            case '+':
                push(nums, val1 + val2);
                break;
            case '-':
                push(nums, val2 - val1);
                break;
            case '*':
                push(nums, val1 * val2);
                break;
            case '/':
                push(nums, val2 / val1);
                break;
            default:
                cout << endl << "Unsupported token: " << token << endl;
            }
        }
    }
    cout << endl << "After: " << pop(nums)->value << endl;

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

int toInt(char c){
    int ret = -1;
    switch(c){
    case '0':
        ret = 0;
        break;
    case '1':
        ret = 1;
        break;
    case '2':
        ret = 2;
        break;
    case '3':
        ret = 3;
        break;
    case '4':
        ret = 4;
        break;
    case '5':
        ret = 5;
        break;
    case '6':
        ret = 6;
        break;
    case '7':
        ret = 7;
        break;
    case '8':
        ret = 8;
        break;
    case '9':
        ret = 9;
        break;
    }
    return ret;
}
