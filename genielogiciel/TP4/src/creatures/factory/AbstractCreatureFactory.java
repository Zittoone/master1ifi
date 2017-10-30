package creatures.factory;

import creatures.BouncingCreature;
import creatures.ICreature;
import creatures.IEnvironment;
import creatures.SmartCreature;
import visual.color.IColorPicker;

import java.awt.*;
import java.awt.geom.Point2D;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Random;

public class AbstractCreatureFactory {

    protected static AbstractCreatureFactory _singleton;

    public static void init(double inMaxSpeed) {

        if (_singleton != null) {
            throw new RuntimeException("CreatureFactory already created by "
                    + _singleton.getClass().getName());
        } else {
            _singleton = new AbstractCreatureFactory();
            maxSpeed = inMaxSpeed;
        }
    }

    public static AbstractCreatureFactory getCreatureFactory() {
        return _singleton;
    }

    private AbstractCreatureFactory() {
    }


    interface ICreatureCreator<T extends ICreature> {
        public T create(IEnvironment env, Point2D position, double speed,
                        double direction, Color color);
    }

    private static double maxSpeed = 10; // default value
    private final Random rand = new Random();

    public <T extends ICreature> Collection<T> createCreatures(IEnvironment env, int count, ICreatureCreator<T> creator) {
        Collection<T> creatures = new ArrayList<T>();

        Dimension s = env.getSize();

        for (int i=0; i<count; i++) {
            // X coordinate
            double x = (rand.nextDouble() * s.getWidth()) - s.getWidth() / 2;

            // Y coordinate
            double y = (rand.nextDouble() * s.getHeight()) - s.getHeight() / 2;

            // direction
            double direction = (rand.nextDouble() * 2 * Math.PI);

            // speed
            int speed = (int) (rand.nextDouble() * maxSpeed);

            T creature = creator.create(env, new Point2D.Double(x,y), speed, direction, Color.RED);
            creatures.add(creature);
        }

        return creatures;
    }

    public Collection<SmartCreature> createSmartCreatures(IEnvironment env, int count) {
        return createCreatures(env, count, new ICreatureCreator<SmartCreature>() {
            public SmartCreature create(IEnvironment env, Point2D position, double speed,
                                        double direction, Color color) {
                return new SmartCreature(env, position, direction, speed, color);
            }
        });
    }


    public Collection<BouncingCreature> createBouncingCreatures(IEnvironment env, int count, final IColorPicker colorStrategy) {
        return createCreatures(env, count, new ICreatureCreator<BouncingCreature>() {
            @Override
            public BouncingCreature create(IEnvironment env, Point2D position,
                                           double speed, double direction, Color color) {
                return new BouncingCreature(env, position, direction, speed, colorStrategy.getNextColor());
            }
        });
    }

}