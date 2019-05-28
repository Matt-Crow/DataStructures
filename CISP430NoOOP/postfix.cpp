#include <iostream>
#include "Stack.h"
#include "TreeNode.h"

using namespace std;

//templates are useless
struct treeStack{
    treeStack* next;
    TreeNode<char>* value;
};
void push(treeStack* &ts, TreeNode<char>* value);
TreeNode<char>* pop(treeStack* &ts);

int toInt(char c);
char toChar(int i); //defined in misc

string toPostfix(string infix);
int evaluatePostfix(string postfix);

TreeNode<char>* toPostfixTree(string postfix);
int evaluatePostfixTree(TreeNode<char>* postfix);

void inOrder(TreeNode<char>* root);


int usePostfix(){
    string ip = "";
    string post = "";
    TreeNode<char>* tree = 0;
    int i = 0;
    do{
        cout << "Enter a prefix expression (like 1 + 1) or 'q' to quit: ";
        getline(cin, ip);
        if(ip != "q"){
            post = toPostfix(ip);
            cout << ip << " : " << post << endl;
            i = evaluatePostfix(post);
            cout << ip << " = " << i << endl;

            cout << "As tree: " << endl;
            tree = toPostfixTree(post);
            i = evaluatePostfixTree(tree);
            inOrder(tree);
            cout << " = " << i << endl;
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


TreeNode<char>* toPostfixTree(string postfix){
    TreeNode<char>* ret = 0;
    treeStack* stack = 0;

    for(char token : postfix){
        if(isdigit(token)){
            push(stack, new TreeNode<char>(token));
        } else {
            TreeNode<char>* right = pop(stack);
            TreeNode<char>* left = pop(stack);
            TreeNode<char>* a = new TreeNode<char>(token);
            a->setLeft(left);
            a->setRight(right);
            push(stack, a);
        }
    }
    if(stack){
        ret = stack->value;
    }
    return ret;
}

int evaluatePostfixTree(TreeNode<char>* postfix){
    int ret = 0;

    if(postfix){
        char binaryOp = postfix->getData();
        int left = evaluatePostfixTree(postfix->getLeft());
        int right = evaluatePostfixTree(postfix->getRight());

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


void push(treeStack* &ts, TreeNode<char>* value){
    treeStack* nn = new treeStack;
    nn->value = value;
    nn->next = ts;
    ts = nn;
}

TreeNode<char>* pop(treeStack* &ts){
    TreeNode<char>* ret = 0;
    if(ts){
        treeStack* temp = ts;
        ret = temp->value;
        ts = temp->next;
        delete temp;
    }
    return ret;
}

void inOrder(TreeNode<char>* root){
    if(root){
        bool isLeaf = !(root->getLeft() || root->getRight());
        if(!isLeaf){
            cout << "( ";
        }
        inOrder(root->getLeft());
        cout << root->getData() << " ";
        inOrder(root->getRight());
        if(!isLeaf){
            cout << ") ";
        }
    }
}
