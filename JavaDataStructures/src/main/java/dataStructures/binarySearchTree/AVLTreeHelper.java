package dataStructures.binarySearchTree;

/**
 *
 * @author Matt
 */
public class AVLTreeHelper<T extends Comparable> extends BinarySearchTreeHelper<T, AVLTreeNode<T>> {
    /**
     * AVL tree: the heights of each node's subtrees differ by at most 1.
     * Keeps time complexity of tree operations closer to O(log(n))
     * rather than O(n)
     * 
     * Should cache height to avoid recalculating multiple times
     * 
     * @param root
     * @param value
     * @return 
     */
    public final AVLTreeNode<T> insertAVL(AVLTreeNode<T> root, T value){
        AVLTreeNode<T> newRoot = root;
        if(root == null){
            newRoot = new AVLTreeNode<>(value);
        } else if(root.value.compareTo(value) > 0){
            root.left = insertAVL((AVLTreeNode<T>) root.left, value);
        } else if(root.value.compareTo(value) < 0){
            root.right = insertAVL((AVLTreeNode<T>) root.right, value);
        } else {
            // duplicate value, do nothing
        }
        
        newRoot = rebalance(newRoot);
        
        return newRoot;
    }
    
    public final int getBalance(BinarySearchTreeNode<T> root){
        int left = -1;
        int right = -1;
        if(root != null){
            left = getHeight(root.left);
            right = getHeight(root.right);
        }
        return left - right;
    }
    
    public final AVLTreeNode<T> rebalance(AVLTreeNode<T> root){
        AVLTreeNode<T> newRoot = root;
        if(root != null){
            int balance = getHeight(root.left) - getHeight(root.right);
            if(balance > 1){
                if(getBalance(root.left) == -1){
                    root.left = leftRotate((AVLTreeNode<T>) root.left);
                }
                newRoot = rightRotate(root);
            } else if(balance < -1){
                if(getBalance(root.right) == 1){
                    root.right = rightRotate((AVLTreeNode<T>) root.right);
                }
                newRoot = leftRotate(root);
            }
        }
        return newRoot;
    }
    
    public final AVLTreeNode<T> leftRotate(AVLTreeNode<T> root){
        AVLTreeNode<T> newRoot = root;
        if(root != null){
            newRoot = (AVLTreeNode<T>) root.right;
            root.right = newRoot.left;
            newRoot.left = root;
            // todo update height of root
            // todo update height of newRoot
        }
        return newRoot;
    }
    
    /**
     *      (4)
     *    /     \
     *  (2)     (6)
     * /  \     / \
     *(1) (3) (5) (7) 
     * 
     * to
     * 
     *      (2)
     *    /     \
     *  (1)     (4)
     *          / \
     *        (3) (6)
     *            / \
     *          (5) (7)
     * 
     * @param root
     * @return 
     */
    public final AVLTreeNode<T> rightRotate(AVLTreeNode<T> root){
        AVLTreeNode<T> newRoot = root;
        if(root != null){
            newRoot = (AVLTreeNode<T>) root.left;
            root.left = newRoot.right;
            newRoot.right = root;
            // todo update height of root
            // todo update height of newRoot
        }
        return newRoot;
    }
    
    @Override
    protected BinarySearchTreeNode<T> createNew(T val){
        return new AVLTreeNode<>(val);
    }
}
