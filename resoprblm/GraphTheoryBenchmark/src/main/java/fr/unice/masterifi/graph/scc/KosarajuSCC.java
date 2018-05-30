package fr.unice.masterifi.graph.scc;

import fr.unice.masterifi.graph.DirectedGraph;
import fr.unice.masterifi.graph.Graph;
import fr.unice.masterifi.graph.Utils;

import java.util.*;

public class KosarajuSCC implements SCC {

    private Stack<Integer> S;
    private boolean[] visited;
    private int[] id;
    private int count;

    public long timeReversing;

    public KosarajuSCC(Graph g) {

       // S = new Stack<>();
        id = new int[g.V()];
        /*for (int i = 0; i < g.V(); i++) {
            id[i] = 0;
        }*/
        visited = new boolean[g.V()];
        count = 0;

        long t1 = System.currentTimeMillis();
        Graph gr = g.reverse();
        timeReversing = System.currentTimeMillis() - t1;
        S = dfsVisitOrder(gr);

        int iteration = 1;

        /* Continuously process the the nodes from the queue by running a DFS
         * from each unmarked node we encounter.
         */
        while (!S.isEmpty()) {
            /* Grab the last node.  If we've already labeled it, skip it and
             * move on.
             */
            Integer startPoint = S.pop();
            if (id[startPoint] != 0)
                continue;

            /* Run a DFS from this node, recording everything we visit as being
             * at the current level.
             */
            markReachableNodes(startPoint, g, iteration);

            /* Bump up the number of the next SCC to label. */
            ++iteration;
        }

        /*for (int i = 0; i < g.V(); i++) {
            if(!visited[i]) {
                dfs(g, i);
            }
        }

        Graph transposed = g.reverse();

        visited = new boolean[g.V()];

        while(!S.empty()) {
            count++;
            int v = S.pop();
            id[v] = count;
            dfs2(transposed, v);
        }*/

        count = iteration - 1;
    }

    private Stack<Integer> dfsVisitOrder(Graph g) {
        Stack<Integer> result = new Stack<>();

        /* Fire off a DFS from each node. */
        for (int i = 0; i < g.V(); i++) {
            recExplore(i, g, result);
        }
        return result;
    }

    private void recExplore(Integer node, Graph g,
                                       Stack<Integer> result) {
        /* If we've already been at this node, don't explore it again. */
        if (visited[node]) return;

        /* Otherwise, mark that we've been here. */
        visited[node] = true;

        /* Recursively explore all the node's children. */
        for (Integer endpoint: g.adj(node))
            recExplore(endpoint, g, result);

        /* We're done exploring this node, so add it to the list of visited
         * nodes.
         */
        result.push(node);
    }

    private void markReachableNodes(Integer node, Graph g, int label) {
        /* If we've visited this node before, stop the search. */
        if (id[node] != 0) return;

        /* Otherwise label the node with the current label, since it's
         * trivially reachable from itself.
         */
        id[node] = label;

        /* Explore all nodes reachable from here. */
        for (Integer endpoint: g.adj(node))
            markReachableNodes(endpoint, g, label);
    }

    private void dfs2(Graph transposed, int v) {
        visited[v] = true;
        id[v] = count;
        for(Integer a : transposed.adj(v)) {
            if(!visited[a]) {
                dfs2(transposed, a);
            }
        }
        // System.out.println(v + " == " + S.peek() + " ?");
        S.remove(((Integer) v));
    }

    private void dfs(Graph g, int u) {
        visited[u] = true;
        for(Integer a : g.adj(u)) {
            if(!visited[a]) {
                dfs(g, a);
            }
        }
        S.add(u);
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
