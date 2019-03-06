#include <iostream>
#include <fstream>

using namespace std;

struct frame{
    frame* next;
    char value;
};

void push(frame* &top, char val);
frame* pop(frame* &top);
void printFrame(frame* top);

int toInt(char c);
char toChar(int i);

string toPostfix(string infix);
int evaluatePostfix(string postfix);

int main(){
    string ip = " ";
    char token;
    frame* operators = 0;
    string result = "";

    while(ip != ""){
        cout << "Enter an infix expression, or just hit enter to quit: ";
        getline(cin, ip);

        if(ip == ""){
            break;
        }

        result = toPostfix(ip);
        cout << result << endl;
        cout << evaluatePostfix(result) << endl;
    }
    return 0;
}

void push(frame* &top, char val){
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

char toChar(int i){
    return (char)(48 + i);
}

string toPostfix(string infix){
    string result = "";
    frame* ops = 0;    //opperator stack

    for(char token : infix){
        if(isdigit(token)){
            result += token;
        } else {
            switch(token){
            case '(':
                //if it is an (, push it to the stack
                push(ops, '(');
                break;
            case ')':
                //if it is an ), pop until you hit an (
                while(token != '('){
                    token = pop(ops)->value;
                    if(token != '('){
                        result += token;
                    }
                }
                break;
            //if the token is an operator, pop until the top is less precedence than the token,
            //then push to token.
            case '+':
                while(ops && ops->value != '('){
                    result += pop(ops)->value;
                }
                push(ops, token);
                break;
            case '-':
                while(ops && ops->value != '('){
                    result += pop(ops)->value;
                }
                push(ops, token);
                break;
            case '*':
                while(
                    ops &&
                    ops->value != '(' &&
                    ops->value != '+' &&
                    ops->value != '-'
                ){
                    result += pop(ops)->value;
                }
                push(ops, token);
                break;
            case '/':
                while(
                    ops &&
                    ops->value != '(' &&
                    ops->value != '+' &&
                    ops->value != '-'
                ){
                    result += pop(ops)->value;
                }
                push(ops, token);
                break;
            case ' ':
                //space
                break;
            default:
                cout << "Not supported token: " << token << endl;
            }
        }
    }
    while(ops){
        result += pop(ops)->value;
    }

    return result;
}

int evaluatePostfix(string postfix){
    frame* nums = 0;
    int a;
    int b;

    for(char token : postfix){
        if(isdigit(token)){
            push(nums, token);
        } else {
            a = toInt(pop(nums)->value);
            b = toInt(pop(nums)->value);

            switch(token){
            case '+':
                push(nums, toChar(a + b));
                break;
            case '-':
                push(nums, toChar(b - a));
                break;
            case '*':
                push(nums, toChar(a * b));
                break;
            case '/':
                push(nums, toChar(b / a));
                break;
            default:
                cout << "Unsupported token: " << token << endl;
            }
        }
    }

    return toInt(pop(nums)->value);
}
