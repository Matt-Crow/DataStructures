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
    
    private Prioritizable[] heapify(Prioritizable[] array){
        Prioritizable[] ret = Arrays.copyOf(array, array.length, Prioritizable[].class);
        /*
        Heap-Order property of leaves are automatically satisfied, as a leaf node
        cannot have children to violate this property. Therefore, start heapifying
        from the first non-leaf node.
        */
        int idxOfLastNonLeafNode = (array.length / 2) - 1; // maybe different
        while(idxOfLastNonLeafNode >= 0){
            // sift down the current node into place
            idxOfLastNonLeafNode--;
        }
        return ret;
    }
    
    private Prioritizable[] heapToSortedArray(Prioritizable[] asHeap){
        Prioritizable[] ret = Arrays.copyOf(asHeap, asHeap.length, Prioritizable[].class);
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
        return ret;
    }
    
    public static void main(String[] args){
        HeapSort sorter = new HeapSort();
        Random rng = new Random();
        PrioritizableInteger[] arr = new PrioritizableInteger[10];
        for(int i = 0; i < arr.length; i++){
            arr[i] = new PrioritizableInteger(rng.nextInt(256));
        }
        Prioritizable[] asHeap = sorter.heapify(arr);
        Prioritizable[] sorted = sorter.heapToSortedArray(asHeap);
        for(int i = 0; i < sorted.length; i++){
            System.out.println(sorted[i].toString());
        }
    }
}
