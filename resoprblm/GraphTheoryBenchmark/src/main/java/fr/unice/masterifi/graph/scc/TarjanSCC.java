package fr.unice.masterifi.graph.scc;

import fr.unice.masterifi.graph.DirectedGraph;

import java.util.List;
import java.util.Stack;

/**
 * Created by Alexis Couvreur on 25/05/2018.
 */
public class TarjanSCC implements SCC {

    private int num;
    private Stack<Integer> P;
    private List<List<Integer>> partition;

    public TarjanSCC(DirectedGraph graph) {
        num = 0;
        P = new Stack<>();

        for(int v = 0; v < graph.V(); v++) {

        }
    }

    private void parcours(DirectedGraph graph, int v) {

    }

    @Override
    public boolean isStronglyConnected(int v, int w) {
        return false;
    }

    @Override
    public int getCount() {
        return 0;
    }

    @Override
    public int id(int v) {
        return 0;
    }
}
