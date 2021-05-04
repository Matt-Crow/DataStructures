package dataStructures.graphs;

import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;

/**
 *
 * @author Matt
 */
public class DijkstrasAlgorithm {
    private final Graph g;
    
    public DijkstrasAlgorithm(Graph g){
        this.g = g;
    }
    
    public final List<Vertex> findPath(int start, int end){
        List<Vertex> path = new LinkedList<>(); // todo path class
        
        return path;
    }
    
    public final void findMST(int start){
        Set<Vertex> visited = new HashSet<>();
        HashMap<Vertex, Vertex> previousInPath = new HashMap<>(); // maps vertex to previous one in path
        HashMap<Vertex, Integer> bestDistThusFar = new HashMap<>();
        
        // start at the start vertex
        Vertex curr = g.getVertex(start);
        visited.add(curr);
        previousInPath.put(curr, null);
        bestDistThusFar.put(curr, 0);
    }
}
