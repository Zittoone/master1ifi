package fr.unice.masterifi.graph;

import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;

public class DirectedGraph {

    private final int V;                // Vertices
    private int E;                      // Edges
    private List<Integer>[] adj;        // adj[v} = adjacency list for vertex v
    private int[] indegree;             // indegree[v} = indegree of vertex v

    public DirectedGraph(int V) {
        this.V = V;
        this.E = 0;
        indegree = new int[V];
        adj = (LinkedList<Integer>[]) new LinkedList[V];
        for (int i = 0; i < V; i++) {
            adj[i] = new LinkedList<Integer>();
        }
    }

    public int V() {
        return V;
    }

    public int E() {
        return E;
    }

    private void validateVertex(int v) {
        if (v < 0 || v >= V)
            throw new IllegalArgumentException("vertex " + v + " is not between 0 and " + (V-1));
    }

    public void addEdge(int v, int w) {
        validateVertex(v);
        validateVertex(w);
        adj[v].add(w);
        indegree[w]++;
        E++;
        adj[v].sort(Comparator.comparingInt(Integer::intValue));
    }

    public Iterable<Integer> adj(int v) {
        validateVertex(v);
        return adj[v];
    }

    public int outdegree(int v) {
        validateVertex(v);
        return adj[v].size();
    }

    public int indegree(int v) {
        validateVertex(v);
        return indegree[v];
    }

    public DirectedGraph reverse() {
        DirectedGraph reverse = new DirectedGraph(V);
        for (int v = 0; v < V; v++) {
            for (int w : adj(v)) {
                reverse.addEdge(w, v);
            }
        }
        return reverse;
    }
}
