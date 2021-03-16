package dataStructures.binarySearchTree;

import java.util.function.Consumer;

/**
 * Psuedo static methods in BinarySearchTreeHelper
 * 
 * @author Matt
 */
public class BinarySearchTreeNode {
    protected int value;
    protected BinarySearchTreeNode left;
    protected BinarySearchTreeNode right;
    
    public BinarySearchTreeNode(int value){
        this.value = value;
        left = null;
        right = null;
    }
    
    public static final void inOrder(BinarySearchTreeNode root, Consumer<Integer> operation){
        if(root != null){
            inOrder(root.left, operation);
            operation.accept(root.value);
            inOrder(root.right, operation);
        }
    }
    
    public static final int getHeight(BinarySearchTreeNode root){
        int ret = -1;
        if(root != null){
            ret = Math.max(getHeight(root.left), getHeight(root.right)) + 1;
        }
        return ret;
    }
    
    public static final BinarySearchTreeNode findMin(BinarySearchTreeNode root){
        BinarySearchTreeNode ret = root;
        if(ret.left != null){
            ret = findMin(ret.left);
        }
        return ret;
    }
    
    public static final BinarySearchTreeNode findMax(BinarySearchTreeNode root){
        BinarySearchTreeNode ret = root;
        if(ret.right != null){
            ret = findMax(ret.right);
        }
        return ret;
    }
    
    
    // returns the new root
    public static BinarySearchTreeNode insert(BinarySearchTreeNode root, int value){
        BinarySearchTreeNode ret = root;
        if(root == null){
            // not work
            ret = new BinarySearchTreeNode(value);
        } else if(root.value > value){
            // need to go left
            root.left = insert(root.left, value);
        } else if(root.value < value){
            // go right
            root.right = insert(root.right, value);
        } else {
            // value already exists, so do nothing
        }
        
        return ret;
    }
    
    // returns the new root
    public static final BinarySearchTreeNode delete(BinarySearchTreeNode root, int value){
        BinarySearchTreeNode ret = root;
        if(root == null){
            // do nothing
        } else if(root.value > value){
            // go left
            root.left = delete(root.left, value);
        } else if(root.value < value){
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
            BinarySearchTreeNode swapMe = findMin(root.right);
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
    
    public static void main(String[] args){
        BinarySearchTreeNode root = null;
        for(int i = 0; i < 10; i++){
            root = insert(root, i);
            System.out.println();
            inOrder(root, System.out::println);
        }
        for(int i = 0; i < 10; i++){
            root = delete(root, i);
            System.out.println();
            inOrder(root, System.out::println);
        }
    }
}
