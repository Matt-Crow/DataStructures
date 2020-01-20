//this file is currently being destroyed
/*
template<class T>
int TreeNode<T>::getHeight(){
    int left = (this->left) ? this->left->getHeight() + 1 : 0;
    int right = (this->right) ? this->right->getHeight() + 1 : 0;
    return (left < right) ? right : left;
}

template<class T>
int TreeNode<T>::getArraySize(){
    int ret = 1;
    int height = getHeight();
    // 2^(height + 1) - 1;
    for(int i = 0; i < height + 1; i++){
        ret *= 2;
    }
    ret--;
    return ret;
}

template<class T>
void TreeNode<T>::populateArray(T* a, int aLen, int idx){
    if(a != 0){
        a[idx] = this->value;
        if(2 * idx + 1 < aLen && this->left){
            this->left->populateArray(a, aLen, 2 * idx + 1);
        }
        if(2 * idx + 2 < aLen && this->right){
            this->right->populateArray(a, aLen, 2 * idx + 2);
        }
    }
}

template<class T>
T* BinaryTree<T>::toArray(){
    T* ret = 0;
    if(!this->isEmpty()){
        int len = this->getArraySize();
        ret = (T*)malloc(sizeof(T) * len);
        this->root->populateArray(ret, len, 0);
    }
    return ret;
}

template<class T>
int BinaryTree<T>::getArraySize(){
    return (this->isEmpty()) ? 0 : this->root->getArraySize();
}

template<class T>
int BinaryTree<T>::test(){
    BinaryTree<int>* tree = new BinaryTree<int>();
    int ip = 0;

    do {
        std::cout << "2: Convert the binary tree to an array" << std::endl;
        std::cout << "-1: Quit" << std::endl;
        std::cout << "Choose an option:" << std::endl;
        std::cin >> ip;
        switch(ip){
            case 2:
                int* a = tree->toArray();
                int len = tree->getArraySize();
                std::cout << "Array:" << std::endl;
                for(int i = 0; i < len; i++){
                    std::cout << a[i] << " ";
                }
                std::cout << std::endl;
                delete a;
                break;
        }
    } while(ip != -1);

    delete tree;
    tree = 0;

    return 0;
}
*/
