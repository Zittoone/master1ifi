package fr.unice.creatures;

import static org.mockito.Mockito.*;
import org.junit.Before;
import org.junit.Test;

import java.awt.*;

import static java.lang.Math.PI;
import static junit.framework.TestCase.assertEquals;

public class BouncingCreatureTest {


    private Environment environment;
    private BouncingCreature bouncingCreature;

    @Before
    public void setUp() throws Exception {
        environment = mock(Environment.class); //new Environment(100, 100);
        bouncingCreature = new BouncingCreature(environment, 0, 0, 10, 0, Color.RED);
    }

    @Test
    public void testBounceOnRight() {

        when(environment.getHeight()).thenReturn(200);
        when(environment.getWidth()).thenReturn(100);

        bouncingCreature.setDirection(0.0 * PI);
        // Move 7 times to get a bounce
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();

        assertEquals(PI, bouncingCreature.getDirection());

    }

    @Test
    public void testBounceOnRightFromBottom() {

        when(environment.getHeight()).thenReturn(200);
        when(environment.getWidth()).thenReturn(100);

        bouncingCreature.setDirection(PI / 4);
        // Move 8 times to get a bounce
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();

        assertEquals(3 * PI / 4, bouncingCreature.getDirection());

    }

    @Test
    public void testBounceOnRightFromTop() {

        when(environment.getHeight()).thenReturn(200);
        when(environment.getWidth()).thenReturn(100);

        bouncingCreature.setDirection(7 * PI / 4);
        // Move 8 times to get a bounce
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();

        assertEquals(5 * PI / 4, bouncingCreature.getDirection());

    }

    @Test
    public void testBounceOnLeft() {

        when(environment.getHeight()).thenReturn(200);
        when(environment.getWidth()).thenReturn(100);

        bouncingCreature.setDirection(PI);
        // Move 7 times to get a bounce
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();

        assertEquals(0.0 * PI, bouncingCreature.getDirection());

    }

    @Test
    public void testBounceOnLeftFromBottom() {

        when(environment.getHeight()).thenReturn(200);
        when(environment.getWidth()).thenReturn(100);

        bouncingCreature.setDirection(3 * PI/4 );
        // Move 8 times to get a bounce
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();

        assertEquals(PI / 4, bouncingCreature.getDirection());

    }

    @Test
    public void testBounceOnLeftFromTop() {

        when(environment.getHeight()).thenReturn(200);
        when(environment.getWidth()).thenReturn(100);

        bouncingCreature.setDirection(5 * PI / 4);
        // Move 8 times to get a bounce
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();

        assertEquals(7 * PI / 4, bouncingCreature.getDirection());

    }

    @Test
    public void testBounceOnTop() {

        when(environment.getHeight()).thenReturn(100);
        when(environment.getWidth()).thenReturn(200);

        bouncingCreature.setDirection(PI / 2);
        // Move 7 times to get a bounce
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();

        assertEquals(3 * PI / 2, bouncingCreature.getDirection());
    }

    @Test
    public void testBounceOnTopFromRight() {

        when(environment.getHeight()).thenReturn(100);
        when(environment.getWidth()).thenReturn(200);

        bouncingCreature.setDirection(PI / 2);
        // Move 8 times to get a bounce
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();

        assertEquals(3 * PI / 2, bouncingCreature.getDirection());
    }

    @Test
    public void testBounceOnTopFromLeft() {

        when(environment.getHeight()).thenReturn(100);
        when(environment.getWidth()).thenReturn(200);

        bouncingCreature.setDirection(PI / 4);
        // Move 8 times to get a bounce
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();

        assertEquals(7 * PI / 4, bouncingCreature.getDirection());
    }

    @Test
    public void testBounceOnBottom() {

        when(environment.getHeight()).thenReturn(100);
        when(environment.getWidth()).thenReturn(200);

        bouncingCreature.setDirection(3 * PI / 2);
        // Move 7 times to get a bounce
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();

        assertEquals(PI / 2, bouncingCreature.getDirection());

    }

    @Test
    public void testBounceOnBottomFromRight() {

        when(environment.getHeight()).thenReturn(100);
        when(environment.getWidth()).thenReturn(200);

        bouncingCreature.setDirection(5 * PI / 4);
        // Move 8 times to get a bounce
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();

        assertEquals(3 * PI / 4, bouncingCreature.getDirection());

    }

    @Test
    public void testBounceOnBottomFromLeft() {

        when(environment.getHeight()).thenReturn(100);
        when(environment.getWidth()).thenReturn(200);

        bouncingCreature.setDirection(7 * PI / 4);
        // Move 8 times to get a bounce
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();
        bouncingCreature.move();

        assertEquals( PI / 4, bouncingCreature.getDirection());

    }

    @Test
    public void testMockEmergence() {


    }
}
