package fr.unice.masterifi.graph.scc;

public interface SCC {

    boolean isStronglyConnected(int v, int w);
    int getCount();
    int id(int v);

}
