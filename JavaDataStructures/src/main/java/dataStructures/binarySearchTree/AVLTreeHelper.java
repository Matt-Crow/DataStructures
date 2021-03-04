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
            newRoot = rebalance(newRoot);
        } else if(root.value.compareTo(value) < 0){
            root.right = insertAVL((AVLTreeNode<T>) root.right, value);
            newRoot = rebalance(newRoot);
        } else {
            // duplicate value, do nothing
        }
        
        // update height of root
        
        return newRoot;
    }
    
    public final AVLTreeNode<T> deleteAVL(AVLTreeNode<T> root, T value){
        AVLTreeNode<T> newRoot = root;
        if(root == null){
            // do nothing
        } else if(root.value.compareTo(value) > 0){
            root.left = deleteAVL((AVLTreeNode<T>) root.left, value); 
        } else if(root.value.compareTo(value) < 0){
            root.right = deleteAVL((AVLTreeNode<T>) root.right, value);
        } else if(root.left == null && root.right == null){
            // found, so delete
            newRoot = null;
        } else if(root.left != null && root.right != null){
            // two children
            /*
            Two children.
            Replace this root with either:
            1. the smallest node from its right subtree
            or
            2. the largest node from its left subtree
            */
            AVLTreeNode<T> swapMe = (AVLTreeNode<T>) root.left.findMax();
            newRoot.value = swapMe.value;
            newRoot.left = deleteAVL((AVLTreeNode<T>) root.left, value);
        } else if(root.left != null){
            // replace root with its left child
            newRoot = (AVLTreeNode<T>) root.left;
        } else if(root.right != null){
            newRoot = (AVLTreeNode<T>) root.right;
        } else {
            throw new RuntimeException();
        }
        newRoot = rebalance(newRoot);
        // need to update heights somewhere
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
    
    /**
     * In class, the professor had us identify 2 "k nodes":
     * - first k node is the imbalanced node
     * - second k node is the next node in the path to the last inserted node
     * - if the last inserted value is between the two k nodes, double rotate
     * - else, single rotation
     * - if double rotation, third k node is the node after k-2 in the path to
     *   the last inserted node
     * 
     * @param root
     * @return 
     */
    public final AVLTreeNode<T> rebalance(AVLTreeNode<T> root){
        AVLTreeNode<T> newRoot = root;
        if(root != null){
            int balance = getHeight(root.left) - getHeight(root.right);
            if(balance > 1){ // left heavy
                if(getBalance(root.left) < 0){ // left heavy inner 
                    root.left = leftRotate((AVLTreeNode<T>) root.left); // rotate child
                }
                newRoot = rightRotate(root); // rotate parent
            } else if(balance < -1){ // right heavy
                if(getBalance(root.right) > 0){ // right heavy outer
                    root.right = rightRotate((AVLTreeNode<T>) root.right); // rotate child
                }
                newRoot = leftRotate(root); // rotate parent
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
