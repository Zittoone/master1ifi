package fr.unice;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.stream.Stream;

public class Main {

    public static void main(String[] args) {

        if (args.length != 1) {
            System.err.println("Usage : pagerank <file>");
            return;
        }

        int nbPage;
        double S[][];
        double delta = 0.85;

        try {

            /* Initialisation */
            BufferedReader br = new BufferedReader(new FileReader(args[0]));
            nbPage = Integer.parseInt(br.readLine());
            S = new double[nbPage][nbPage];

            /* Fill the matrix with initial values */
            for (int i = 0; i < nbPage; i++) {
                S[i] = Stream.of(br.readLine().split(" ")).mapToDouble(Double::parseDouble).toArray();
            }

            /* compute G */
            double[][] G = getG(S, delta, getE(nbPage), nbPage);

            /* compute Pi */
            double[] vector = new double[nbPage];
            Arrays.fill(vector, 1 / nbPage);

            int t = 0;

            do {

            } while(true);


        } catch (FileNotFoundException e) {
            System.err.println("The file \"" + args[0] + "\" was not found.");
        } catch (IOException e) {
            System.err.println("An error occurred reading the file (" + e.getMessage() + ").");
        }
    }


    private static double[][] getG(double[][] S, double delta, double[][] E, int nbPage) {

        double[][] G = new double[nbPage][nbPage];

        /* compute S by delta */
        S = multiplyByValue(S, delta);

        /* compute E by 1 - delta */
        E = multiplyByValue(E, 1 - delta);

        for (int i = 0; i < nbPage; i++) {
            for (int j = 0; j < nbPage; j++) {
                G[i][j] = S[i][j] + E[i][j];
            }
        }

        return null;
    }

    private static double[][] getE(int nbPage) {

        double[][] E = new double[nbPage][nbPage];

        for (int i = 0; i < nbPage; i++) {
            Arrays.fill(E[i], 1.);
        }

        return E;
    }

    private static double[][] multiplyByValue(double[][] matrix, double v) {

        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[i].length; j++) {
                matrix[i][j] *= v;
            }
        }

        return matrix;
    }

    public static double[][] multiplyByMatrix(double[][] a, double[][] b) {
        int m1ColLength = a[0].length;
        int m2RowLength = b.length;
        if (m1ColLength != m2RowLength) return null;
        int mRRowLength = a.length;
        int mRColLength = b[0].length;
        double[][] mResult = new double[mRRowLength][mRColLength];
        for (int i = 0; i < mRRowLength; i++) {
            for (int j = 0; j < mRColLength; j++) {
                for (int k = 0; k < m1ColLength; k++) {
                    mResult[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return mResult;
    }
}
