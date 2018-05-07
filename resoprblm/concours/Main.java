import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int N = 15;
        int n = 0;

        String line = sc.nextLine();

        String[] strings = line.split(" ");

        int[] ints = new int[strings.length];
        for(int i = 0; i < strings.length; i++) {
            ints[i] = Integer.parseInt(strings[i]);
        }

        System.out.println("" + triABulle(ints));

    }

    private static int triABulle(int[] ints) {

        int nb = 0;
        for(int i = 0; i < ints.length; i++){
            for(int j = 1; j < ints.length; j++) {
                if(ints[j - 1] > ints[j]) {
                    nb++;
                    int tmp = ints[j - 1];
                    ints[j-1] = ints[j];
                    ints[j] = tmp;
                }
            }
        }
        return nb;
    }
}
