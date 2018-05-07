import javax.xml.bind.DatatypeConverter;
import java.util.Scanner;

public class Mirroir {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);


        String[] lineSplit = sc.nextLine().split(" ");

        String number = lineSplit[0].replace("0x", "");
        int size = Integer.parseInt(lineSplit[1]);

        StringBuilder binary = new StringBuilder();
        binary.append(Integer.toBinaryString(Integer.parseInt(number, 16)));

        while(binary.length() < size) {
            binary.insert(0, "0");
        }

        String sub = new StringBuilder(binary.toString().substring(binary.length() - size, binary.length())).reverse().toString();

        binary.replace(binary.length() - size, binary.length(), sub);

        long decimal = Long.parseLong(binary.toString(),2);
        String hexStr = Long.toString(decimal,16);
        System.out.println("0x" + hexStr.toUpperCase());
        // System.out.println(Integer.toString(Integer.parseInt(number, 16), base));
    }

    public static byte[] hexStringToByteArray(String s) {
        int len = s.length();
        byte[] data = new byte[len / 2];
        for (int i = 0; i < len; i += 2) {
            data[i / 2] = (byte) ((Character.digit(s.charAt(i), 16) << 4)
                    + Character.digit(s.charAt(i+1), 16));
        }
        return data;
    }
}
