package dataStructures.binarySearchTree;

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
    
    public final BinarySearchTreeNode<T> findMin(){
        BinarySearchTreeNode<T> ret = this;
        if(ret.left != null){
            ret = ret.left.findMin();
        }
        return ret;
    }
    
    public final BinarySearchTreeNode<T> findMax(){
        BinarySearchTreeNode<T> ret = this;
        if(ret.right != null){
            ret = ret.right.findMax();
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
            helper.inOrder(root, System.out::println);
        }
        for(String arg : args){
            root = helper.delete(root, arg);
            System.out.println();
            helper.inOrder(root, System.out::println);
        }
    }
}
