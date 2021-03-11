package dataStructures.binarySearchTree;

/**
 *
 * @author Matt
 */
public class AVLTreeNode extends BinarySearchTreeNode {
    private int height;
    public AVLTreeNode(int value) {
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
        AVLTreeNode root = null;
        AVLTreeHelper helper = new AVLTreeHelper();
        for(int i = 0; i < 10; i++){
            root = helper.insertAVL(root, i);
            System.out.println();
            helper.inOrder(root, System.out::println);
            System.out.println("Height is " + helper.getHeight(root));
        }
        System.out.println("Height is " + helper.getHeight(root));
        for(int i = 0; i < 10; i++){
            root = helper.deleteAVL(root, i);
            System.out.println();
            helper.inOrder(root, System.out::println);
            System.out.println("Height is " + helper.getHeight(root));
        }
    }
}
