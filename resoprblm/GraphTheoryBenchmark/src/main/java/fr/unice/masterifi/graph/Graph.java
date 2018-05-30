package fr.unice.masterifi.graph;

public interface Graph {
    int V();

    int E();

    void addEdge(int v, int w);

    Iterable<Integer> adj(int v);

    Graph reverse();
}
