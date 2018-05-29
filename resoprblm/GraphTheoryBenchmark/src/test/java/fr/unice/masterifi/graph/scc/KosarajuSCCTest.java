package fr.unice.masterifi.graph.scc;

import fr.unice.masterifi.graph.DirectedGraph;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class KosarajuSCCTest {

    KosarajuSCC scc;

    @Before
    public void setUp() throws Exception {

        DirectedGraph g = new DirectedGraph(8);
        g.addEdge(0, 1); // a -> b

        g.addEdge(1, 2); // b -> c
        g.addEdge(1, 4); // b -> e
        g.addEdge(1, 5); // b -> f

        g.addEdge(2, 3); // c -> d
        g.addEdge(2, 6); // c -> g

        g.addEdge(3, 2); // d -> c
        g.addEdge(3, 7); // d -> h

        g.addEdge(4, 0); // e -> a
        g.addEdge(4, 5); // e -> f

        g.addEdge(5, 6); // f -> g

        g.addEdge(6, 5); // g -> f

        g.addEdge(7, 6); // h -> g
        g.addEdge(7, 3); // h -> d

        scc = new KosarajuSCC(g);
    }

    @Test
    public void isStronglyConnectedA() throws Exception {

        int s = 0;
        assertEquals(true, scc.isStronglyConnected(s, 0)); // a sc to a
        assertEquals(true, scc.isStronglyConnected(s, 1)); // a sc to b
        assertEquals(true, scc.isStronglyConnected(s, 4)); // a sc to e

        assertEquals(false, scc.isStronglyConnected(s, 2)); // a sc to c
        assertEquals(false, scc.isStronglyConnected(s, 3)); // a sc to d
        assertEquals(false, scc.isStronglyConnected(s, 5)); // a sc to f
        assertEquals(false, scc.isStronglyConnected(s, 6)); // a sc to g
        assertEquals(false, scc.isStronglyConnected(s, 7)); // a sc to h

    }

    @Test
    public void isStronglyConnectedB() throws Exception {

        int s = 1;
        assertEquals(true, scc.isStronglyConnected(s, 0)); // b sc to a
        assertEquals(true, scc.isStronglyConnected(s, 1)); // b sc to b
        assertEquals(true, scc.isStronglyConnected(s, 4)); // b sc to e

        assertEquals(false, scc.isStronglyConnected(s, 2)); // b sc to c
        assertEquals(false, scc.isStronglyConnected(s, 3)); // b sc to d
        assertEquals(false, scc.isStronglyConnected(s, 5)); // b sc to f
        assertEquals(false, scc.isStronglyConnected(s, 6)); // b sc to g
        assertEquals(false, scc.isStronglyConnected(s, 7)); // b sc to h

    }

    @Test
    public void isStronglyConnectedC() throws Exception {
        int s = 2;
        assertEquals(true, scc.isStronglyConnected(s, 2)); // c sc to c
        assertEquals(true, scc.isStronglyConnected(s, 3)); // c sc to d
        assertEquals(true, scc.isStronglyConnected(s, 7)); // c sc to h

        assertEquals(false, scc.isStronglyConnected(s, 0)); // c sc to a
        assertEquals(false, scc.isStronglyConnected(s, 1)); // c sc to b
        assertEquals(false, scc.isStronglyConnected(s, 4)); // c sc to e
        assertEquals(false, scc.isStronglyConnected(s, 5)); // c sc to f
        assertEquals(false, scc.isStronglyConnected(s, 6)); // c sc to g
    }

    @Test
    public void isStronglyConnectedD() throws Exception {
        int s = 3;
        assertEquals(true, scc.isStronglyConnected(s, 2)); // d sc to c
        assertEquals(true, scc.isStronglyConnected(s, 3)); // d sc to d
        assertEquals(true, scc.isStronglyConnected(s, 7)); // d sc to h

        assertEquals(false, scc.isStronglyConnected(s, 0)); // d sc to a
        assertEquals(false, scc.isStronglyConnected(s, 1)); // d sc to b
        assertEquals(false, scc.isStronglyConnected(s, 4)); // d sc to e
        assertEquals(false, scc.isStronglyConnected(s, 5)); // d sc to f
        assertEquals(false, scc.isStronglyConnected(s, 6)); // d sc to g
    }

    @Test
    public void isStronglyConnectedE() throws Exception {
        int s = 4;
        assertEquals(true, scc.isStronglyConnected(s, 0)); // e sc to a
        assertEquals(true, scc.isStronglyConnected(s, 1)); // e sc to b
        assertEquals(true, scc.isStronglyConnected(s, 4)); // e sc to e

        assertEquals(false, scc.isStronglyConnected(s, 2)); // e sc to c
        assertEquals(false, scc.isStronglyConnected(s, 3)); // e sc to d
        assertEquals(false, scc.isStronglyConnected(s, 5)); // e sc to f
        assertEquals(false, scc.isStronglyConnected(s, 6)); // e sc to g
        assertEquals(false, scc.isStronglyConnected(s, 7)); // e sc to h
    }

    @Test
    public void isStronglyConnectedF() throws Exception {
        int s = 5;
        assertEquals(true, scc.isStronglyConnected(s, 5)); // f sc to f
        assertEquals(true, scc.isStronglyConnected(s, 6)); // f sc to g

        assertEquals(false, scc.isStronglyConnected(s, 0)); // f sc to a
        assertEquals(false, scc.isStronglyConnected(s, 1)); // f sc to b
        assertEquals(false, scc.isStronglyConnected(s, 4)); // f sc to e
        assertEquals(false, scc.isStronglyConnected(s, 2)); // f sc to c
        assertEquals(false, scc.isStronglyConnected(s, 3)); // f sc to d
        assertEquals(false, scc.isStronglyConnected(s, 7)); // f sc to h
    }

    @Test
    public void isStronglyConnectedG() throws Exception {
        int s = 6;
        assertEquals(true, scc.isStronglyConnected(s, 5)); // g sc to f
        assertEquals(true, scc.isStronglyConnected(s, 6)); // g sc to g

        assertEquals(false, scc.isStronglyConnected(s, 0)); // g sc to a
        assertEquals(false, scc.isStronglyConnected(s, 1)); // g sc to b
        assertEquals(false, scc.isStronglyConnected(s, 4)); // g sc to e
        assertEquals(false, scc.isStronglyConnected(s, 2)); // g sc to c
        assertEquals(false, scc.isStronglyConnected(s, 3)); // g sc to d
        assertEquals(false, scc.isStronglyConnected(s, 7)); // g sc to h
    }

    @Test
    public void isStronglyConnectedH() throws Exception {
        int s = 7;
        assertEquals(true, scc.isStronglyConnected(s, 2)); // h sc to c
        assertEquals(true, scc.isStronglyConnected(s, 3)); // h sc to d
        assertEquals(true, scc.isStronglyConnected(s, 7)); // h sc to h

        assertEquals(false, scc.isStronglyConnected(s, 0)); // h sc to a
        assertEquals(false, scc.isStronglyConnected(s, 1)); // h sc to b
        assertEquals(false, scc.isStronglyConnected(s, 4)); // h sc to e
        assertEquals(false, scc.isStronglyConnected(s, 5)); // h sc to f
        assertEquals(false, scc.isStronglyConnected(s, 6)); // h sc to g
    }

    @Test
    public void getCount() throws Exception {
        assertEquals(3, scc.getCount());
    }
}