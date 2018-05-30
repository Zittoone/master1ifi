package fr.unice.masterifi.graph;

import java.util.Iterator;
import java.util.NoSuchElementException;

public class AdjMatrixDirectedGraph implements Graph {
    private int V;
    private int E;
    private boolean[][] adj;

    public AdjMatrixDirectedGraph(int V) {
        if (V < 0) throw new RuntimeException("Number of vertices must be nonnegative");
        this.V = V;
        this.E = 0;
        this.adj = new boolean[V][V];
    }

    public int V() { return V; }
    public int E() { return E; }

    public void addEdge(int v, int w) {
        if (!adj[v][w]) E++;
        adj[v][w] = true;
    }

    public Iterable<Integer> adj(int v) {
        return new AdjIterator(v);
    }

    @Override
    public AdjMatrixDirectedGraph reverse() {
        AdjMatrixDirectedGraph reverse = new AdjMatrixDirectedGraph(V);
        for (int v = 0; v < V; v++) {
            for (int w : adj(v)) {
                reverse.addEdge(w, v);
            }
        }
        return reverse;
    }

    private class AdjIterator implements Iterator<Integer>, Iterable<Integer> {
        private int v;
        private int w = 0;

        AdjIterator(int v) {
            this.v = v;
        }

        public Iterator<Integer> iterator() {
            return this;
        }

        public boolean hasNext() {
            while (w < V) {
                if (adj[v][w]) return true;
                w++;
            }
            return false;
        }

        public Integer next() {
            if (hasNext()) return w++;
            else           throw new NoSuchElementException();
        }

        public void remove() {
            throw new UnsupportedOperationException();
        }
    }
}
