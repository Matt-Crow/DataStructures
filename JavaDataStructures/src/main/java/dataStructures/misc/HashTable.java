package dataStructures.misc;

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
 * @author Matt
 */
public class HashTable {
    // must be of constant size
    private final Prioritizable[] keys;
    private final Object[] values; 
    private final int[] valuesWithHash; // how many values in the table have a given hash
    /*
    can do LinkedList<Object>[]. See C notes. "Separate chaining". Find becomes 
    O(logn). Commonly used method. Takes more memory, but that's only a problem on
    smaller systems
    */
    
    public HashTable(int size){
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
            idx = quadraticProbe(hash, key, valuesWithHash[hash] + 1, this::findValue);
        }
        
        if(idx == -1){
            // still not found
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
            idx = quadraticProbe(hash, key, valuesWithHash[hash] + 1, this::findEmpty);
        }
        
        if(idx == -1){
            // still not found
        }
        
        return idx;
    }
    
    private boolean findEmpty(int i, Prioritizable dummy){
        return keys[i] == null;
    }
    
    private boolean findValue(int i, Prioritizable key){
        return Objects.equals(keys[i], key);
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
        }
        
        System.out.println(tab);
    }
}
