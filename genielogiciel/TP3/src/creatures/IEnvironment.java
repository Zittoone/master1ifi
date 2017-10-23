package creatures;

import java.awt.*;

public interface IEnvironment {
    Iterable<ICreature> getCreatures();

    Dimension getSize();
}
