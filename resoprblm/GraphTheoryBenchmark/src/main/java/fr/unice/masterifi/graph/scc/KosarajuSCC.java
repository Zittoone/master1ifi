package fr.unice.masterifi.graph.scc;

import fr.unice.masterifi.graph.DirectedGraph;

public class KosarajuSCC implements SCC {

    private boolean[] marked;     // marked[v] = has vertex v been visited?
    private int[] id;             // id[v] = id of strong component containing v
    private int count;            // number of strongly-connected components

    public KosarajuSCC(DirectedGraph G) {

        // compute reverse postorder of reverse graph
       // DepthFirstOrder dfs = new DepthFirstOrder(G.reverse());

        // run DFS on G, using reverse postorder to guide calculation
        /*marked = new boolean[G.V()];
        id = new int[G.V()];
        for (int v : dfs.reversePost()) {
            if (!marked[v]) {
                dfs(G, v);
                count++;
            }
        }*/

        // check that id[] gives strong components
        //assert check(G);
    }

    @Override
    public boolean isStronglyConnected(int v, int w) {
        validateVertex(v);
        validateVertex(w);
        return id[v] == id[w];
    }

    @Override
    public int getCount() {
        return count;
    }

    @Override
    public int id(int v) {
        validateVertex(v);
        return id[v];
    }

    private void validateVertex(int v) {
        int V = marked.length;
        if (v < 0 || v >= V)
            throw new IllegalArgumentException("vertex " + v + " is not between 0 and " + (V-1));
    }
}
