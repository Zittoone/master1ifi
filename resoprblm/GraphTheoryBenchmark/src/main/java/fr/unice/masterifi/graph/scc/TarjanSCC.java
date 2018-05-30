package fr.unice.masterifi.graph.scc;

import fr.unice.masterifi.graph.DirectedGraph;
import fr.unice.masterifi.graph.Graph;
import fr.unice.masterifi.graph.Utils;

import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

/**
 * Created by Alexis Couvreur on 25/05/2018.
 */
public class TarjanSCC implements SCC {

    private int num;
    private int[] nums;
    private int[] numAccessible;
    private boolean[] dans_P;
    private Stack<Integer> P;
    private List<List<Integer>> partition;

    public TarjanSCC(Graph graph) {
        num = 0;
        P = new Stack<>();
        nums = new int[graph.V()];
        numAccessible = new int[graph.V()];
        dans_P = new boolean[graph.V()];
        partition = new ArrayList<>();

        for (int i = 0; i < graph.V(); i++) {
            nums[i] = -1;
        }
        for(int v = 0; v < graph.V(); v++) {
            if(nums[v] == -1) {
                parcours(graph, v);
            }
        }
    }

    private void parcours(Graph graph, int v) {
        nums[v] = num;
        numAccessible[v] = num;
        num++;
        P.push(v);
        dans_P[v] = true;

        for(Integer w : graph.adj(v)) {
            if(nums[w] == -1) {
                parcours(graph, w);
                numAccessible[v] = Math.min(numAccessible[v], numAccessible[w]);
            } else if (dans_P[w]) {
                numAccessible[v] = Math.min(numAccessible[v], nums[w]);
            }
        }

        if(numAccessible[v] == nums[v]) {
            int w;
            List<Integer> C = new ArrayList<>();
            do {
                w = P.pop();
                dans_P[w] = false;
                C.add(w);
            } while(w != v);

            partition.add(C);
        }
    }

    @Override
    public boolean isStronglyConnected(int v, int w) {
        for (List<Integer> l : partition)
            if(l.contains(v) && l.contains(w))
                return true;
        return false;
    }

    @Override
    public int getCount() {
        return partition.size();
    }

    @Override
    public int id(int v) {
        for (List<Integer> l : partition)
            if(l.contains(v))
                return partition.indexOf(l);
        return 0;
    }
}
