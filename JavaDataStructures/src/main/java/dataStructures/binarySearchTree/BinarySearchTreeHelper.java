package dataStructures.binarySearchTree;

import java.util.function.Consumer;

/**
 * Move static parameterized methods out of BSTN
 * @author Matt
 * @param <T>
 */
public class BinarySearchTreeHelper<TreeType extends BinarySearchTreeNode> {
    
    public final void inOrder(BinarySearchTreeNode root, Consumer<Integer> operation){
        if(root != null){
            inOrder(root.left, operation);
            operation.accept(root.value);
            inOrder(root.right, operation);
        }
    }
    
    public final int getHeight(BinarySearchTreeNode root){
        int ret = -1;
        if(root != null){
            ret = Math.max(getHeight(root.left), getHeight(root.right)) + 1;
        }
        return ret;
    }
    
    // returns the new root
    public TreeType insert(TreeType root, int value){
        TreeType ret = root;
        if(root == null){
            // not work
            ret = (TreeType) createNew(value);
        } else if(root.value > value){
            // need to go left
            root.left = insert((TreeType) root.left, value);
        } else if(root.value < value){
            // go right
            root.right = insert((TreeType) root.right, value);
        } else {
            // value already exists, so do nothing
        }
        
        return ret;
    }
    
    // returns the new root
    public final TreeType delete(TreeType root, int value){
        TreeType ret = root;
        if(root == null){
            // do nothing
        } else if(root.value > value){
            // go left
            root.left = delete((TreeType) root.left, value);
        } else if(root.value < value){
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
            BinarySearchTreeNode swapMe = BinarySearchTreeNode.findMin(root.right);
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
    
    protected TreeType createNew(int val){
        return (TreeType)new BinarySearchTreeNode(val);
    }
}
