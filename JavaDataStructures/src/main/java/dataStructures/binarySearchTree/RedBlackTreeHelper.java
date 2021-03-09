package dataStructures.binarySearchTree;

/**
 *
 * @author Matt
 */
public class RedBlackTreeHelper<T extends Comparable> extends BinarySearchTreeHelper<T, RedBlackTreeNode<T>>{
    
    @Override
    public final RedBlackTreeNode<T> insert(RedBlackTreeNode<T> root, T value){
        RedBlackTreeNode<T> newRoot = super.insert(root, value);
        if(newRoot != null){
            // first check for red left child with red right child or mirror
            //  and rotate outward
            // second check for red left child with red left child or mirror
            //  and rotate ???
            if(!((RedBlackTreeNode<T>)(newRoot.left)).isBlack){
                // todo: if root has a red child with a red child,
                // rotate and swap colors between root and old child
            }
            if(newRoot.right != null && !((RedBlackTreeNode<T>)(newRoot.right)).isBlack){
                // right child is red
                if(!((RedBlackTreeNode<T>)(newRoot.left)).isBlack){
                    // if both children are red, flip colors
                    flipColor(root);
                }
            }
        }
        return newRoot;
    }
    
    /*
    Rotation: swap colors of the two rotated nodes
    */
    
    /**
     * Children and parents swap colors.
     * Notice this does not change the number of black nodes in any path
     * Parent must have two children
     * @param root the parent.
     */
    public final void flipColor(RedBlackTreeNode<T> root){
        if(root != null){
            root.isBlack = !root.isBlack;
            ((RedBlackTreeNode<T>)root.left).isBlack = !((RedBlackTreeNode<T>)root.left).isBlack;
            ((RedBlackTreeNode<T>)root.right).isBlack = !((RedBlackTreeNode<T>)root.right).isBlack;          
        }
    }
    
    public static void main(String[] args){
        RedBlackTreeNode<String> tree = null;
        RedBlackTreeHelper<String> helper = new RedBlackTreeHelper<>();
        for(String arg : args){
            tree = helper.insert(tree, arg);
            helper.inOrder(tree, System.out::println);
            System.out.println();
        }
    }
    
    // new nodes must be red at the start
    @Override
    protected RedBlackTreeNode<T> createNew(T value){
        return new RedBlackTreeNode<>(value, false);
    }
}
