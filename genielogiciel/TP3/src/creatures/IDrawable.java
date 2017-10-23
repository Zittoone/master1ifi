package creatures;

import java.awt.*;

public interface IDrawable {
    Color getColor();

    int getSize();

    void paint(Graphics2D g2);
}
