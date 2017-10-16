package fr.unice.creatures;

import static java.lang.Math.PI;
import static java.lang.Math.cos;
import static java.lang.Math.random;
import static java.lang.Math.sin;

import java.awt.Color;

public class BouncingCreature extends AbstractCreature {

	private static final double MIN_SPEED = 3;
	private static final double MAX_SPEED = 10;

	/**
	 * Number of cycles after which we apply some random noise.
	 */
	private static final int NUMBER_OF_CYCLES_PER_CHANGE = 3000;

	/**
	 * Current step number from the last noise application.
	 */
	protected int currCycle;

	public BouncingCreature(Environment environment, double x, double y, double speed,
			double direction, Color color) {
		super(environment, x, y);

		this.speed = speed;
		this.direction = direction;
		this.color = color;

		currCycle = 0;
	}

	@Override
	public void act() {
		applyNoise();
		move();
	}

	/**
	 * Every number of cycles we apply some random noise over speed and
	 * direction
	 */
	public void applyNoise() {
		currCycle++;
		currCycle %= NUMBER_OF_CYCLES_PER_CHANGE;

		// every NUMBER_OF_CYCLES_PER_CHANGE we do the change
		if (currCycle == 0) {
			this.speed += ((random() * 2) - 1);

			// maintain the speed within some boundaries
			if (this.speed < MIN_SPEED) {
				this.speed = MIN_SPEED;
			} else if (this.speed > MAX_SPEED) {
				this.speed = MAX_SPEED;
			}

			setDirection(this.direction
					+ ((random() * PI / 2) - (PI / 4)));
		}
	}

	/**
	 * The actual move
	 */
	public void move() {
		double newX = x + speed * cos(direction);
		// the reason there is a minus instead of a plus is that in our plane
		// Y coordinates rises downwards
		double newY = y - speed * sin(direction);

		double hw = environment.getWidth() / 2;
		double hh = environment.getHeight() / 2;

		if (newX < -hw) {
			// BOUNCE LEFT
			newX = - 2*hw - newX; // Set the new position directly bounced
			setDirectionBounceX();
		} else if (newX > hw) {
			// BOUNCE RIGHT
			newX = 2*hw - newX;
			setDirectionBounceX();
		} else 	if (newY < -hh) {
			// BOUNCE TOP
			newY = - 2*hh - newY;
			setDirectionBounceY();
		} else if (newY > hh) {
			// BOUNCE BOTTOM
			newY = 2*hh - newY;
			setDirectionBounceY();
		}

		setX(newX);
		setY(newY);
	}

	private void setDirectionBounceX() {
		if (direction >= PI)
			// If it goes towards the bottom
			setDirection(3*PI - direction);
		else
		// Towards up
			setDirection(PI - direction);
	}

	private void setDirectionBounceY() {
		setDirection(PI * 2 - direction);
	}

}
