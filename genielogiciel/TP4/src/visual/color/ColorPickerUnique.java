package visual.color;

import java.awt.*;
import java.util.Random;

public class ColorPickerUnique implements IColorPicker {

    private float r;
    private float g;
    private float b;

    public ColorPickerUnique(){
        Random rand = new Random();
        r = rand.nextFloat();
        g = rand.nextFloat();
        b = rand.nextFloat();
    }


    public ColorPickerUnique(float r, float g, float b) {
        this.r = r;
        this.g = g;
        this.b = b;
    }

    public ColorPickerUnique(Color color){
        r = color.getRed()   / 255;
        g = color.getGreen() / 255;
        b = color.getBlue()  / 255;
    }

    @Override
    public Color getNextColor() {
        return new Color(r, g, b);
    }
}
