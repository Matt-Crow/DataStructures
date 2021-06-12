package dataStructures.hashing;

import dataStructures.priorityQueue.Prioritizable;
import dataStructures.priorityQueue.PrioritizableInteger;
import java.util.Objects;
import java.util.function.BiFunction;

/**
 * Open addressing techniques: can use instead of separate chaining
 *  - linear probing
 *  - quadratic probing
 *  - double hashing
 * 
 * Rehashing: once a hash table is at ~ 80% capacity, insert all values into a
 * new, larger table, then switch to using the new table
 * 
 * The capacity of the hash array MUST BE A PRIME NUMBER for most hashing 
 * techniques to work. This prevents techniques such as double hashing from 
 * cycling between a finite series of values when trying to find an open address.
 * For example, given H(x, i) = (h(x) + i*g(x)) % 10, suppose h(n) = 0 and g(n) = 5.
 * If the indeces 0 and 5 are already occupied, n cannot be inserted into the table,
 * as the range for H(n, i) = {0, 5}. Choosing H(x, i) = (h(x) + i*g(x)) % 11 resolves
 * this issue, as H(n, i) would then output the series (0, 5, 10, 4, 9, 3, ...)
 * @author Matt Crow
 */
public class HashTable {
    // must be of constant size
    private final int doubleHashSize;
    private final Prioritizable[] keys;
    private final Object[] values; 
    private final int[] valuesWithHash; // how many values in the table have a given hash
    /*
    can do LinkedList<Object>[]. See C notes. "Separate chaining". Find becomes 
    O(logn). Commonly used method. Takes more memory, but that's only a problem on
    smaller systems
    */
    
    public HashTable(int size){
        doubleHashSize = new PrimeNumberService().largestPrimeLessThan(size);
        keys = new Prioritizable[size];
        values = new Object[size];
        valuesWithHash = new int[size];
    }
    
    public final void put(Prioritizable key, Object value){
        valuesWithHash[hash(key)]++; // one new key with the given hash
        int idx = getOpenIdx(key);
        keys[idx] = key;
        values[idx] = value;
    }
    
    public final boolean has(Prioritizable key){
        return getIdx(key) != -1;
    }
    
    public final Object get(Prioritizable key){
        int idx = getIdx(key);
        return values[idx];
    }
    
    public final void delete(Prioritizable key){
        if(has(key)){
            valuesWithHash[hash(key)]--;
            int idx = getIdx(key);
            keys[idx] = null;
            values[idx] = null;
        }
    }
    
    /**
     * Maps key to an index in the table
     * 
     * Need to ensure the hash function utilizes the entire table
     * 
     * @param key
     * @return 
     */
    private int hash(Prioritizable key){
        return (key == null) ? -1 : key.getPriority() % keys.length;
    }
    
    /**
     * Checks for collisions
     * 
     * @param key
     * @return 
     */
    private int getIdx(Prioritizable key){
        int hash = hash(key);
        int idx = -1;
        
        if(keys[hash] == null || keys[hash].equals(key)){ // empty or equal
            idx = hash;
        } else {
            // collision.
            idx = doubleHash(hash, key, valuesWithHash[hash] + 1, this::findValue);
        }
        
        if(idx == -1){
            // still not found
            throw new RuntimeException(String.format("Failed to find an index for key %s\n", key));
        }
        
        return idx;
    }
    
    private int getOpenIdx(Prioritizable key){
        int hash = hash(key);
        int idx = -1;
        
        if(keys[hash] == null || keys[hash].equals(key)){ // empty or equal
            idx = hash;
        } else {
            // collision.
            idx = doubleHash(hash, key, valuesWithHash[hash] + 1, this::findEmpty);
        }
        
        if(idx == -1){
            // still not found
            throw new RuntimeException(String.format("Failed to find an open index for key %s\n", key));
        }
        
        return idx;
    }
    
    // doesn't work for remove
    // better at finding empty spaces
    private int linearProbe(int fromIdx, Prioritizable key, int maxTries, BiFunction<Integer, Prioritizable, Boolean> matcher){
        int idx = -1;
        int temp;
        for(int attempt = 1; attempt <= maxTries && idx == -1; attempt++){
            temp = (fromIdx + attempt) % keys.length;
            
            if(matcher.apply(temp, key)){
                idx = temp;
            }
            
            if(hash(keys[temp]) != hash(key)){
                maxTries++; // that check doesn't count
            }
        }
        return idx;
    }
    // doesn't work for remove
    // finds values faster
    private int quadraticProbe(int fromIdx, Prioritizable key, int maxTries, BiFunction<Integer, Prioritizable, Boolean> matcher){
        int idx = -1;
        int temp;
        for(int attempt = 1; attempt <= maxTries && idx == -1; attempt++){
            temp = (fromIdx + attempt * attempt) % keys.length;
            
            if(matcher.apply(temp, key)){
                idx = temp;
            }
            
            if(hash(keys[temp]) != hash(key)){
                maxTries++; // that check doesn't count
            }
        }
        return idx;
    }
    
    /**
     * A hashing technique used to resolve problems where two keys have the same
     * hash, so linear- or quadratic-probing would just keep hitting the same
     * indeces for both of them.
     * 
     * @param fromIdx
     * @param key
     * @param maxTries
     * @param matcher
     * @return 
     */
    private int doubleHash(int fromIdx, Prioritizable key, int maxTries, BiFunction<Integer, Prioritizable, Boolean> matcher){
        int r = doubleHashSize;
        int secondHash = (r - key.getPriority() % r); 
        int idx = -1;
        int temp;
        for(int attempt = 1; attempt <= maxTries && idx == -1; attempt++){
            temp = (fromIdx + attempt * secondHash) % keys.length;
            if(matcher.apply(temp, key)){
                idx = temp;
            }
            
            if(hash(keys[temp]) != hash(key)){
                maxTries++; // check doesn't count
            }
        }
        
        return idx;
    }
    
    private boolean findEmpty(int i, Prioritizable dummy){
        return keys[i] == null;
    }
    
    private boolean findValue(int i, Prioritizable key){
        return Objects.equals(keys[i], key);
    }    
    
    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder();
        for(int i = 0; i < keys.length; i++){
            if(keys[i] == null){
                sb.append(String.format("%3d:\n", i));
            } else {
                sb.append(String.format("%3d: #%3d: %20s | %3d with hash\n", i, keys[i].getPriority(), values[i].toString(), valuesWithHash[i]));
            }
        }
        return sb.toString();
    }
    
    public static void main(String[] args){
        HashTable tab = new HashTable(10);
        for(int i = 0; i < 10; i++){
            tab.put(new PrioritizableInteger(i * i), String.format("Entry #%d", i * i));
            //System.out.println(tab);
        }
        
        System.out.println(tab);
    }
}
