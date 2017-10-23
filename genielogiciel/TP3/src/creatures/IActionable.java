package creatures;

public interface IActionable {
    /**
     * The core method of a creature. It is suppose to modify its internal state
     * (position, etc.) in a response to an environment. It can use methods
     * defined in the {@link #environment}.
     */
    void act();
}
