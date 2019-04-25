#include <iostream>

using namespace std;

struct Tree{
    char data;
    Tree* leftChild;
    Tree* rightChild;
};

struct frame{
    frame* next;
    Tree* value;
};

Tree* newTree(char data);

void preOrder(Tree* root, ostream &output);
void inOrder(Tree* root, ostream &output);
int postOrder(Tree* root, ostream &output);

void push(frame* &top, char val);
void push(frame* &top, Tree* val);
frame* pop(frame* &top);
void printFrame(frame* top);

int toInt(char c);
char toChar(int i);

//string toPostfix(string infix);
//int evaluatePostfix(string postfix);
int evaluateBinaryOp(Tree* root);

//useInfixPostfixTree
int main(){
    frame* myStack = 0;
    string ip = "12+3*";
    for(int i = 0; i < ip.size(); i++){
        if(isdigit(ip[i])){
            push(myStack, ip[i]);
        } else {
            Tree* right = pop(myStack)->value;
            Tree* left = pop(myStack)->value;
            Tree* a = new Tree;
            a->leftChild = left;
            a->rightChild = right;
            a->data = ip[i];
            push(myStack, a);
        }
    }
    inOrder(myStack->value, cout);
    cout << endl;
    int val = postOrder(myStack->value, cout);
    cout << endl << val << endl;

    return 0;
}

Tree* newTree(char data){
    Tree* ret = new Tree;
    ret->leftChild = 0;
    ret->rightChild = 0;
    ret->data = data;
    return ret;
}

void preOrder(Tree* root, ostream &output){
    if(root){
        output << root->data << " ";
        preOrder(root->leftChild, output);
        preOrder(root->rightChild, output);
    }
}
void inOrder(Tree* root, ostream &output){
    if(root){
        bool isLeaf = !(root->leftChild && root->rightChild);
        if(!isLeaf){
            output << "( ";
        }
        inOrder(root->leftChild, output);
        output << root->data << " ";
        inOrder(root->rightChild, output);
        if(!isLeaf){
            output << ") ";
        }
    }
}
int postOrder(Tree* root, ostream &output){
    int ret;
    if(root){
        if(!isdigit(root->data)){
            ret += evaluateBinaryOp(root);
            cout << "op ret is " << ret << endl;
        }
        postOrder(root->leftChild, output);
        postOrder(root->rightChild, output);
        output << root->data << " ";

        if(isdigit(root->data)){
            ret += toInt(root->data);
            cout << "num ret is " << ret << endl;
        }
        return ret;
    }
    return 0;
}


void push(frame* &top, Tree* val){
    frame* newFrame = new frame;
    newFrame->next = top;
    newFrame->value = val;
    top = newFrame;
}

void push(frame* &top, char val){
    frame* newFrame = new frame;
    newFrame->next = top;
    newFrame->value = newTree(val);
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
    default:
        cout << "Unsupported character: " << c << endl;
    }
    return ret;
}

char toChar(int i){
    return (char)(48 + i);
}

//change this to just evaluate
int evaluateBinaryOp(Tree* root){
    int ret = 0;

    if(root){
        char binaryOp = root->data;
        int left = evaluateBinaryOp(root->leftChild);
        int right = evaluateBinaryOp(root->rightChild);

        switch(binaryOp){
        case '+':
            ret = right + left;
            break;
        case '-':
            ret = right - left;
            break;
        case '*':
            ret = right * left;
            break;
        case '/':
            ret = right / left;
            break;
        default:
            ret = toInt(binaryOp);
            cout << "Invalid binaryOp: " + binaryOp << endl;
        }
        cout << right << " " << binaryOp << " " << left << " = " << ret << endl;
    }

    return ret;
}

/*
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
*/
