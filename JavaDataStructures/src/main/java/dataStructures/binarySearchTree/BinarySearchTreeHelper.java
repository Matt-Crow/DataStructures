package dataStructures.binarySearchTree;

/**
 * Move static parameterized methods out of BSTN
 * @author Matt
 * @param <T>
 */
public class BinarySearchTreeHelper<T extends Comparable, TreeType extends BinarySearchTreeNode<T>> {
    public final int getHeight(BinarySearchTreeNode<?> root){
        int ret = -1;
        if(root != null){
            ret = Math.max(getHeight(root.left), getHeight(root.right)) + 1;
        }
        return ret;
    }
    
    // returns the new root
    public final TreeType insert(TreeType root, T value){
        TreeType ret = root;
        if(root == null){
            // not work
            ret = (TreeType) createNew(value);
        } else if(root.value.compareTo(value) > 0){
            // need to go left
            root.left = insert((TreeType) root.left, value);
        } else if(root.value.compareTo(value) < 0){
            // go right
            root.right = insert((TreeType) root.right, value);
        } else {
            // value already exists, so do nothing
        }
        
        return ret;
    }
    
    // returns the new root
    public final TreeType delete(TreeType root, T value){
        TreeType ret = root;
        if(root == null){
            // do nothing
        } else if(root.value.compareTo(value) > 0){
            // go left
            root.left = delete((TreeType) root.left, value);
        } else if(root.value.compareTo(value) < 0){
            // go right
            root.right = delete((TreeType) root.right, value);
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
            root.right = delete((TreeType) root.right, swapMe.value);
        } else if(root.left != null){
            // replace root with its left child
            ret = (TreeType) root.left;
        } else if(root.right != null){
            ret = (TreeType) root.right;
        } else {
            throw new RuntimeException();
        }
        return ret;
    }
    
    protected BinarySearchTreeNode<T> createNew(T val){
        return new BinarySearchTreeNode<>(val);
    }
}
