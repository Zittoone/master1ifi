import com.sun.istack.internal.NotNull;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.text.DecimalFormat;
import java.util.Arrays;
import java.util.stream.Stream;

public class Main {

    public static void main(String... args) {

        int maxIterations;

        if(args.length == 2){
            maxIterations = Integer.parseInt(args[1]);
        } else if (args.length == 1){
            maxIterations = 3;
        } else {
            System.err.println("Usage : pagerank file [maxIteration]");
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

            System.out.println(printMatrix(S));

            /* compute G */
            double[][] G = getG(S, delta, getE(nbPage), nbPage);

            System.out.println(printMatrix(G));

            /* compute Pi */
            double[][] vector = new double[1][nbPage];

            // Pi = vector * G^0
            Arrays.fill(vector[0], 1. / nbPage);

            System.out.printf("Pi(%d) : \n", 0);
            System.out.println(printMatrix(vector));

            int t = 1;

            do {
                vector = multiplyByMatrix(vector, powerMatrix(G, t));

                System.out.printf("Pi(%d) : \n", t);
                System.out.println(printMatrix(vector));
                t++;
            } while(t < maxIterations);


        } catch (FileNotFoundException e) {
            System.err.println("The file \"" + args[0] + "\" was not found.");
        } catch (IOException e) {
            System.err.println("An error occurred reading the file (" + e.getMessage() + ").");
        }
    }


    /*
     *
     * Compute,from matrix S, matrix G = δS + (1−δ)E, for δ= 0.85 and a teleportation matrix E.
     *
     */
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

        return G;
    }

    /*
     * Matrix E,whose rows consist of  the vector u= (1/n,...,1/n).
     *
     */
    private static double[][] getE(int nbPage) {

        double[][] E = new double[nbPage][nbPage];

        for (int i = 0; i < nbPage; i++) {
            Arrays.fill(E[i], 1. / nbPage);
        }

        return E;
    }

    private static double[][] multiplyByValue(@NotNull double[][] matrix, double v) {

        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[i].length; j++) {
                matrix[i][j] *= v;
            }
        }

        return matrix;
    }

    private static double[][] multiplyByMatrix(@NotNull double[][] a, @NotNull double[][] b) {
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

    private static double[][] powerMatrix(@NotNull double[][] a, int p) {
        double[][] result = a;
        for (int n = 1; n < p; ++ n)
            result = multiplyByMatrix(result, a);
        return result;
    }

    private static String printMatrix(@NotNull double[][] m){

        StringBuilder sb = new StringBuilder();
        DecimalFormat df = new DecimalFormat("0.000");

        sb.append("[");
        for (int i = 0; i < m.length; i++) {
            sb.append("[");
            for (int j = 0; j < m[i].length; j++) {
                sb.append(df.format(m[i][j]));
                if(j != m[i].length - 1)
                    sb.append(", ");
            }
            sb.append("]");
            if(i != m.length - 1)
                sb.append(",\n");
        }
        sb.append("]\n");

        return sb.toString();
    }
}
