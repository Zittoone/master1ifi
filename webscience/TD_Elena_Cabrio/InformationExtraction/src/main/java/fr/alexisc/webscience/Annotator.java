package fr.alexisc.webscience;

import java.io.*;
import java.net.URI;
import java.util.Arrays;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Created by Alexis Couvreur on 05/03/2018.
 */
public class Annotator {

    /**
     * The name of the given entity
     */
    private Entity entity;
    private PrintWriter writer;
    private BufferedReader reader;

    /**
     * Instantiates a new Annotator.
     *
     */
    public Annotator(Entity entity) {
        this.entity = entity;
    }

    /**
     * Annotate the file and creates a new one.
     */
    public void annotate() throws IOException {

        writer = new PrintWriter(App.CORPUSES_ANNOTATED_PATH + entity.getCorpusFile().getName().split("\\.")[0] + "_annotated.txt");
        reader = new BufferedReader(new FileReader(App.CORPUSES_PATH + entity.getCorpusFile().getName()));

        String[] decomposedEntity = entity.getDecomposedName(" ");

        // Naive matching of the entity
        StringBuilder regexp = new StringBuilder();
        regexp.append("(").append(entity.getName());
        Arrays.stream(decomposedEntity).forEach( part -> regexp.append("|").append(part));
        regexp.append(")");

        String line;

        while((line = reader.readLine()) != null){
            writer.println(line.replaceAll(regexp.toString(), "<entity name=\"" + entity.getURI().toString() + "\">$1</entity>"));
        }

        reader.close();
        writer.close();
    }

}
