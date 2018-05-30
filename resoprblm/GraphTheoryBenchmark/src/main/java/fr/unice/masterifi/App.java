package fr.unice.masterifi;

import fr.unice.masterifi.graph.AdjMatrixDirectedGraph;
import fr.unice.masterifi.graph.Graph;
import fr.unice.masterifi.graph.scc.GabowSCC;
import fr.unice.masterifi.graph.scc.KosarajuSCC;
import fr.unice.masterifi.graph.scc.TarjanSCC;
import org.knowm.xchart.*;
import org.knowm.xchart.style.Styler;

import java.io.IOException;
import java.util.Arrays;

public class App {

    public static void main(String[] args) throws IOException {

        int V = 10000;
        // adj matrix so Kosaraju is O(V²)
        Graph graph = new AdjMatrixDirectedGraph(V);

        KosarajuSCC kosaraju;
        TarjanSCC tarjan;
        GabowSCC gabow;
        int nbSimulations = 100;
        int inc = V/nbSimulations;

        double ms[][] = new double[7][nbSimulations+1];
        long t1, t2;

        for (int i = 0; i < nbSimulations + 1; i++) {

            double density = ((double) graph.E() / (double)(V*V));
            System.out.println("beginning iteration " + i + " => " + graph.E() + " edges and " + density + " density");
            ms[3][i] = density;

            t1 = System.currentTimeMillis();
            tarjan = new TarjanSCC(graph);
            t2 = System.currentTimeMillis();
            ms[0][i] = t2 - t1;
            ms[4][i] = tarjan.getCount();
            ms[6][i] = graph.E() / V;

            System.out.println("Tarjan done in " + ms[0][i] + "ms => " + tarjan.getCount());

            t1 = System.currentTimeMillis();
            // kosarajuSharirSCC = new KosarajuSharirSCC(graph);
            kosaraju = new KosarajuSCC(graph);
            t2 = System.currentTimeMillis();
            ms[1][i] = t2 - t1;
            ms[5][i] = ms[1][i] - kosaraju.timeReversing;

            System.out.println("Kosaraju done in " + ms[1][i] + "ms => " + kosaraju.getCount());

            t1 = System.currentTimeMillis();
            gabow = new GabowSCC(graph);
            t2 = System.currentTimeMillis();
            ms[2][i] = t2 - t1;

            System.out.println("Gabow done in " + ms[2][i] + "ms => " + gabow.getCount());

/*
            asserts to be sure it's working, now that i tested many times i can remove them
            assert tarjan.getCount() == kosaraju.getCount();
            assert tarjan.getCount() == gabow.getCount();

            for (int j = 0; j < graph.V(); j++) {
                for (int k = 0; k < graph.V(); k++) {
                    assert tarjan.isStronglyConnected(j, k) == kosaraju.isStronglyConnected(j, k);
                    assert tarjan.isStronglyConnected(j, k) == gabow.isStronglyConnected(j, k);
                }
            }
*/
            System.out.println("Found -----> " + tarjan.getCount() + " SCC");

            if(i != nbSimulations) {
                for (int j = i*inc; j < (i+1)*inc; j++) {
                    for (int k = 0; k < V; k++) {
                        // System.out.println("adding : " + k +", " + j);
                        graph.addEdge(k, j);
                    }
                }
            }
        }

        /*for (int i = 0; i < graph.V(); i++) {
            System.out.println(graph.adj(i));
        }*/
        System.out.println(Arrays.deepToString(ms));

        // XYChart chart = QuickChart.getChart("SCC Solvers Benchmark", "Graph density (Edges/V²)", "Time to solve (ms));
        XYChart chart = new XYChartBuilder().width(1920).height(1080).title("SCC Solvers Benchmark with " + V + " vertices").xAxisTitle("Graph density (Edges/V²)").yAxisTitle("Time to solve (ms)").theme(Styler.ChartTheme.XChart).build();
        chart.addSeries("Tarjan", ms[3], ms[0]);
        chart.addSeries("Kosaraju", ms[3], ms[5]);
        chart.addSeries("Gabow", ms[3], ms[2]);

        new SwingWrapper<>(chart).displayChart();

// or save it in high-res
        BitmapEncoder.saveBitmap(chart, "./SCCSolvers_" + V + "_" + System.currentTimeMillis(), BitmapEncoder.BitmapFormat.PNG);
    }
}
