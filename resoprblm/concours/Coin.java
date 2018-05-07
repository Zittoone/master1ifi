import java.util.Scanner;

public class Coin {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        String line = sc.nextLine();

        int N = Integer.parseInt(line);

        for(int i = 0; i < N; i++) {
            ProgLandienneCoin p = new ProgLandienneCoin(Integer.parseInt(sc.nextLine()));
            System.out.println(p.getRealValue());
        }
    }

    private static class ProgLandienneCoin {
        public long value;
        public ProgLandienneCoin n2;
        public ProgLandienneCoin n3;
        public ProgLandienneCoin n4;

        public ProgLandienneCoin(long value) {
            this.value = value;
            long n2 = value / 2;
            long n3 = value / 3;
            long n4 = value / 4;

            if(n2 + n3 + n4 > value) {
                this.n2 = new ProgLandienneCoin(n2);
                this.n3 = new ProgLandienneCoin(n3);
                this.n4 = new ProgLandienneCoin(n4);
            }

        }

        public long getRealValue() {
            if(n2 != null) {
                return n2.getRealValue() + n3.getRealValue() + n4.getRealValue();
            }

            return value;
        }
    }
}
