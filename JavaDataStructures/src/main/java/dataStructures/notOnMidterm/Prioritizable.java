package dataStructures.notOnMidterm;

/**
 *
 * @author Matt
 */
public interface Prioritizable {
    /**
     * Higher priority Prioritizables are removed from the PriorityQueue first
     * 
     * @return this object's priority 
     */
    public int getPriority();
}
