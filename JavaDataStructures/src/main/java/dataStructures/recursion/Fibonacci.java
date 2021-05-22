package dataStructures.recursion;

import java.util.function.Function;

/**
 * This program displays some important rules with recursion, and why recursive
 * Fibonacci is not a good idea
 * 
 * @author Matt Crow
 */

public class Fibonacci {
    private static final long THRESHOLD = (long)Math.pow(2, 31);
    private static final String SEARCH_MSG = "Searching for the first non-32 bit Fibonacci number using %s...%n";
    private static final String FOUND_MSG = "found fib(%d) = %d in %d nanoseconds%n";

    private static void runAndComputeTime(String msg, Function<Integer, Long> fibFunction){
        //Time-measurement variables
        long startTime = 0;
        long endTime = 0;
        long duration = 0;

        //Search variables. Initialize all to signal "not found"
        int largeEnoughN = -1;
        long fibOfLargeEnoughN = -1;
        long currFibNumber = -1;

        System.out.printf(SEARCH_MSG, msg);
        startTime = System.nanoTime();
        // Linear search for the first non-32 bit Fibonacci number
        for(int n = 0; fibOfLargeEnoughN == -1; n++){
            currFibNumber = fibFunction.apply(n);
            if(currFibNumber > THRESHOLD){
                endTime = System.nanoTime();
                duration = endTime - startTime;
                largeEnoughN = n;
                fibOfLargeEnoughN = currFibNumber;
            }
        }
        System.out.printf(FOUND_MSG, largeEnoughN, fibOfLargeEnoughN, duration);
    }

    private static long fibRecur(int n){
        long ret = 1; // base case
        if(n > 1){ // we're zero-indexing Fibonacci numbers
            ret = fibRecur(n - 1) + fibRecur(n - 2);
        } // else, base case holds
        return ret;
    }

    private static long fibIter(int n){ // Complexity Analysis
        long ret = 1;                   // 1
        long prev = 1;                  // 1
        long prevPrev = 1;              // 1
        for(int i = 1; i < n; i++){     // By Rule 1: 3n
            ret = prev + prevPrev;      // 1
            prevPrev = prev;            // 1
            prev = ret;                 // 1
        }
        return ret;                     // 1
    }                                   // total is 3n + 4, which is O(n)
    //           as leading constants and lower order terms are discarded

    public static void main(String[] args){
        runAndComputeTime("recursion", Fibonacci::fibRecur);
        runAndComputeTime("iteration", Fibonacci::fibIter);
    }
}
