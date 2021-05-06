package dataStructures.graphs;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

/**
 *
 * @author Matt
 */
public class DijkstrasAlgorithm {
    private final Graph g;
    
    private static final int INFINITY = -1;
    
    public DijkstrasAlgorithm(Graph g){
        this.g = g;
    }
    
    public final List<Vertex> findPath(int start, int end){
        List<Vertex> path = new LinkedList<>(); // todo path class
        
        return path;
    }
    
    /*
    Greedy algorithm: makes decisions based on what is IMMEDIATELY available
    Doesn't work with negative weight edges
    */
    public final void findMST(int start){
        HashMap<Integer, Integer> previousInPath = new HashMap<>(); // maps vertex to previous one in path
        HashMap<Vertex, Integer> bestDistThusFar = new HashMap<>(); // cumulative distance
        HashMap<Vertex, Boolean> visited = new HashMap<>(); // if visited, the shortest path to this vertex has been found
        
        g.getAllVertices().forEach((v)->{
            previousInPath.put(v.getId(), null);
            bestDistThusFar.put(v, INFINITY);
            visited.put(v, Boolean.FALSE);
        });
        
        // start at the start vertex
        Vertex curr = g.getVertex(start);
        visited.put(curr, true);
        previousInPath.put(curr.getId(), null);
        bestDistThusFar.put(curr, 0);
        
        while(curr != null){
            // find new best paths to curr's neighbors
            for(Edge edge : g.getEdgesAdjTo(curr.getId())){
                // unvisited
                if(!visited.get(g.getVertex(edge.getTo()))){
                    Vertex to = g.getVertex(edge.getTo());
                    int totalDist = edge.getWeight() + bestDistThusFar.get(curr);
                    // check for a new best path
                    if(bestDistThusFar.get(to) == INFINITY || bestDistThusFar.get(to) > totalDist){
                        bestDistThusFar.put(to, totalDist);
                        previousInPath.put(edge.getTo(), curr.getId());
                    }
                }
            }
            
            // find the shortest path to an unvisited node, then make that node curr
            Vertex newCurr = null;
            int shortest = INFINITY;
            for(Vertex v : visited.keySet()){
                if(!visited.get(v) && (shortest == INFINITY || shortest < bestDistThusFar.get(v))){
                    newCurr = v;
                    shortest = bestDistThusFar.get(v);
                }
            }
            curr = newCurr;
            if(curr != null){
                visited.put(curr, Boolean.TRUE);
            }
        }
        
        System.out.printf("%3c | %3c | %3c\n", 'V', 'D', 'P');
        System.out.println("================");
        visited.keySet().forEach((vertex)->{
            System.out.printf("%3d | %3d | %3d\n", vertex.getId(), bestDistThusFar.get(vertex), previousInPath.get(vertex.getId()));
        });
        
        return;
    }
    
    public static void main(String[] args){
        Graph g = new Graph();
        g.addVertex(new Vertex(0, 0, 0));
        g.addVertex(new Vertex(1, 1, 0));
        g.addVertex(new Vertex(2, 0, 1));
        g.addVertex(new Vertex(3, 1, 1));
        g.addEdge(new Edge(0, 1, 1));
        g.addEdge(new Edge(1, 0, 1));
        g.addEdge(new Edge(0, 2, 1));
        g.addEdge(new Edge(2, 0, 1));
        g.addEdge(new Edge(1, 3, 1));
        g.addEdge(new Edge(3, 1, 1));
        g.addEdge(new Edge(2, 3, 1));
        g.addEdge(new Edge(3, 2, 1));
        
        DijkstrasAlgorithm alg = new DijkstrasAlgorithm(g);
        alg.findMST(0);
    }
}
