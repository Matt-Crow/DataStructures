package dataStructures.misc;

/**
 *
 * @author Matt
 */
public class PrimeNumberService {
    public final int largestPrimeLessThan(int i){
        int largestPrime = i;
        if(largestPrime != 2 && (largestPrime & 1) == 0){ // even
            largestPrime--;
        }
        
        while(!isPrime(largestPrime)){
            largestPrime -= 2;
        }
        
        return largestPrime;
    }
    
    public final boolean isPrime(int i){
        if(i != 2 && (i & 1) == 0){
            return false; // catch evens first
        }
        boolean isPrime = true;
        for(int num = i - 2; num > 2 && isPrime; num -= 2){
            if((i % num) == 0){
                isPrime = false;
            }
        }
        return isPrime;
    }
    
    public static void main(String[] args){
        PrimeNumberService s = new PrimeNumberService();
        
        for(int i = 1; i < 100000; i++){
            if(s.isPrime(i)){
                System.out.printf("%d ", i);
            }
        }
    }
}
