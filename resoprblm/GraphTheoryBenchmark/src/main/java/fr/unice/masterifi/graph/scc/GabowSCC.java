package fr.unice.masterifi.graph.scc;

import fr.unice.masterifi.graph.Utils;
import fr.unice.masterifi.graph.DirectedGraph;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Stack;
import java.util.stream.Stream;

public class GabowSCC implements SCC {

    private Stack<Integer> S;
    private Stack<Integer> B;
    private int[] I;
    private int count;
    private int num;

    public GabowSCC(DirectedGraph g) {

        I = new int[g.V()];
        S = new Stack<>();
        B = new Stack<>();
        num = 0;

        strong(g);

        count = count - g.V();
    }

    private void strong(DirectedGraph g) {
        // 1. Empty stacks S and B
        S.clear();
        B.clear();

        // 2.
        for(int v = 0; v < g.V(); v++) {
            I[v] = -1;
        }

        // 3. c = n
        count = g.V();
        num = 1;

        // 4.
        for(int v = 0; v < g.V(); v++) {
            if(I[v] == -1) dfs(g, v);
        }

    }

    private void dfs(DirectedGraph g, int v) {

        S.push(v);
        B.push(v);
        I[v] = num;
        num++;

        for(int w : g.adj(v)) {
            if(I[w] == -1) {
                dfs(g, w);
            } else {
                /* if non affected to CFC */
                if(I[w] <= g.V()) {
                    while (I[B.peek()] > I[w]) {
                        B.pop();
                    }
                }
            }
        }

        if(v == B.peek()) {
            count++;
            while (!S.empty() && v != S.peek()) {
                I[S.pop()] = count;
            }
            I[S.pop()] = count;
            B.pop();
        }
    }

    @Override
    public boolean isStronglyConnected(int v, int w) {
        return I[v] == I[w];
    }

    @Override
    public int getCount() {
        return count;
    }

    @Override
    public int id(int v) {
        return I[v];
    }
}
