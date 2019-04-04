struct TreeNode{
    int data;
    TreeNode* parent;
    TreeNode* leftChild;
    TreeNode* rightChild;
}

void insertChild(TreeNode* parent, TreeNode* child){
    //recursive until finds open left or right child
}

TreeNode* spawnNode(TreeNode* parent, int data){
    TreeNode* ret = new TreeNode;
    ret->parent = parent;
    ret->data = data;
    ret->leftChild = 0;
    ret->rightChild = 0;

    //recursively place child

    return ret;
}
