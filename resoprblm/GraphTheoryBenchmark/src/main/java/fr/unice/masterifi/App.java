package fr.unice.masterifi;

import fr.unice.masterifi.graph.AdjMatrixDirectedGraph;
import fr.unice.masterifi.graph.DirectedGraph;
import fr.unice.masterifi.graph.Graph;
import fr.unice.masterifi.graph.scc.GabowSCC;
import fr.unice.masterifi.graph.scc.KosarajuSCC;
import fr.unice.masterifi.graph.scc.KosarajuSharirSCC;
import fr.unice.masterifi.graph.scc.TarjanSCC;

import java.util.Arrays;

public class App {

    public static void main(String[] args) {

        int V = 5000;
        Graph graph = new DirectedGraph(V);

        KosarajuSharirSCC kosarajuSharirSCC;
        KosarajuSCC kosaraju;
        TarjanSCC tarjan;
        GabowSCC gabow;
        int nbSimulations = 10;
        int inc = V/nbSimulations;

        long ms[][] = new long[3][nbSimulations];
        long t1, t2;

        for (int i = 0; i < nbSimulations; i++) {
            for (int j = 0; j < inc; j++) {
                for (int k = 0; k < V; k++) {
                    graph.addEdge(j + i*j, k);
                }
            }

            double density = ((double) graph.E() / (double)(V*V)) ;
            System.out.println("beginning iteration " + i + " => " + graph.E() + " edges and " + density + " density");

            t1 = System.currentTimeMillis();
            tarjan = new TarjanSCC(graph);
            t2 = System.currentTimeMillis();
            ms[0][i] = t2 - t1;

            System.out.println("Tarjan done in " + ms[0][i] + "ms");

            t1 = System.currentTimeMillis();
            kosarajuSharirSCC = new KosarajuSharirSCC(graph);
            t2 = System.currentTimeMillis();
            ms[1][i] = t2 - t1;

            System.out.println("Kosaraju done in " + ms[1][i] + "ms");

            t1 = System.currentTimeMillis();
            gabow = new GabowSCC(graph);
            t2 = System.currentTimeMillis();
            ms[2][i] = t2 - t1;

            System.out.println("Gabow done in " + ms[2][i] + "ms");

            assert tarjan.getCount() == kosarajuSharirSCC.count();
            assert tarjan.getCount() == gabow.getCount();

            for (int j = 0; j < graph.V(); j++) {
                for (int k = 0; k < graph.V(); k++) {
                    assert tarjan.isStronglyConnected(j, k) == kosarajuSharirSCC.stronglyConnected(j, k);
                    assert tarjan.isStronglyConnected(j, k) == gabow.isStronglyConnected(j, k);
                }
            }

            System.out.println("Found -----> " + tarjan.getCount() + " SCC");
        }

        System.out.println(Arrays.deepToString(ms));
    }
}
