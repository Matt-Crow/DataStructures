package dataStructures.misc;

import dataStructures.priorityQueue.Prioritizable;
import dataStructures.priorityQueue.PrioritizableInteger;

/**
 *
 * @author Matt
 */
public class HashTable {
    // must be of constant size
    private final Prioritizable[] keys;
    private final Object[] values; 
    /*
    can do LinkedList<Object>[]. See C notes. "Seperate chaining". Find becomes 
    O(n). Commonly used method. Takes more memory, but that's only a problem on
    smaller systems
    */
    
    public HashTable(int size){
        keys = new Prioritizable[size];
        values = new Object[size];
    }
    
    public final void put(Prioritizable key, Object value){
        int idx = getIdx(key);
        keys[idx] = key;
        values[idx] = value;
    }
    
    public final Object get(Prioritizable key){
        int idx = getIdx(key);
        return values[idx];
    }
    
    public final void delete(Prioritizable key){
        int idx = getIdx(key);
        keys[idx] = null;
        values[idx] = null;
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
        return key.getPriority() % keys.length;
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
                sb.append(String.format("%3d: #%3d: %s\n", i, keys[i].getPriority(), values[i].toString()));
            }
        }
        return sb.toString();
    }
    
    public static void main(String[] args){
        HashTable tab = new HashTable(10);
        for(int i = 0; i < 10; i++){
            tab.put(new PrioritizableInteger(i), String.format("Entry #%d", i));
        }
        System.out.println(tab);
    }
}
