package fr.unice.creatures;

import java.awt.*;
import java.util.List;

import static java.lang.Math.cos;
import static java.lang.Math.sin;

public class SmartCreature extends AbstractCreature {

    public SmartCreature(Environment environment, double x, double y,
                          double direction, double speed, Color color) {
        super(environment, x, y);

        this.direction = direction;
        this.speed = speed;
        this.color = color;
    }

    /*
    Créez une nouvelle classe SmartCreature qui simule le comportement suivant :

    Essaye d'aller à la vitesse moyenne des créatures autour
    Va dans la direction moyenne du troupeau environnant (les créatures autour)
    Maintient une distance minimale avec celles qui sont autour

Vous pouvez construire le comportement de votre créature au fur et à mesure en définissant la méthode act(). Regardez bien les méthodes utilitaires fournies dans les classes AbstractCreature et Environment : les annexes en bas de page peuvent bien vous aider.
     */
    @Override
    public void act() {

        double moySpeed = 0.;
        double moyDirection = 0.;

        List<AbstractCreature> creaturesAround = environment.creaturesAround(this);
        if(!creaturesAround.isEmpty()){

            for (AbstractCreature creature : creaturesAround){
                moySpeed += creature.getSpeed();
                moyDirection += creature.getDirection();

                if(creature.distanceFromAPoint(this.position()) < 5){
                    moyDirection = -direction * creaturesAround.size();
                    break;
                }
            }

            speed = moySpeed / creaturesAround.size();
            direction = moyDirection / creaturesAround.size();

        }

        double incX = speed * cos(direction);
        double incY = - speed * sin(direction);

        move(incX, incY);
    }
}
