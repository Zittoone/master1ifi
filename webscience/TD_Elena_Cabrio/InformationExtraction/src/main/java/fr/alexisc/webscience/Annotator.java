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
    private String entityName;
    private File corpus;
    private PrintWriter writer;
    private BufferedReader reader;
    private URI entityURI;

    /**
     * Instantiates a new Annotator.
     *
     * @param entityName the entity name
     * @param corpus     the corpus
     */
    public Annotator(String entityName, File corpus, URI entityURI) {
        this.corpus = corpus;
        this.entityName = entityName;
        this.entityURI = entityURI;
    }

    /**
     * Annotate the file and creates a new one.
     */
    public void annotate() throws IOException {

        writer = new PrintWriter(App.CORPUSES_ANNOTATED_PATH + corpus.getName().split("\\.")[0] + "_annotated.txt");
        reader = new BufferedReader(new FileReader(App.CORPUSES_PATH + corpus.getName()));

        String[] decomposedEntity = entityName.split(" ");

        // Naive matching of the entity
        StringBuilder regexp = new StringBuilder();
        regexp.append("(").append(entityName);
        Arrays.stream(decomposedEntity).forEach( part -> regexp.append("|").append(part));
        regexp.append(")");

        Pattern pattern = Pattern.compile(regexp.toString());
        String line;

        while((line = reader.readLine()) != null){

            Matcher matcher = pattern.matcher(line);
            StringBuffer sb = new StringBuffer();

            while(matcher.find()){
                matcher.appendReplacement(sb, "<entity name=\"" + entityURI.toString() + "\">" + matcher.group() + "</entity>");
            }

            writer.append(sb);
        }

        reader.close();
        writer.close();
    }

}
