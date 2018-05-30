package fr.unice.masterifi.graph.scc;

import fr.unice.masterifi.graph.Graph;

import java.util.*;

public class KosarajuSCC implements SCC {

    private Stack<Integer> S;
    private boolean[] visited;
    private int[] id;
    private int count;

    public long timeReversing;

    public KosarajuSCC(Graph g) {

        id = new int[g.V()];
        visited = new boolean[g.V()];
        count = 0;

        long t1 = System.currentTimeMillis();
        Graph gr = g.reverse();
        timeReversing = System.currentTimeMillis() - t1;
        S = dfsVisitOrder(gr);

        int iteration = 1;

        while (!S.isEmpty()) {
            Integer startPoint = S.pop();
            if (id[startPoint] != 0)
                continue;

            dfs(startPoint, g, iteration);
            ++iteration;
        }
        count = iteration - 1;
    }

    private Stack<Integer> dfsVisitOrder(Graph g) {
        Stack<Integer> result = new Stack<>();

        for (int i = 0; i < g.V(); i++) {
            dfs2(i, g, result);
        }
        return result;
    }

    private void dfs2(Integer node, Graph g, Stack<Integer> stack) {
        if (visited[node]) return;
        visited[node] = true;

        for (Integer endpoint: g.adj(node))
            dfs2(endpoint, g, stack);
        stack.push(node);
    }

    private void dfs(Integer node, Graph g, int id) {
        if (this.id[node] != 0) return;
        this.id[node] = id;
        for (Integer endpoint: g.adj(node))
            dfs(endpoint, g, id);
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
        /*int V = marked.length;
        if (v < 0 || v >= V)
            throw new IllegalArgumentException("vertex " + v + " is not between 0 and " + (V-1));*/
    }
}
