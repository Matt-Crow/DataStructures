package dataStructures.notOnMidterm;

import java.util.ArrayList;

/**
 * A Binary Heap is an implementation of Priority Queue,
 * consumes far less memory than a Binary Search Tree
 * 
 * Visually, looks like a Complete Tree:
 *       (1)
 *     /     \
 *   (2)     (3)
 *   / \    /
 * (4) (5) (6)
 * 
 * @author Matt
 */
public class BinaryHeap implements PriorityQueue {
    private final ArrayList<Prioritizable> contents;
    private int nextEmptyIdx;
    
    public BinaryHeap(){
        contents = new ArrayList<>();
        nextEmptyIdx = 0;
    }
    
    public final boolean isEmpty(){
        return nextEmptyIdx == 0;
    }
    
    private boolean hasParent(int idx){
        int pIdx = parentIdx(idx);
        return 0 >= pIdx && pIdx < nextEmptyIdx;
    }
    
    private boolean hasLeftChild(int idx){
        return leftChildIdx(idx) <= nextEmptyIdx;
    }
    
    private boolean hasRightChild(int idx){
        return rightChildIdx(idx) <= nextEmptyIdx;
    }
    
    private int parentIdx(int idx){
        return (idx - 1) / 2;
    }
    
    private int leftChildIdx(int idx){
        return 2 * idx + 1;
    }
    
    private int rightChildIdx(int idx){
        return 2 * idx + 2;
    }
    
    private int getValue(int idx){
        return contents.get(idx).getPriority();
    }
    
    private int getLeftValue(int idx){
        return getValue(leftChildIdx(idx));
    }
    
    private int getRightValue(int idx){
        return getValue(rightChildIdx(idx));
    }
    
    
    @Override
    public void add(Prioritizable newObj) {
        contents.ensureCapacity(nextEmptyIdx + 1);
        contents.set(nextEmptyIdx, newObj);
        nextEmptyIdx++;
        // todo: sift up   
    }

    @Override
    public Prioritizable dequeueHighestPriority() {
        Prioritizable ret = null;
        if(!isEmpty()){
            ret = contents.get(0);
            contents.set(0, contents.get(nextEmptyIdx - 1)); // last becomes first
            nextEmptyIdx--;
            // todo: sift down
        }
        return ret;
    }
    
    public static void main(String[] args){
        BinaryHeap heap = new BinaryHeap();
        for(int i = 0; i < 10; i++){
            heap.add(new PrioritizableInteger(i));
        }
        
        while(!heap.isEmpty()){
            System.out.println(heap.dequeueHighestPriority());
        }
    }

}
