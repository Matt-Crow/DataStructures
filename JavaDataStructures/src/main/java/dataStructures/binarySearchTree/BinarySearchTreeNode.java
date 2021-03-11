package dataStructures.binarySearchTree;

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
    
    public static void main(String[] args){
        BinarySearchTreeNode root = null;
        BinarySearchTreeHelper<BinarySearchTreeNode> helper = new BinarySearchTreeHelper<>();
        for(int i = 0; i < 10; i++){
            root = helper.insert(root, i);
            System.out.println();
            helper.inOrder(root, System.out::println);
        }
        for(int i = 0; i < 10; i++){
            root = helper.delete(root, i);
            System.out.println();
            helper.inOrder(root, System.out::println);
        }
    }
}
