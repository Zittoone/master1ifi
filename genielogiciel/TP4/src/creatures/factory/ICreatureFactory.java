package creatures.factory;

import creatures.ICreature;
import creatures.IEnvironment;

import java.util.List;

public interface ICreatureFactory {

    List<ICreature> createCreatures(IEnvironment env, int number);

}
