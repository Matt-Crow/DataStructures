package dataStructures.binarySearchTree;

/**
 *
 * @author Matt
 */
public class AVLTreeNode<T extends Comparable> extends BinarySearchTreeNode<T> {
    private int height;
    public AVLTreeNode(T value) {
        super(value);
        height = 0;
    }
    
    public final int getHeight(){
        throw new UnsupportedOperationException();
        //return height;
    }
    
    public final void setHeight(int height){
        this.height = height;
    }
    
    public static void main(String[] args){
        args = new String[]{"a", "b", "c", "d", "e", "f", "g"};
        AVLTreeNode<String> root = null;
        AVLTreeHelper<String> helper = new AVLTreeHelper<>();
        for(String arg : args){
            root = helper.insertAVL(root, arg);
            System.out.println();
            helper.inOrder(root, System.out::println);
        }
        System.out.println("Height is " + helper.getHeight(root));
        for(String arg : args){
            root = helper.delete(root, arg);
            System.out.println();
            helper.inOrder(root, System.out::println);
        }
    }
}
