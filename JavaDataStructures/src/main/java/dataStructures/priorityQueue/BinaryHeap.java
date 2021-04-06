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
 * @author Matt
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
    
    public final boolean isEmpty(){
        return nextEmptyIdx == 0;
    }
    
    private boolean hasParent(int idx){
        int pIdx = parentIdx(idx);
        return 0 <= pIdx && pIdx < nextEmptyIdx;
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
    
    private int getParentValue(int idx){
        return getValue(parentIdx(idx));
    }
    
    private int getLeftValue(int idx){
        return getValue(leftChildIdx(idx));
    }
    
    private int getRightValue(int idx){
        return getValue(rightChildIdx(idx));
    }
    
    private void swap(int idx1, int idx2){
        Prioritizable temp = contents.get(idx1);
        contents.set(idx1, contents.get(idx2));
        contents.set(idx2, temp);
    }
    
    private boolean shouldSwap(int parentIdx, int childIdx){
        return (isMinHeap && getValue(parentIdx) > getValue(childIdx))
            || (!isMinHeap && getValue(parentIdx) < getValue(childIdx)); 
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
        contents.ensureCapacity(nextEmptyIdx);
        contents.add(nextEmptyIdx, newObj);
        nextEmptyIdx++;
        int currIdx = nextEmptyIdx - 1;
        //System.out.println(this);
        while(hasParent(currIdx) && shouldSwap(parentIdx(currIdx), currIdx)){
            swap(currIdx, parentIdx(currIdx));
            currIdx = parentIdx(currIdx);
            //System.out.println(this);
        }
    }

    /**
     * Removes the first value in the heap, replaces it with the last value in
     * the heap, and swaps that new first value into place.
     * 
     * @return the highest priority object in the heap 
     */
    @Override
    public Prioritizable dequeueHighestPriority() {
        Prioritizable ret = null;
        if(!isEmpty()){
            ret = contents.get(0);
            contents.set(0, contents.get(nextEmptyIdx - 1)); // last becomes first
            nextEmptyIdx--;
            // todo: clean up
            int currIdx = 0;
            while(
                (hasLeftChild(currIdx) && shouldSwap(currIdx, leftChildIdx(currIdx)))
                || (hasRightChild(currIdx) && shouldSwap(currIdx, rightChildIdx(currIdx)))
            ){
                if(isMinHeap){
                    if(hasLeftChild(currIdx) && hasRightChild(currIdx) && getLeftValue(currIdx) > getRightValue(currIdx)){
                        swap(currIdx, rightChildIdx(currIdx));
                        currIdx = rightChildIdx(currIdx);
                    } else if(hasLeftChild(currIdx) && hasRightChild(currIdx)){
                        swap(currIdx, leftChildIdx(currIdx));
                        currIdx = leftChildIdx(currIdx);
                    } else if(hasLeftChild(currIdx)){
                        swap(currIdx, leftChildIdx(currIdx));
                        currIdx = leftChildIdx(currIdx);
                    } else { // just right child
                        swap(currIdx, rightChildIdx(currIdx));
                        currIdx = rightChildIdx(currIdx);
                    }
                } else {
                    if(hasLeftChild(currIdx) && hasRightChild(currIdx) && getLeftValue(currIdx) < getRightValue(currIdx)){
                        swap(currIdx, rightChildIdx(currIdx));
                        currIdx = rightChildIdx(currIdx);
                    } else if(hasLeftChild(currIdx) && hasRightChild(currIdx)){
                        swap(currIdx, leftChildIdx(currIdx));
                        currIdx = leftChildIdx(currIdx);
                    } else if(hasLeftChild(currIdx)){
                        swap(currIdx, leftChildIdx(currIdx));
                        currIdx = leftChildIdx(currIdx);
                    } else { // just right child
                        swap(currIdx, rightChildIdx(currIdx));
                        currIdx = rightChildIdx(currIdx);
                    }
                }
            }
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
