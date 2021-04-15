package dataStructures.sorting;

import dataStructures.priorityQueue.Prioritizable;
import dataStructures.priorityQueue.PrioritizableInteger;
import java.util.Arrays;

/**
 *
 * @author Matt
 */
public class MergeSort {
    
    // inclusive of min, exclusive of max
    public final void mergeSort(Prioritizable[] array, int min, int max){
        if(max <= min){
            return;
        }
        
        int mid = (max + min) / 2;
        
        mergeSort(array, min, mid);
        mergeSort(array, mid + 1, max);
        
        // merge result
        int i = min;
        int j = mid + 1;
        int newIdx = 0;
        Prioritizable[] merged = new Prioritizable[max - min];
        while(newIdx < merged.length && i <= mid && j <= max){
            if(array[i].getPriority() > array[j].getPriority()){
                merged[newIdx] = array[j];
                j++;
            } else {
                merged[newIdx] = array[i];
                i++;
            }
            newIdx++;
        }
        
        while(newIdx < merged.length && i <= mid){
            merged[newIdx] = array[i];
            i++;
            newIdx++;
        }
        
        while(newIdx < merged.length && j <= max){
            merged[newIdx] = array[j];
            j++;
            newIdx++;
        }
        
        for(newIdx = 0; newIdx < merged.length; newIdx++){
            array[newIdx + min] = merged[newIdx];
        }
    }
    
    public static void main(String[] args){
        PrioritizableInteger[] unsorted = new PrioritizableInteger[10];
        int[] is = new int[]{9, 0, 1, 3, 4, 6, 8, 2, 5, 7};
        for(int i = 0; i < is.length; i++){
            unsorted[i] = new PrioritizableInteger(is[i]);
        }
        
        System.out.println(Arrays.toString(unsorted));
        new MergeSort().mergeSort(unsorted, 0, unsorted.length - 1);
        System.out.println(Arrays.toString(unsorted));
    }
}
