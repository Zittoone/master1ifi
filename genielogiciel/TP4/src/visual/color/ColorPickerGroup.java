package visual.color;

import java.awt.*;
import java.util.Random;

public class ColorPickerGroup implements IColorPicker {

    private float r;
    private float g;
    private float b;
    private int size, current;
    private Random rand;

    public ColorPickerGroup(int number) {

        if(number <= 0)
            size = 10;
        else size = number;
        current = 0;

        rand = new Random();

        changeColor();
    }

    private void changeColor() {
        r = rand.nextFloat();
        g = rand.nextFloat();
        b = rand.nextFloat();
    }

    @Override
    public Color getNextColor() {
        if(current == size){
            current = 0;
            changeColor();
        } else current++;

        return new Color(r, g, b);
    }

}
