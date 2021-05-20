package dataStructures.sorting;

import dataStructures.priorityQueue.Prioritizable;
import dataStructures.priorityQueue.PrioritizableInteger;
import java.util.Arrays;
import java.util.Random;

/**
 * General idea behind Heap Sort:
 * - take an array, and convert it into a heap (nlogn)
 * - finding the min/max value becomes Theta(1)
 * - use deleteMin or deleteMax to sort (nlogn)
 * 
 * Very space efficient
 * 
 * @author Matt Crow
 */
public class HeapSorter {
    
    public final void heapSort(Prioritizable[] array){
        heapify(array);
        heapToSortedArray(array);
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
        for(int size = asHeap.length - 1; size > 0; size--){
            swap(asHeap, 0, size); // first becomes last
            siftDown(asHeap, 0, size); 
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
        while( // to sort low to high, sort heap from high to low
            (left  < stopIdx && array[parent].getPriority() < array[left].getPriority()) || 
            (right < stopIdx && array[parent].getPriority() < array[right].getPriority())
        ){
            if(right < stopIdx && array[left].getPriority() < array[right].getPriority()){
                swap(array, parent, right);
                parent = right;
            } else {
                swap(array, parent, left);
                parent = left;
            }
            left = 2 * parent + 1;
            right = 2 * parent + 2;
        }
    }
    
    private void swap(Prioritizable[] array, int a, int b){
        Prioritizable temp = array[a];
        array[a] = array[b];
        array[b] = temp;
    }
    
    public static void main(String[] args){
        HeapSorter sorter = new HeapSorter();
        Random rng = new Random();
        PrioritizableInteger[] arr = new PrioritizableInteger[100];
        for(int i = 0; i < arr.length; i++){
            arr[i] = new PrioritizableInteger(rng.nextInt(256));
        }
        System.out.printf("Before heapifying: %s\n", Arrays.toString(arr));
        sorter.heapSort(arr);
        System.out.printf("After sorting: %s\n", Arrays.toString(arr));
    }
}
