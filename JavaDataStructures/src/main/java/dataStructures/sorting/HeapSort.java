package dataStructures.sorting;

import dataStructures.priorityQueue.Prioritizable;
import dataStructures.priorityQueue.PrioritizableInteger;
import java.util.Arrays;
import java.util.Random;

/**
 * General idea behind Heap Sort:
 * - take an array, and convert it into a heap (nlogn)
 * - use deleteMin or deleteMax to sort (nlogn)
 * 
 * Very space efficient
 * 
 * @author Matt
 */
public class HeapSort {
    private final boolean sortLowToHigh;
    
    public HeapSort(boolean sortLowToHigh){
        this.sortLowToHigh = sortLowToHigh;
    }
    
    
    private void heapify(Prioritizable[] array){
        /*
        Heap-Order property of leaves are automatically satisfied, as a leaf node
        cannot have children to violate this property. Therefore, start heapifying
        from the first non-leaf node.
        */
        int lastLeaf = array.length - 1;
        int idxOfLastNonLeafNode = (lastLeaf - 1) / 2;
        while(idxOfLastNonLeafNode >= 0){
            // sift down the current node into place
            siftDown(array, idxOfLastNonLeafNode, array.length);
            
            idxOfLastNonLeafNode--;
        }
    }
    
    private void heapToSortedArray(Prioritizable[] asHeap){
        /*
        Use a max heap to sort from smallest to largest,
        and a min heap to sort from largest to smallest
        
        to conserve space, deleteMin swaps first and last elements instead of
        just overriding first with last. So, for example:
        (| marks the end of the heap)
        a, c, b |
        b, c | a
        c | b, a
        | c, b, a <== hey look, sorted!
        Still need to still sift down after each iteration
        */
        for(int i = asHeap.length - 1; i > 0; i--){
            swap(asHeap, 0, i); // first becomes last
            siftDown(asHeap, 0, i); 
            // sift down, but ignore the elements we've sifted down
        }
    }
    
    /**
     * 
     * @param array
     * @param idxToSiftDown
     * @param stopIdx the size of the heap, not the array 
     */
    private void siftDown(Prioritizable[] array, int idxToSiftDown, int stopIdx){
        int parent = idxToSiftDown;
        int left = 2 * parent + 1;
        int right = 2 * parent + 2;
        int newParentIdx;
        while(
            (left < stopIdx && shouldSwap(array, parent, left))
            || (right < stopIdx && shouldSwap(array, parent, right))
        ){
            newParentIdx = getChildToSwapWith(array, parent, stopIdx);
            swap(array, parent, newParentIdx);
            parent = newParentIdx;
            left = 2 * parent + 1;
            right = 2 * parent + 2;
        }
    }
    
    private boolean shouldSwap(Prioritizable[] array, int parentIdx, int childIdx){
        boolean shouldSwap = false;
        if(this.sortLowToHigh && array[parentIdx].getPriority() < array[childIdx].getPriority()){
            // to sort low to high, sort heap from high to low
            shouldSwap = true;
        } else if(!this.sortLowToHigh && array[parentIdx].getPriority() > array[childIdx].getPriority()){
            shouldSwap = true;
        }
        return shouldSwap;
    }
    
    private void swap(Prioritizable[] array, int a, int b){
        Prioritizable temp = array[a];
        array[a] = array[b];
        array[b] = temp;
    }
    
    /**
     * 
     * @param array
     * @param parentIdx
     * @param stopIdx the size of the heap - not the array
     * @return 
     */
    private int getChildToSwapWith(Prioritizable[] array, int parentIdx, int stopIdx){
        int leftIdx = 2 * parentIdx + 1;
        int rightIdx = 2 * parentIdx + 2;
        int better = leftIdx;
        
        if(rightIdx >= stopIdx){
            better = leftIdx;
        } else if(sortLowToHigh && array[leftIdx].getPriority() < array[rightIdx].getPriority()){
            // to sort low to high, sort heap from high to low
            better = rightIdx;
        } else if(sortLowToHigh && array[leftIdx].getPriority() > array[rightIdx].getPriority()){
            better = leftIdx;
        } else if(!sortLowToHigh && array[leftIdx].getPriority() < array[rightIdx].getPriority()){
            better = leftIdx;
        } else if(!sortLowToHigh && array[leftIdx].getPriority() > array[rightIdx].getPriority()){
            better = rightIdx;
        } else {
            better = leftIdx;
        }
        
        return better;
    }
    
    public static void main(String[] args){
        HeapSort sorter = new HeapSort(true);
        Random rng = new Random();
        PrioritizableInteger[] arr = new PrioritizableInteger[10];
        for(int i = 0; i < arr.length; i++){
            arr[i] = new PrioritizableInteger(rng.nextInt(256));
        }
        System.out.printf("Before heapifying: %s\n", Arrays.toString(arr));
        sorter.heapify(arr);
        System.out.printf("Before sorting: %s\n", Arrays.toString(arr));
        sorter.heapToSortedArray(arr);
        System.out.printf("After sorting: %s\n", Arrays.toString(arr));
    }
}
