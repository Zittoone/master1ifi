package fr.unice.masterifi.graph.scc;

import fr.unice.masterifi.graph.DirectedGraph;

import java.util.Stack;

public class GabowSCC implements SCC {

    private Stack<Integer> S;
    private Stack<Integer> B;
    private int[] I;
    private int count;

    public GabowSCC(DirectedGraph g) {

        I = new int[g.V()];
        S = new Stack<>();
        B = new Stack<>();
    }

    private void strong(DirectedGraph g) {
        // 1. Empty stacks S and B
        S.clear();
        B.clear();

        // 2.
        for(int v = 0; v < g.V(); v++) {
            I[v] = 0;
        }

        // 3. c = n
        count = 1;

        // 4.
        for(int v = 0; v < g.V(); v++) {
            if(I[v] == 0) dfs(g, v);
        }

    }

    private void dfs(DirectedGraph g, int v) {
        S.push(v);
        I[v] = S.peek();
        B.push(I[v]);

        for(int w : g.adj(v)) {
            if(I[w] == 0) {
                dfs(g, w);
            } else {
                /* contract if necessary */
                while(I[w] < B.elementAt(B.peek())) {
                    B.pop();
                }
            }
        }

        if(I[v] == B.elementAt(B.peek())) {
            B.pop();
            count++;
            while (I[v] <= S.peek()) {
                I[S.pop()] = count;
            }
        }
    }

    @Override
    public boolean isStronglyConnected(int v, int w) {
        return false;
    }

    @Override
    public int getCount() {
        return count;
    }

    @Override
    public int id(int v) {
        return 0;
    }
}
