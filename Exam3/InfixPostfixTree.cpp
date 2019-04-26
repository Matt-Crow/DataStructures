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

void inOrder(Tree* root, ostream &output);

void push(frame* &top, Tree* val);

frame* pop(frame* &top);

void printFrame(frame* top);

int toInt(char c);
char toChar(int i);

int evaluate(Tree* root);

int useInfixPostfixTree(){
    frame* myStack = 0;
    string ip = "";

    cout << "Enter a postfix expression: ";
    cin >> ip;

    for(int i = 0; i < ip.size(); i++){
        if(isdigit(ip[i])){
            push(myStack, newTree(ip[i]));
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
    cout << ip << " -> ";
    inOrder(myStack->value, cout);
    cout << " = " << evaluate(myStack->value) << endl;

    return 0;
}

Tree* newTree(char data){
    Tree* ret = new Tree;
    ret->leftChild = 0;
    ret->rightChild = 0;
    ret->data = data;
    return ret;
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

void push(frame* &top, Tree* val){
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
    default:
        cout << "Unsupported character: " << c << endl;
    }
    return ret;
}

char toChar(int i){
    return (char)(48 + i);
}

int evaluate(Tree* root){
    int ret = 0;

    if(root){
        char binaryOp = root->data;
        int left = evaluate(root->leftChild);
        int right = evaluate(root->rightChild);

        switch(binaryOp){
        case '+':
            ret = left + right;
            break;
        case '-':
            ret = left - right;
            break;
        case '*':
            ret = left * right;
            break;
        case '/':
            ret = left / right;
            break;
        default:
            //if it is not an operator, just return the value
            ret = toInt(binaryOp);
        }
    }

    return ret;
}
