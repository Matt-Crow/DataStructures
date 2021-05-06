package dataStructures.graphs;

import dataStructures.priorityQueue.Prioritizable;

/**
 *
 * @author Matt
 */
public class Edge implements Prioritizable {
    private final int v1;
    private final int v2;
    private final int weight; // cannot be negative
    
    public Edge(int v1, int v2, int weight){
        this.v1 = v1;
        this.v2 = v2;
        this.weight = weight;
    }
    
    public final int getFrom(){
        return v1;
    }
    
    public final int getTo(){
        return v2;
    }
    
    public final int getWeight(){
        return weight;
    }
    
    @Override
    public String toString(){
        return String.format("%d => %d (%d)", v1, v2, weight);
    }

    @Override
    public int getPriority() {
        return weight;
    }
}
