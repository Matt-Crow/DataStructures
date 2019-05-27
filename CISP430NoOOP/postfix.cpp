#include <iostream>
#include "Stack.h"

using namespace std;

int toInt(char c);
char toChar(int i); //defined in misc

string toPostfix(string infix);
int evaluatePostfix(string postfix);

int usePostfix(){
    string ip = "";
    string post = "";
    int i = 0;
    do{
        cout << "Enter a prefix expression (like 1 + 1) or 'q' to quit: ";
        getline(cin, ip);
        if(ip != "q"){
            post = toPostfix(ip);
            cout << ip << " : " << post << endl;
            i = evaluatePostfix(post);
            cout << ip << " = " << i << endl;
        }
    }while(ip != "q");
    return 0;
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


string toPostfix(string infix){
    string result = "";
    Stack<char>* ops = new Stack<char>();    //opperator stack

    for(char token : infix){
        if(isdigit(token)){
            result += token;
        } else {
            switch(token){
            case '(':
                //if it is an (, push it to the stack
                ops->push('(');
                break;
            case ')':
                //if it is an ), pop until you hit an (
                while(token != '('){
                    token = ops->pop();
                    if(token != '('){
                        result += token;
                    }
                }
                break;
            //if the token is an operator, pop until the top is less precedence than the token,
            //then push to token.
            case '+':
                while(!ops->isEmpty() && ops->peek() != '('){
                    result += ops->pop();
                }
                ops->push(token);
                break;
            case '-':
                while(!ops->isEmpty() && ops->peek() != '('){
                    result += ops->pop();
                }
                ops->push(token);
                break;
            case '*':
                while(
                    !ops->isEmpty() &&
                    ops->peek() != '(' &&
                    ops->peek() != '+' &&
                    ops->peek() != '-'
                ){
                    result += ops->pop();
                }
                ops->push(token);
                break;
            case '/':
                while(
                    !ops->isEmpty() &&
                    ops->peek() != '(' &&
                    ops->peek() != '+' &&
                    ops->peek() != '-'
                ){
                    result += ops->pop();
                }
                ops->push(token);
                break;
            case ' ':
                //space
                break;
            default:
                cout << "Not supported token: " << token << endl;
            }
        }
    }
    while(!ops->isEmpty()){
        result += ops->pop();
    }

    return result;
}

int evaluatePostfix(string postfix){
    Stack<int>* nums = new Stack<int>();
    int a;
    int b;

    for(char token : postfix){
        if(isdigit(token)){
            nums->push(toInt(token));
        } else {
            a = nums->pop();
            b = nums->pop();

            switch(token){
            case '+':
                nums->push(a + b);
                break;
            case '-':
                nums->push(b - a);
                break;
            case '*':
                nums->push(a * b);
                break;
            case '/':
                nums->push(b / a);
                break;
            default:
                cout << "Unsupported token: " << token << endl;
            }
        }
    }

    return nums->pop();
}
