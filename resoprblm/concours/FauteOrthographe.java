import java.util.Scanner;

public class FauteOrthographe {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String line = sc.nextLine();

        int N = Integer.parseInt(line);

        for(int i = 1; i <= N; i++) {
            String[] lineS = sc.nextLine().split(" ");
            int index = Integer.parseInt(lineS[0]);
            char[] word = lineS[1].toCharArray();

            if(i != N) {
                System.out.println(i + " " + getWordMinus(word, index - 1));
            } else {
                System.out.print(i + " " + getWordMinus(word, index - 1));
            }

        }

    }

    private static String getWordMinus(char[] word, int indexMinus) {

        StringBuilder nword = new StringBuilder();
        for(int i = 0; i < word.length; i++){
            if(i != indexMinus){
                nword.append(word[i]);
            }
        }

        return nword.toString();
    }


}
