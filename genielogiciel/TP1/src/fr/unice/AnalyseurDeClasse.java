package fr.unice;
/**
 * @version 1.00 23 Mars 2001
 * @author Michel Buffa
 * Inspir� par la classe Reflectiontest.java de
 * Cay S. Horstmann & Gary Cornell, publi�e dans le livre Core Java, Sun Press
 */

import com.sun.org.apache.xpath.internal.operations.Mod;

import java.lang.reflect.*;
import java.io.*;

// TODO: exception handling

public class AnalyseurDeClasse {

    public static void analyseClasse(String nomClasse) throws ClassNotFoundException {
        // R�cup�ration d'un objet de type Class correspondant au nom pass� en param�tres
        Class cl = getClasse(nomClasse);

        afficheEnTeteClasse(cl);

        System.out.println();
        afficheAttributs(cl);

        System.out.println();
        afficheConstructeurs(cl);

        System.out.println();
        afficheMethodes(cl);

        // L'accolade fermante de fin de classe !
        System.out.println("}");
    }


    /**
     * Retourne la classe dont le nom est pass� en param�tre
     */
    public static Class getClasse(String nomClasse) throws ClassNotFoundException {
        return Class.forName(nomClasse);
    }

    /**
     * Cette m�thode affiche par ex "public class Toto extends Tata implements Titi, Tutu {"
     */
    public static void afficheEnTeteClasse(Class cl) {
        //  Affichage du modifier et du nom de la classe
        int mod = cl.getClass().getModifiers();
        System.out.print(Modifier.toString(mod) + " ");

        System.out.print(cl.getName() + " ");

        System.out.print(getTypeParameters(cl) + " ");

        // R�cup�ration de la superclasse si elle existe (null si cl est le type Object)
        Class supercl = cl.getSuperclass();

        // On ecrit le "extends " que si la superclasse est non nulle et
        // diff�rente de Object
        if (supercl != null && !supercl.getClass().getName().equals("Object")) {
            System.out.print("extends " + supercl.getName());
        }

        // Affichage des interfaces que la classe implemente
        Class[] interfaces = cl.getInterfaces();
        if (interfaces[0] != null) {
            System.out.print(" implements");

            for (int i = 0; i < interfaces.length; i++) {
                System.out.print(interfaces[i].getName());
                if (i + 1 < interfaces.length) {
                    System.out.print(", ");
                }
            }
        }

        // Enfin, l'accolade ouvrante !
        System.out.print(" {\n");
    }

    public static void afficheAttributs(Class cl) {

        for (Field f : cl.getDeclaredFields()) {
            System.out.println(Modifier.toString(f.getModifiers()) + " " + f.getType().getName() + " " + f.getName() + ";");
        }

    /*System.out.println("");

    for (Field f : cl.getFields()) {
      System.out.println(Modifier.toString(f.getModifiers()) + " " + f.getType().getName() + " " + f.getName() + ";");
    }*/
    }

    public static void afficheConstructeurs(Class cl) {
        for (Constructor c : cl.getDeclaredConstructors()) {

            System.out.println(
                    Modifier.toString(c.getModifiers())
                            + " " + c.getName() +
                            getTypeParameters(cl) + " "
                            + getArguments(c.getParameterTypes()) + "{}");
        }

    }

    private static String getTypeParameters(Class cl) {
        StringBuilder genericParameters = new StringBuilder();
        if (cl.getTypeParameters().length > 0) {
            genericParameters.append("<");

            for (int i = 0; i < cl.getTypeParameters().length; i++) {
                genericParameters.append(cl.getTypeParameters()[i].getName());
                if (i + 1 < cl.getTypeParameters().length) {
                    genericParameters.append(", ");
                }
            }

            genericParameters.append(">");
        }

        return genericParameters.toString();
    }

    private static String getArguments(Class<?>[] cl) {
        StringBuilder argumentsParameters = new StringBuilder();

        argumentsParameters.append("(");

        for (int i = 0; i < cl.length; i++) {
            argumentsParameters.append(cl[i].getName()).append(getTypeParameters(cl[i]));
            if (i + 1 < cl.length) {
                argumentsParameters.append(", ");
            }
        }

        argumentsParameters.append(")");

        return argumentsParameters.toString();
    }


    public static void afficheMethodes(Class cl) {
        for (Method c : cl.getMethods()) {

            System.out.println(
                    Modifier.toString(c.getModifiers())
                            + " " + c.getName() +
                            getTypeParameters(cl) + " "
                            + getArguments(c.getParameterTypes()) + "{}");
        }
    }

    public static String litChaineAuClavier() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        return br.readLine();
    }

    public static void main(String[] args) {
        boolean ok = false;

        while (!ok) {
            try {
                System.out.print("Entrez le nom d'une classe (ex : java.util.Date): ");
                String nomClasse = litChaineAuClavier();

                analyseClasse(nomClasse);

                ok = true;
            } catch (ClassNotFoundException e) {
                System.out.println("Classe non trouv�e.");
            } catch (IOException e) {
                System.out.println("Erreur d'E/S!");
            }
        }
    }

}
