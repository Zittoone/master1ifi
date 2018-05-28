package fr.unice.masterifi.graph.scc;

import fr.unice.masterifi.graph.DirectedGraph;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Created by Alexis Couvreur on 28/05/2018.
 */
public class GabowSCCTest {

    DirectedGraph g;
    GabowSCC scc;

    @Before
    public void setUp() throws Exception {
        g = new DirectedGraph(8);
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

        scc = new GabowSCC(g);
    }

    @Test
    public void isStronglyConnectedA() throws Exception {

        /* A */
        assertEquals(true, scc.isStronglyConnected(0, 1));
        assertEquals(false, scc.isStronglyConnected(0, 2));
        assertEquals(false, scc.isStronglyConnected(0, 3));
        assertEquals(true, scc.isStronglyConnected(0, 4));
        assertEquals(false, scc.isStronglyConnected(0, 5));
        assertEquals(false, scc.isStronglyConnected(0, 6));
        assertEquals(false, scc.isStronglyConnected(0, 7));

        /* B */
        assertEquals(false, scc.isStronglyConnected(1, 2));
        assertEquals(false, scc.isStronglyConnected(1, 3));
        assertEquals(true, scc.isStronglyConnected(1, 4));
        assertEquals(false, scc.isStronglyConnected(1, 5));
        assertEquals(false, scc.isStronglyConnected(1, 6));
        assertEquals(false, scc.isStronglyConnected(1, 7));

        /* C */
        assertEquals(true, scc.isStronglyConnected(2, 3));
        assertEquals(false, scc.isStronglyConnected(2, 4));
        assertEquals(false, scc.isStronglyConnected(2, 5));
        assertEquals(false, scc.isStronglyConnected(2, 6));
        assertEquals(true, scc.isStronglyConnected(2, 7));

        /* D */
        assertEquals(false, scc.isStronglyConnected(3, 4));
        assertEquals(false, scc.isStronglyConnected(3, 5));
        assertEquals(false, scc.isStronglyConnected(3, 6));
        assertEquals(true, scc.isStronglyConnected(3, 7));

        /* E */
        assertEquals(false, scc.isStronglyConnected(4, 5));
        assertEquals(false, scc.isStronglyConnected(4, 6));
        assertEquals(false, scc.isStronglyConnected(4, 7));

        /* F */
        assertEquals(true, scc.isStronglyConnected(5, 6));
        assertEquals(false, scc.isStronglyConnected(5, 7));

        /* G */
        assertEquals(false, scc.isStronglyConnected(6, 7));
    }

    @Test
    public void getCount() throws Exception {
        assertEquals(3, scc.getCount());
    }

    @Test
    public void id() throws Exception {
    }

}