package dataStructures.binarySearchTree;

/**
 * todo main root is black
 * @author Matt
 */
public class RedBlackTreeHelper extends BinarySearchTreeHelper<RedBlackTreeNode>{
    
    @Override
    public final RedBlackTreeNode insert(RedBlackTreeNode root, int value){
        RedBlackTreeNode newRoot = root;
        
        if(root == null){
            newRoot = new RedBlackTreeNode(value, false);
        } else if(root.value > value){
            root.left = insert((RedBlackTreeNode)root.left, value);
        } else if(root.value < value){
            root.right = insert((RedBlackTreeNode)root.right, value);
        } else {
            // duplicate, do nothing
        }
        
        // left is black, right is red
        if(isBlack((RedBlackTreeNode) root.left) && !isBlack((RedBlackTreeNode) root.right)){
            newRoot = rotateLeft(newRoot);
        }
        
        // error case #2: check for two outer red descendants
        // will short-circuit evaluate if left is null
        if(!isBlack((RedBlackTreeNode) root.left) && !isBlack((RedBlackTreeNode) root.left.left)){
            newRoot = rotateRight(newRoot);
        }
        if(!isBlack((RedBlackTreeNode) root.right) && !isBlack((RedBlackTreeNode) root.right.right)){
            newRoot = rotateLeft(newRoot);
        }
        
        // error case #3: check for two red children
        if(!isBlack((RedBlackTreeNode) root.left) && !isBlack((RedBlackTreeNode) root.right)){
            flipColor(root);
        }
        
        
        
        
        
        // each check will change its problem to the next one

        // first check for red left child with red right child or mirror
        //  and rotate outward

        // second check for red left child with red left child or mirror
        //  and rotate inward

        // third check for two red children
        // and flip colors between parent and children
        
        return newRoot;
    }
    
    private static boolean isBlack(RedBlackTreeNode root){
        boolean ret = true; // null is black
        if(root != null){
            ret = root.isBlack;
        }
        return ret;
    }
    
    /*
    TODO Rotation: swap colors of the two rotated nodes
    */
    
    private static RedBlackTreeNode rotateLeft(RedBlackTreeNode root){
        RedBlackTreeNode newRoot = root;
        if(root != null){
            newRoot = (RedBlackTreeNode) root.right;
            root.right = newRoot.left;
            newRoot.left = root;
            
            boolean temp = root.isBlack;
            root.isBlack = newRoot.isBlack;
            newRoot.isBlack = temp;
        }
        return newRoot;
    }
    private static RedBlackTreeNode rotateRight(RedBlackTreeNode root){
        RedBlackTreeNode newRoot = root;
        if(root != null){
            newRoot = (RedBlackTreeNode) root.left;
            root.left = newRoot.right;
            newRoot.right = root;
            
            boolean temp = root.isBlack;
            root.isBlack = newRoot.isBlack;
            newRoot.isBlack = temp;
        }
        return newRoot;
    }
    
    
    /**
     * Children and parents swap colors.
     * Notice this does not change the number of black nodes in any path
     * Parent must have two children
     * @param root the parent.
     */
    public final void flipColor(RedBlackTreeNode root){
        if(root != null){
            root.isBlack = !root.isBlack;
            ((RedBlackTreeNode)root.left).isBlack = !((RedBlackTreeNode)root.left).isBlack;
            ((RedBlackTreeNode)root.right).isBlack = !((RedBlackTreeNode)root.right).isBlack;          
        }
    }
    
    
    
    // new nodes must be red at the start
    @Override
    protected RedBlackTreeNode createNew(int value){
        return new RedBlackTreeNode(value, false);
    }
    
    public static void main(String[] args){
        RedBlackTreeNode tree = null;
        RedBlackTreeHelper helper = new RedBlackTreeHelper();
        for(int i = 0; i < 10; i++){
            tree = helper.insert(tree, i);
            helper.inOrder(tree, System.out::println);
            System.out.println();
        }
        
        for(int i = 0; i < 10; i++){
            tree = helper.delete(tree, i);
            helper.inOrder(tree, System.out::println);
            System.out.println();
        }
    }
}
