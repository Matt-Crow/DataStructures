package dataStructures.graphs;

/**
 *
 * @author Matt
 */
public class Vertex {
    private final int id;
    private final int x;
    private final int y;
    
    public Vertex(int id, int x, int y){
        this.id = id;
        this.x = x;
        this.y = y;
    }
    
    public final int getId(){
        return id;
    }
    
    public final int getX(){
        return x;
    }
    
    public final int getY(){
        return y;
    }
    
    @Override
    public int hashCode(){
        return Integer.hashCode(id);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Vertex other = (Vertex) obj;
        if (this.id != other.id) {
            return false;
        }
        return true;
    }
    
    @Override
    public String toString(){
        return String.format("Vertex#%d (%d, %d)", id, x, y);
    }
}
