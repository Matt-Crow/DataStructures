package dataStructures.graphs;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.stream.Collectors;

/**
 * 
 * Storing edges:
 *   1. can use a two-dimensional array as an adjacency matrix, where a number n
 *      in cell [a][b] designates an edge of weight n from vertex a to vertex b.
 *      Not very space efficient
 * 
 *   2. Adjacency list: array of objects mapping vertices to a linked list of 
 *      vertices adjacent to them (a is mapped to a => b, not b is mapped to a 
 *      => b). Less time-efficient than adjacency matrix
 * 
 * @author Matt Crow
 */
public class Graph {
    private final HashMap<Integer, Vertex> vertices;
    private final HashMap<Integer, LinkedList<Edge>> edges;
    
    public Graph(){
        this.vertices = new HashMap<>();
        this.edges = new HashMap<>();
    }
    
    public final void addVertex(Vertex v){
        vertices.put(v.getId(), v);
    }
    
    public final void addEdge(Edge e){
        if(!edges.containsKey(e.getFrom())){
            edges.put(e.getFrom(), new LinkedList<>());
        }
        edges.get(e.getFrom()).add(e);
    }
    
    public final Vertex getVertex(int id){
        return vertices.get(id);
    }
    
    public final List<Edge> getEdges(int id){
        // shallow copy
        return edges.get(id).stream().collect(Collectors.toList());
    }
    
    public final int getVertexCount(){
        return vertices.size();
    }
}
