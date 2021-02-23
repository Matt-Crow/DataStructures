package dataStructures.binarySearchTree;

/**
 * Move static parameterized methods out of BSTN
 * @author Matt
 * @param <T>
 */
public class BinarySearchTreeHelper<T extends Comparable> {
    public final int getHeight(BinarySearchTreeNode<T> root){
        int ret = -1;
        if(root != null){
            ret = Math.max(getHeight(root.left), getHeight(root.right)) + 1;
        }
        return ret;
    }
    
    // returns the new root
    public final BinarySearchTreeNode<T> insert(BinarySearchTreeNode<T> root, T value){
        BinarySearchTreeNode<T> ret = root;
        if(root == null){
            ret = new BinarySearchTreeNode<>(value);
        } else if(root.value.compareTo(value) > 0){
            // need to go left
            root.left = insert(root.left, value);
        } else if(root.value.compareTo(value) < 0){
            // go right
            root.right = insert(root.right, value);
        } else {
            // value already exists, so do nothing
        }
        
        return ret;
    }
    
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
    public final BinarySearchTreeNode<T> insertAVL(BinarySearchTreeNode<T> root, T value){
        BinarySearchTreeNode<T> newRoot = root;
        if(root == null){
            newRoot = new BinarySearchTreeNode<>(value);
        } else if(root.value.compareTo(value) > 0){
            root.left = insertAVL(root.left, value);
        } else if(root.value.compareTo(value) < 0){
            root.right = insertAVL(root.right, value);
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
    
    public final BinarySearchTreeNode<T> rebalance(BinarySearchTreeNode<T> root){
        BinarySearchTreeNode<T> newRoot = root;
        if(root != null){
            int balance = getHeight(root.left) - getHeight(root.right);
            // todo: inner rotates
            if(balance > 1){
                newRoot = rightRotate(root);
            } else if(balance < -1){
                newRoot = leftRotate(root);
            }
        }
        return newRoot;
    }
    
    public final BinarySearchTreeNode<T> leftRotate(BinarySearchTreeNode<T> root){
        BinarySearchTreeNode<T> newRoot = root;
        if(root != null){
            newRoot = root.right;
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
    public final BinarySearchTreeNode<T> rightRotate(BinarySearchTreeNode<T> root){
        BinarySearchTreeNode<T> newRoot = root;
        if(root != null){
            newRoot = root.left;
            root.left = newRoot.right;
            newRoot.right = root;
            // todo update height of root
            // todo update height of newRoot
        }
        return newRoot;
    }
    
    // returns the new root
    public final BinarySearchTreeNode<T> delete(BinarySearchTreeNode<T> root, T value){
        BinarySearchTreeNode<T> ret = root;
        if(root == null){
            // do nothing
        } else if(root.value.compareTo(value) > 0){
            // go left
            root.left = delete(root.left, value);
        } else if(root.value.compareTo(value) < 0){
            // go right
            root.right = delete(root.right, value);
        } else if(root.left == null && root.right == null){
            /*
            By now, we know the root contains the value to delete
            first, check if it has no children
            */
            ret = null;
            // the caller will set this root to null, deleting it
        } else if(root.left != null && root.right != null){
            /*
            Two children.
            Replace this root with either:
            1. the smallest node from its right subtree
            or
            2. the largest node from its left subtree
            */
            BinarySearchTreeNode<T> swapMe = root.right.findMin();
            ret.value = swapMe.value;
            root.right = delete(root.right, swapMe.value);
        } else if(root.left != null){
            // replace root with its left child
            ret = root.left;
        } else if(root.right != null){
            ret = root.right;
        } else {
            throw new RuntimeException();
        }
        return ret;
    }
}
