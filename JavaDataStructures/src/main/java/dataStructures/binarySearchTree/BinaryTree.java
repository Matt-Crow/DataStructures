package dataStructures.binarySearchTree;

/**
 * Might help de-clutter
 * @author Matt
 */
public interface BinaryTree<T extends Comparable> {
    public void setValue(T value);
    public T getValue();
    
    public void setLeft(BinaryTree<T> left);
    public BinaryTree<T> getLeft();
    
    public void setRight(BinaryTree<T> right);
    public BinaryTree<T> getRight();
}
