package dataStructures;

import java.util.function.Consumer;

/**
 *
 * @author Matt
 * @param <T>
 */
public class BinarySearchTreeNode<T extends Comparable> {
    private T value;
    private BinarySearchTreeNode<T> left;
    private BinarySearchTreeNode<T> right;
    
    public BinarySearchTreeNode(T value){
        this.value = value;
        left = null;
        right = null;
    }
    
    public final void inOrder(Consumer<T> operation){
        if(left != null){
            left.inOrder(operation);
        }
        operation.accept(value);
        if(right != null){
            right.inOrder(operation);
        }
    }
    
    // returns the new root
    public static <T extends Comparable> BinarySearchTreeNode<T> insert(BinarySearchTreeNode<T> root, T value){
        BinarySearchTreeNode<T> ret = root;
        if(root == null){
            ret = new BinarySearchTreeNode<>(value);
        } else if(root.value.compareTo(value) > 0){
            // need to go left
            root.left = BinarySearchTreeNode.<T>insert(root.left, value);
        } else if(root.value.compareTo(value) < 0){
            // go right
            root.right = BinarySearchTreeNode.<T>insert(root.right, value);
        } else {
            // value already exists, so do nothing
        }
        
        return ret;
    }
    
    public final BinarySearchTreeNode<T> findMin(){
        BinarySearchTreeNode<T> ret = this;
        if(ret.left != null){
            ret = ret.left.findMin();
        }
        return ret;
    }
    
    // returns the new root
    public static <T extends Comparable> BinarySearchTreeNode<T> delete(BinarySearchTreeNode<T> root, T value){
        BinarySearchTreeNode<T> ret = root;
        if(root == null){
            // do nothing
        } else if(root.value.compareTo(value) > 0){
            // go left
            root.left = BinarySearchTreeNode.<T>delete(root.left, value);
        } else if(root.value.compareTo(value) < 0){
            // go right
            root.right = BinarySearchTreeNode.<T>delete(root.right, value);
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
            root.right = BinarySearchTreeNode.<T>delete(root.right, swapMe.value);
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
        BinarySearchTreeNode<String> root = null;
        for(String arg : args){
            root = BinarySearchTreeNode.<String>insert(root, arg);
            System.out.println();
            if(root != null){
                root.inOrder(System.out::println);
            }
        }
        for(String arg : args){
            root = BinarySearchTreeNode.<String>delete(root, arg);
            System.out.println();
            if(root != null){
                root.inOrder(System.out::println);
            }
        }
    }
}
