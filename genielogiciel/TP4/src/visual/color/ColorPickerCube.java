package visual.color;

import java.awt.*;
import java.util.Random;

public class ColorPickerCube implements IColorPicker {

    private float r;
    private float g;
    private float b;
    private int number;

    public ColorPickerCube(int number) {
        this.number = number;
        r = 0.0f;
        g = 0.0f;
        b = 0.0f;
    }

    @Override
    public Color getNextColor() {
        // view the color space as a cube and then iterate over it using a small
        // steps
        float creaturesCountCubeRoot = (float) Math.pow(number, 1.0 / 3.0);
        float colorPhase = (float) (1.0 / creaturesCountCubeRoot);

        // color
        r += colorPhase;
        if (r > 1.0) {
            r -= 1.0f;
            g += colorPhase;
            if (g > 1.0) {
                g -= 1.0f;
                b += colorPhase;
                if (b > 1.0)
                    b -= 1.0f;
            }
        }

        return new Color(r, g, b);

    }

}
