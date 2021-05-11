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
    public final void findAllShortestPathsFrom(int start){
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
    }
    
    /**
     * Minimum Spanning Tree: a tree containing N vertices, and N - 1 edges.
     * A subgraph of some graph G such that it has the minimum total cost of
     * edges out of all possible completely connected subgraphs
     */
    public final void primsAlgorithm(){
        HashMap<Integer, Integer> vertexToPrevious = new HashMap<>();
        HashMap<Integer, Integer> vertexToBestDist = new HashMap<>();
        HashMap<Integer, Boolean> vertexToVisited = new HashMap<>();
        
        g.getAllVertices().forEach((vertex)->{
            vertexToPrevious.put(vertex.getId(), null);
            vertexToBestDist.put(vertex.getId(), INFINITY);
            vertexToVisited.put(vertex.getId(), Boolean.FALSE);
        });
        
        // start at any vertex
        int curr = g.getAllVertices().get(0).getId();
        vertexToBestDist.put(curr, 0);
        vertexToVisited.put(curr, Boolean.TRUE);
        
        while(curr != -1){
            for(Edge e : g.getEdgesAdjTo(curr)){
                if(!vertexToVisited.get(e.getTo())){
                    // only difference between Dijkstras: don't add cumulative distance
                    int totalDist = e.getWeight();
                    if(vertexToBestDist.get(e.getTo()) == INFINITY || totalDist < vertexToBestDist.get(e.getTo())){
                        vertexToBestDist.put(e.getTo(), totalDist);
                        vertexToPrevious.put(e.getTo(), curr);
                    }
                }
            }
            
            int newCurr = -1;
            int shortest = INFINITY;
            for(int v : vertexToVisited.keySet()){
                if(!vertexToVisited.get(v) && (shortest == INFINITY || shortest < vertexToBestDist.get(v))){
                    newCurr = v;
                    shortest = vertexToBestDist.get(v);
                }
            }
            curr = newCurr;
            if(curr != -1){
                vertexToVisited.put(curr, Boolean.TRUE);
            }
        }
        
        System.out.printf("%3c | %3c | %3c\n", 'V', 'D', 'P');
        System.out.println("================");
        vertexToVisited.keySet().forEach((vertex)->{
            System.out.printf("%3d | %3d | %3d\n", vertex, vertexToBestDist.get(vertex), vertexToPrevious.get(vertex));
        });
    }
    
    public static void main(String[] args){
        /*
        0 - 1 - 2
        |   |   |
        3 - 4 - 5
        |   |   |
        6 - 7 - 8
        */
        Graph g = new Graph();
        g.addVertex(new Vertex(0, 0, 0));
        g.addVertex(new Vertex(1, 1, 0));
        g.addVertex(new Vertex(2, 2, 0));
        g.addVertex(new Vertex(3, 0, 1));
        g.addVertex(new Vertex(4, 1, 1));
        g.addVertex(new Vertex(5, 2, 1));
        g.addVertex(new Vertex(6, 0, 2));
        g.addVertex(new Vertex(7, 1, 2));
        g.addVertex(new Vertex(8, 2, 2));
        g.addEdge(new Edge(0, 1, 1));
        g.addEdge(new Edge(1, 0, 1));
        g.addEdge(new Edge(1, 2, 1));
        g.addEdge(new Edge(2, 1, 1));
        g.addEdge(new Edge(0, 3, 1));
        g.addEdge(new Edge(3, 0, 1));
        g.addEdge(new Edge(3, 4, 1));
        g.addEdge(new Edge(4, 3, 1));
        g.addEdge(new Edge(1, 4, 1));
        g.addEdge(new Edge(4, 1, 1));
        g.addEdge(new Edge(4, 5, 1));
        g.addEdge(new Edge(5, 4, 1));
        g.addEdge(new Edge(2, 5, 1));
        g.addEdge(new Edge(5, 2, 1));
        g.addEdge(new Edge(3, 6, 1));
        g.addEdge(new Edge(6, 3, 1));
        g.addEdge(new Edge(6, 7, 1));
        g.addEdge(new Edge(7, 6, 1));
        g.addEdge(new Edge(4, 7, 1));
        g.addEdge(new Edge(7, 4, 1));
        g.addEdge(new Edge(7, 8, 1));
        g.addEdge(new Edge(8, 7, 1));
        g.addEdge(new Edge(5, 8, 1));
        g.addEdge(new Edge(8, 5, 1));
        
        DijkstrasAlgorithm alg = new DijkstrasAlgorithm(g);
        alg.findAllShortestPathsFrom(0);
        System.out.println();
        alg.primsAlgorithm();
    }
}
