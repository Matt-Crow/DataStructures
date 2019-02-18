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

int main(){
    fstream file = fstream("input.txt");
    char token;
    frame* operators = 0;
    string result = "";

    cout << "Before: ";
    while(file >> token){
        cout << token;
        if(isdigit(token)){
            result += token;
        } else {
            switch(token){
            case '(':
                push(operators, token);
                break;
            case ')':
                while(token != '('){
                    token = pop(operators)->value;
                    if(token != '('){
                        result += token;
                    }
                }
                break;
            case '+':
                while(operators && operators->value != '('){
                    result += pop(operators)->value;
                }
                push(operators, token);
                break;
            case '-':
                while(operators && operators->value != '('){
                    result += pop(operators)->value;
                }
                push(operators, token);
                break;
            case '*':
                while(
                    operators &&
                    operators->value != '(' &&
                    operators->value != '+' &&
                    operators->value != '-'
                ){
                    result += pop(operators)->value;
                }
                push(operators, token);
                break;
            case '/':
                while(
                    operators &&
                    operators->value != '(' &&
                    operators->value != '+' &&
                    operators->value != '-'
                ){
                    result += pop(operators)->value;
                }
                push(operators, token);
                break;
            default:
                cout << "Not supported token: " << token << endl;
            }
        }
    }
    file.close();
    while(operators){
        result += pop(operators)->value;
    }
    cout << endl << "After: " << result << endl;

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
