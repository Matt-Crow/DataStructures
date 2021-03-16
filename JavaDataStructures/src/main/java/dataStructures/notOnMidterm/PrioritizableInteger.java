package dataStructures.notOnMidterm;

/**
 *
 * @author Matt
 */
public class PrioritizableInteger implements Prioritizable {
    private final int value;
    
    public PrioritizableInteger(int value){
        this.value = value;
    }
    
    @Override
    public int getPriority() {
        return value;
    }
    
    @Override
    public String toString(){
        return String.format("PriorityInt(%d)", value);
    }
}
