package creatures.factory;

import creatures.BouncingCreature;
import creatures.ICreature;
import creatures.IEnvironment;

import java.util.List;

public class CreatureFactory {

    private ICreatureFactory bouncingCreatureFactory = new BouncingCreatureFactory();
    private ICreatureFactory smartCreatureFactory    = new SmartCreatureFactory();
    private ICreatureFactory stupidCreatureFactory   = new StupidCreatureFactory();

    public List<ICreature> createBouncingCreatures(IEnvironment env, int number) {

        return bouncingCreatureFactory.createCreatures(env, number);
    }

    public List<ICreature> createSmartCreatures(IEnvironment env, int number) {

        return smartCreatureFactory.createCreatures(env, number);
    }

    public List<ICreature> createStupidCreatures(IEnvironment env, int number) {

        return stupidCreatureFactory.createCreatures(env, number);
    }

}
