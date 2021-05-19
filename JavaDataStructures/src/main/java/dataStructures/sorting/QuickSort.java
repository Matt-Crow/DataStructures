package dataStructures.sorting;

import dataStructures.priorityQueue.Prioritizable;
import dataStructures.priorityQueue.PrioritizableInteger;
import java.util.Arrays;
import java.util.Random;

/**
 *
 * @author Matt
 */
public class QuickSort {
    
    public QuickSort(){
        
    }
    
    /**
     * 
     * @param min inclusive
     * @param max exclusive
     * @return 
     */
    private int medianIdx(Prioritizable[] array, int min, int max){
        int mid = (min + max) / 2;
        int minVal = array[min].getPriority();
        int midVal = array[mid].getPriority();
        int maxVal = array[max - 1].getPriority();
        int bestIdx = -1;
        
        if(
            (midVal <= minVal && minVal <= maxVal) ||
            (maxVal <= minVal && minVal <= midVal)
        ){
            bestIdx = min;
        } else if(
            (midVal <= maxVal && maxVal <= minVal) ||
            (minVal <= maxVal && maxVal <= midVal)
        ){
            bestIdx = max;
        } else {
            bestIdx = mid;
        }
        
        return bestIdx;
    }
    
    private void swap(Prioritizable[] array, int a, int b){
        Prioritizable temp = array[a];
        array[a] = array[b];
        array[b] = temp;
    }
    
    /**
     * Sort the array in ascending order
     * @param array
     * @param min minimum index - inclusive
     * @param max maximum index - exclusive
     */
    private void quickSort(Prioritizable[] array, int min, int max) {
        if(max - min <= 1){ // don't sort one-element sets
            return;
        }
        // choose pivot. Can be any index within [min, max)
        int pivotIdx = medianIdx(array, min, max - 1);
        Prioritizable pivot = array[pivotIdx];
        
        // move pivot to the end to make things easier
        swap(array, pivotIdx, max - 1);
        
        // partition values smaller than pivot to its left
        // partition values greater than pivot to its right
        int i = min;
        int j = max - 2; // left of pivot
        while(i <= j){ // exit when i and j cross. VERY IMPORTANT: i can equal j
            // don't move i or j if they point to same priority as the pivot
            //                            do not use <= here! a[i] = p is problematic
            while(i <= max && array[i].getPriority() < pivot.getPriority()){
                i++;
            } 
            /*
            by now, i points to a problematic value or the pivot. If it points to
            the pivot, that means the pivot is the pivot is the largest value in
            this portion of the array.
            */
            
            // needs the ">= min", not "> min"
            //                            do not use >= here!
            while(j >= min && array[j].getPriority() > pivot.getPriority()){
                j--;
            }
            /*
            by now, both i and j point to problematic values, or j has fallen 
            off the left end of the array. If j == min - 1, that means there are
            no values less than the pivot
            */
            if(i <= j){
                // a[i] is greater than pivot, a[j] is lesser, so swap them 
                swap(array, i, j);
                i++;
                j--;
            }
        }          
        // array[i] is now greater than the pivot
        swap(array, max - 1, i);
        // pivot is now in its proper place
        
        
        /*
        System.out.printf("[%d, %d)\n", min, max);
        System.out.printf("Pivot %d Index %d is set: %s\n", pivot.getPriority(), i, Arrays.toString(array));
        System.out.printf("[%d, %d) U [%d,%d)\n\n", min, i, i + 1, max);
        */
        
        // call quicksort on the left partition
        quickSort(array, min, i);
        // call quicksort on the right partition
        quickSort(array, i + 1, max);
    }
    
    public final void quickSort(Prioritizable[] array){
        quickSort(array, 0, array.length);
    }
    
    public static void main(String[] args){
        int count = 100;
        PrioritizableInteger[] unsorted = new PrioritizableInteger[count];
        Random rng = new Random();
        for(int i = 0; i < unsorted.length; i++){
            unsorted[i] = new PrioritizableInteger(rng.nextInt(5));
        }
        
        System.out.println(Arrays.toString(unsorted));
        new QuickSort().quickSort(unsorted);
        System.out.println(Arrays.toString(unsorted));
    }
}
