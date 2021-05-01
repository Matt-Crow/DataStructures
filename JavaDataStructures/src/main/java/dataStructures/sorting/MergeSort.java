package dataStructures.sorting;

import dataStructures.priorityQueue.Prioritizable;
import dataStructures.priorityQueue.PrioritizableInteger;
import java.util.Arrays;

/**
 *
 * @author Matt
 */
public class MergeSort {
    
    // sorts the interval [min, max)
    public final void mergeSort(Prioritizable[] array, int min, int max){
        if(max - min <= 1){ // don't sort just 1 element
            return;
        }
        
        int mid = (max + min) / 2;
        
        mergeSort(array, min, mid);
        mergeSort(array, mid, max);
        
        // merge result
        int i = min;
        int j = mid;
        int newIdx = 0;
        Prioritizable[] merged = new Prioritizable[max - min];
        while(newIdx < merged.length && i < mid && j < max){
            if(array[i].getPriority() > array[j].getPriority()){
                merged[newIdx] = array[j];
                j++;
            } else {
                merged[newIdx] = array[i];
                i++;
            }
            newIdx++;
        }
        
        while(newIdx < merged.length && i < mid){
            merged[newIdx] = array[i];
            i++;
            newIdx++;
        }
        
        while(newIdx < merged.length && j < max){
            merged[newIdx] = array[j];
            j++;
            newIdx++;
        }
        
        for(newIdx = 0; newIdx < merged.length; newIdx++){
            array[newIdx + min] = merged[newIdx];
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
        new MergeSort().mergeSort(unsorted, 0, unsorted.length);
        System.out.println(Arrays.toString(unsorted));
    }
}
