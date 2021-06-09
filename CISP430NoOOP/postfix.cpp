
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
            cout << "As tree: " << endl;
            tree = toPostfixTree(post);
            i = evaluatePostfixTree(tree);
            inOrder(tree);
            cout << " = " << i << endl;
        }
    }while(ip != "q");
    return 0;
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
