package fr.alexisc.webscience;

import java.io.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;
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


    public String getBirthDateTriple(Entity entity) throws IOException {

        reader = new BufferedReader(new FileReader(App.CORPUSES_PATH + entity.getCorpusFile().getName()));

        String regex = "([0-9]?[0-9]) ([A-Za-z]+) ([0-9][0-9][0-9][0-9])";

        // The date of birth is almost always inside the first sentence so fo this version we will only check the first sentence
        String line = reader.readLine();
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(line);

        reader.close();

        if(matcher.find()){
            Date date = null;
            try {
                date = new SimpleDateFormat("dd MMMM yyyy", new Locale("en,EN")).parse(matcher.group());
            } catch (ParseException e) {
                e.printStackTrace();
                return null;
            }
            Calendar cal = Calendar.getInstance();
            cal.setTime(date);

            return "<\"" + entity.getURI().toString() + "\", \"hasDate\"" + ", \"" + cal.get(Calendar.YEAR) + "-" + cal.get(Calendar.MONTH) + "-" + cal.get(Calendar.DAY_OF_MONTH) + "\">";
        } else {
            return null;
        }
    }

    public List<String> getTypeTriples(Entity entity) {

        return null;
    }
}
