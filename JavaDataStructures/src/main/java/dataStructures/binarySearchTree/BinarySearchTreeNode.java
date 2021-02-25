package dataStructures.binarySearchTree;

import java.util.function.Consumer;

/**
 * Psuedo static methods in BinarySearchTreeHelper
 * 
 * @author Matt
 * @param <T>
 */
public class BinarySearchTreeNode<T extends Comparable> {
    protected T value;
    protected BinarySearchTreeNode<T> left;
    protected BinarySearchTreeNode<T> right;
    
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
    
    public final BinarySearchTreeNode<T> findMin(){
        BinarySearchTreeNode<T> ret = this;
        if(ret.left != null){
            ret = ret.left.findMin();
        }
        return ret;
    }
    
    public static void main(String[] args){
        args = new String[]{"a", "b", "c", "d", "e", "f", "g"};
        BinarySearchTreeNode<String> root = null;
        BinarySearchTreeHelper<String, BinarySearchTreeNode<String>> helper = new BinarySearchTreeHelper<>();
        for(String arg : args){
            root = helper.insert(root, arg);
            System.out.println();
            if(root != null){
                root.inOrder(System.out::println);
            }
        }
        for(String arg : args){
            root = helper.delete(root, arg);
            System.out.println();
            if(root != null){
                root.inOrder(System.out::println);
            }
        }
    }
}
