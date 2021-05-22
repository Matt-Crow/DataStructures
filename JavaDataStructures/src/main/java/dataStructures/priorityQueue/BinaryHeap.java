package dataStructures.priorityQueue;

import java.util.ArrayList;

/**
 * A Binary Heap is an implementation of Priority Queue,
 * consumes far less memory than a Binary Search Tree
 * 
 * Structure Property: Visually, looks like a Complete Tree:
 *       (1)
 *     /     \
 *   (2)     (3)
 *   / \    /
 * (4) (5) (6)
 * 
 * Heap Order Property:
 * 
 *  min heap: (default)
 *      the priority of a node's children will be no less than its own
 *      (x)
 *     /   \
 *   (x)  (x+n)
 * 
 *  max heap:
 *      the priority of a node's children will be no greater than its own
 *      (x)
 *     /   \
 *   (x)  (x-n)
 * 
 * @author Matt Crow
 */
public class BinaryHeap implements PriorityQueue {
    private final ArrayList<Prioritizable> contents;
    private int nextEmptyIdx;
    private final boolean isMinHeap;
    
    /**
     * 
     * @param isMinHeap : if true, this will dequeue lower numerical priorities
     * first. If false, dequeues higher numerical priorities first
     */
    public BinaryHeap(boolean isMinHeap){
        contents = new ArrayList<>();
        nextEmptyIdx = 0;
        this.isMinHeap = isMinHeap;
    }
    
    public BinaryHeap(boolean isMinHeap, int initialCapacity){
        this(isMinHeap);
        contents.ensureCapacity(initialCapacity); // saves time when resizing
    }
    
    public final boolean isEmpty(){
        return nextEmptyIdx == 0;
    }
    
    /**
     * Inserts the given object in the first empty index of the heap,
     * then repeatedly swaps it with it's parent until it is in its proper place.
     * 
     * O(log(n))
     * 
     * @param newObj the new object to sift up
     */
    @Override
    public void add(Prioritizable newObj) {
        contents.ensureCapacity(nextEmptyIdx + 1);
        // https://stackoverflow.com/questions/7688151/java-arraylist-ensurecapacity-not-working
        while(contents.size() < nextEmptyIdx + 1){
            contents.add(null);
        }
        contents.set(nextEmptyIdx, newObj);
        nextEmptyIdx++;
        
        /*
        sift up by swapping the newly inserted value with its parent until the
        child is in the correct position relative to its parent. This ensures 
        the heap order property is maintained.
        
        For a min heap, a heavier parent will sink into the heap.
        For a max heap, a lighter parent will sink into the heap.
        */
        int childIdx = nextEmptyIdx - 1;
        int parentIdx = (childIdx - 1) / 2;
        while(parentIdx >= 0 && shouldSwap(parentIdx, childIdx)){
            swap(childIdx, parentIdx);
            childIdx = parentIdx;
            parentIdx = (childIdx - 1) / 2;
            //System.out.println(this);
        }
    }
    
    private boolean shouldSwap(int parentIdx, int childIdx){
        return (isMinHeap && getValue(parentIdx) > getValue(childIdx))
            || (!isMinHeap && getValue(parentIdx) < getValue(childIdx)); 
    }
    
    private void swap(int idx1, int idx2){
        Prioritizable temp = contents.get(idx1);
        contents.set(idx1, contents.get(idx2));
        contents.set(idx2, temp);
    }
    
    private int getValue(int idx){
        return contents.get(idx).getPriority();
    }

    /**
     * Removes the first value in the heap, replaces it with the last value in
     * the heap, and swaps that new first value into place.
     * 
     * @return the highest priority object in the heap 
     */
    @Override
    public Prioritizable dequeueHighestPriority() {
        if(this.isEmpty()){
            throw new UnsupportedOperationException("Cannot dequeue highest priority from an empty BinaryHeap");
        }
        Prioritizable ret = contents.get(0);
        contents.set(0, contents.get(nextEmptyIdx - 1)); // last becomes first
        nextEmptyIdx--;
        
        int currIdx = 0;
        int left = 1;
        int right = 2;
        
        // sift down
        while(
            (left < nextEmptyIdx && shouldSwap(currIdx, left )) || 
            (right< nextEmptyIdx && shouldSwap(currIdx, right))
        ){
            if(isMinHeap){
                /*
                Parent is larger than at least one of its children
                swap with the smaller child
                */
                if(right < nextEmptyIdx && getValue(left) > getValue(right)){
                    swap(currIdx, right);
                    currIdx = right;
                } else {
                    swap(currIdx, left);
                    currIdx = left;
                }
            } else { // is max heap
                /*
                Parent is smaller than at least one of its childen
                swap with the larger child
                */
                if(right < nextEmptyIdx && getValue(left) < getValue(right)){
                    swap(currIdx, right);
                    currIdx = right;
                } else {
                    swap(currIdx, left);
                    currIdx = left;
                }
            }
            left = 2 * currIdx + 1;
            right =2 * currIdx + 2;
        }
        return ret;
    }
    
    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder();
        int currWidth = 0;
        int maxWidth = 1;
        for(int i = 0; i < this.nextEmptyIdx; i++){
            sb.append(Integer.toString(getValue(i)));
            currWidth++;
            if(currWidth == maxWidth){
                maxWidth *= 2;
                currWidth = 0;
                sb.append("\n");
            } else if(i < this.nextEmptyIdx - 1){
                sb.append(", ");
            }
        }
        return sb.toString();
    }
    
    public static void main(String[] args){
        BinaryHeap heap = new BinaryHeap(true);
        for(int i = 10; i > 0; i--){
            heap.add(new PrioritizableInteger(i));
            System.out.printf("Inserted %d:\n", i);
            System.out.println(heap);
        }
        
        while(!heap.isEmpty()){
            System.out.printf("Dequeued %s\n", heap.dequeueHighestPriority().toString());
            System.out.println(heap);
        }
    }

}
