package dataStructures.binarySearchTree;

/**
 * 1. Each node has a color
 * 2. Tree root node must be black
 * 3. Right child must be black
 *    Left can be either red or black
 * 
 * 4. Cannot have two red nodes in a row
 * 
 * 5. Black Balanced Condition:
 *    every path from the root to a null node must have exact same number of black
 *    nodes (color of null is black)
 * 
 * 4 & 5 guarantee that the longest path in the left subtree is at most twice as
 * long as the longest path in the right subtree. More relaxed on balance condition
 * than AVL
 * 
 * 
 * Need to test
 * 
 * @author Matt Crow
 */
public class RedBlackTreeNode extends BinarySearchTreeNode {
    /*
    True: node is black
    False: node is red
    */
    protected boolean isBlack;
    
    public RedBlackTreeNode(int value, boolean isBlack) {
        super(value);
        this.isBlack = isBlack;
    }
    
    public static final RedBlackTreeNode insert(RedBlackTreeNode root, int value){
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
        
        // each check will change its problem to the next one

        // first check for red left child with red right child or mirror
        // and rotate outward
        if(!isBlack((RedBlackTreeNode)newRoot.left) && !isBlack((RedBlackTreeNode)newRoot.left.right)){
            newRoot.left = rotateLeft((RedBlackTreeNode)newRoot.left);
        }
        if(!isBlack((RedBlackTreeNode)newRoot.right) && !isBlack((RedBlackTreeNode)newRoot.right.left)){
            newRoot.right = rotateRight((RedBlackTreeNode)newRoot.right);
        }
        
        // error case #2: check for two outer red descendants
        // will short-circuit evaluate if left is null
        if(!isBlack((RedBlackTreeNode) newRoot.left) && !isBlack((RedBlackTreeNode) newRoot.left.left)){
            newRoot = rotateRight(newRoot);
        }
        if(!isBlack((RedBlackTreeNode) newRoot.right) && !isBlack((RedBlackTreeNode) newRoot.right.right)){
            newRoot = rotateLeft(newRoot);
        }
        
        // left is black, right is red
        if(isBlack((RedBlackTreeNode) newRoot.left) && !isBlack((RedBlackTreeNode) newRoot.right)){
            newRoot = rotateLeft(newRoot);
        }
        
        // error case #3: check for two red children
        if(!isBlack((RedBlackTreeNode) newRoot.left) && !isBlack((RedBlackTreeNode) newRoot.right)){
            flipColor(newRoot);
        }
        
        return newRoot;
    }
    
    private static boolean isBlack(RedBlackTreeNode root){
        boolean ret = true; // null is black
        if(root != null){
            ret = root.isBlack;
        }
        return ret;
    }
    
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
    public static final void flipColor(RedBlackTreeNode root){
        if(root != null){
            root.isBlack = !root.isBlack;
            ((RedBlackTreeNode)root.left).isBlack = !isBlack((RedBlackTreeNode)root.left);
            ((RedBlackTreeNode)root.right).isBlack = !isBlack((RedBlackTreeNode)root.right);          
        }
    }
    
    public static void main(String[] args){
        RedBlackTreeNode tree = null;
        for(int i = 0; i < 10; i++){
            tree = insert(tree, i);
            RedBlackTreeNode.inOrder(tree, System.out::println);
            System.out.println();
        }
    }
}
