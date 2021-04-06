/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dataStructures.priorityQueue;

/**
 * A Priority Queue stores many objects, each of which have a priority. Should
 * support retrieving the object with the highest (or lowest) priority.
 * 
 * Applications:
 * - CPU scheduling
 * - internet traffic scheduling
 * 
 * Can use AVL or Red-Black trees as Priority Queue
 * 
 * @author Matt Crow
 */
public interface PriorityQueue {
    public void add(Prioritizable newObj);
    public Prioritizable dequeueHighestPriority();
}
