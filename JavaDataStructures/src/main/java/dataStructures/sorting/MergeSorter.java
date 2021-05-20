package dataStructures.sorting;

import dataStructures.priorityQueue.Prioritizable;
import dataStructures.priorityQueue.PrioritizableInteger;
import java.util.Arrays;

/**
 * The general idea of mergesort:
 *      Divide and conquer the process of sorting an array by dividing it into
 *      two sub-arrays, and conquer by merging them back together once they are
 *      sorted.
 *      
 * @author Matt Crow
 */
public class MergeSorter {
    
    public final void mergeSort(Prioritizable[] array){
        mergeSort(array, 0, array.length);
    }
    
    // sorts the interval [min, max)
    private void mergeSort(Prioritizable[] array, int min, int max){
        if(max - min <= 1){ // don't sort just 1 element
            return;
        }
        
        int mid = (max + min) / 2;
        
        mergeSort(array, min, mid);
        mergeSort(array, mid, max);
        // [min, mid) and [mid, max) are now sorted
        
        // merge result
        int leftQueue = min;
        int rightQueue = mid;
        int mergedIdx = 0;
        Prioritizable[] merged = new Prioritizable[max - min];
        while(mergedIdx < merged.length && leftQueue < mid && rightQueue < max){
            if(array[leftQueue].getPriority() > array[rightQueue].getPriority()){
                merged[mergedIdx] = array[rightQueue];
                rightQueue++;
            } else {
                merged[mergedIdx] = array[leftQueue];
                leftQueue++;
            }
            mergedIdx++;
        }
        // By now, one queue is empty
        
        
        // Empty whichever queue is not empty
        
        while(mergedIdx < merged.length && leftQueue < mid){
            merged[mergedIdx] = array[leftQueue];
            leftQueue++;
            mergedIdx++;
        }
        
        while(mergedIdx < merged.length && rightQueue < max){
            merged[mergedIdx] = array[rightQueue];
            rightQueue++;
            mergedIdx++;
        }
        
        // graft the merged array back into the original
        for(mergedIdx = 0; mergedIdx < merged.length; mergedIdx++){
            array[min + mergedIdx] = merged[mergedIdx];
        }
    }
    
    public static void main(String[] args){
        int count = 100;
        PrioritizableInteger[] unsorted = new PrioritizableInteger[count];
        int[] is = new int[count];
        for(int i = 0; i < is.length; i++){
            unsorted[i] = new PrioritizableInteger(count - 1 - i);
        }
        
        System.out.println(Arrays.toString(unsorted));
        new MergeSorter().mergeSort(unsorted);
        System.out.println(Arrays.toString(unsorted));
    }
}
