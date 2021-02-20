package dataStructures;

import java.util.function.Consumer;

/**
 *
 * @author Matt
 * @param <T>
 */
public class BinarySearchTreeNode<T extends Comparable> {
    private final T value;
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
    
    public static void main(String[] args){
        BinarySearchTreeNode<String> root = null;
        for(String arg : args){
            root = BinarySearchTreeNode.<String>insert(root, arg);
            System.out.println();
            if(root != null){
                root.inOrder(System.out::println);
            }
        }
    }
}
