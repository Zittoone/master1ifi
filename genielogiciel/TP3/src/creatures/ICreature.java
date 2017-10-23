package creatures;

import java.awt.geom.Point2D;

public interface ICreature extends IActionable, IDrawable {

    double getSpeed();

    double getDirection();

    IEnvironment getEnvironment();

    Point2D getPosition();

    double directionFromAPoint(Point2D p, double axis);

    double distanceFromAPoint(Point2D p);

}
