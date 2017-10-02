package fr.unice;

import static fr.unice.AnalyseurDeClasse.analyseClasse;

public class Main {

    public static void main(String[] args) {
        try {
            analyseClasse("java.util.HashMap");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
