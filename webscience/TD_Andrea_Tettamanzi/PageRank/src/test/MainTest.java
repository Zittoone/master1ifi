

import org.junit.Test;

import java.io.*;

public class MainTest {

    @Test
    public void main() throws FileNotFoundException {
        String inputFile = "/home/alexisc/Documents/master1ifi/webscience/TD_Andrea_Tettamanzi/PageRank/src/test/resources/data.in";
        String outputFile = "/home/alexisc/Documents/master1ifi/webscience/TD_Andrea_Tettamanzi/PageRank/src/test/resources/data.out";

        PrintStream printStream = new PrintStream(new FileOutputStream(outputFile, true));

        System.setOut(printStream);

        Main.main(inputFile);

        printStream.close();
    }
}