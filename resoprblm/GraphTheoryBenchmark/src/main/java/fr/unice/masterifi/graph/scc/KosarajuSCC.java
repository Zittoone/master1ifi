package fr.unice.masterifi.graph.scc;

import fr.unice.masterifi.graph.DirectedGraph;
import fr.unice.masterifi.graph.Utils;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Stack;

public class KosarajuSCC implements SCC {

    private Stack<Integer> S;
    private boolean[] visited;
    private int[] id;
    private int count;

    public KosarajuSCC(DirectedGraph g) {

        S = new Stack<>();
        id = new int[g.V()];
        for (int i = 0; i < g.V(); i++) {
            id[i] = 0;
        }
        visited = new boolean[g.V()];
        count = 1;

        List<Integer> elems = new ArrayList<>();
        for (int i = 0; i < g.V(); i++) {
            elems.add(i);
        }

        int current;
        while(!S.containsAll(elems)) {
            elems.removeAll(S);
            current = elems.get(0);
            dfs(g, current);
        }

        System.out.println("On prend le transposé");
        DirectedGraph transposed = g.reverse();

        for (int i = 0; i < g.V(); i++) {
            visited[i] = false;
        }
        while(!S.empty()) {
            int v = S.pop();
            System.out.println("On dépile S: " + Utils.toAlphabet(v) + ". On atteint : " + Utils.toStringListCustom(Utils.toList(transposed.adj(v)), Utils::toAlphabet));
            id[v] = count;
            dfs2(transposed, v);
            count++;
        }
    }

    private void dfs2(DirectedGraph transposed, int v) {
        visited[v] = true;
        for(Integer a : transposed.adj(v)) {
            if(!visited[a]) {
                dfs2(transposed, a);
            }
        }
        System.out.println("adding " + Utils.toAlphabet(v) + " to CFC " + count);
        id[v] = count;
        S.remove(((Integer) v));
    }

    private void dfs(DirectedGraph g, int u) {
        visited[u] = true;
        for(Integer a : g.adj(u)) {
            if(!visited[a]) {
                dfs(g, a);
            }
        }
        S.add(u);
        System.out.println("On ferme " + Utils.toAlphabet(u) + " : " + Utils.toStringListCustom(S, Utils::toAlphabet));
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
