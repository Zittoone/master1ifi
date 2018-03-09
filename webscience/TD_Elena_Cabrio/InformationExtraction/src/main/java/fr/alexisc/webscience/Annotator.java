package fr.alexisc.webscience;

import edu.stanford.nlp.ling.HasWord;
import edu.stanford.nlp.ling.Label;
import edu.stanford.nlp.parser.lexparser.LexicalizedParser;
import edu.stanford.nlp.process.DocumentPreprocessor;
import edu.stanford.nlp.trees.Tree;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.URI;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

/**
 * Created by Alexis Couvreur on 05/03/2018.
 */
public class Annotator {

    LexicalizedParser lp;
    /**
     * The name of the given entity
     */
    private Entity entity;
    private PrintWriter writer;
    private BufferedReader reader;

    /**
     * Instantiates a new Annotator.
     *
     * @param entity the entity
     */
    public Annotator(Entity entity) {
        this.entity = entity;
        lp = App.lp;
    }

    /**
     * Annotate the file and creates a new one.
     *
     * @throws IOException the io exception
     */
    public void annotate() throws IOException {

        writer = new PrintWriter(App.CORPUSES_ANNOTATED_PATH + entity.getCorpusFile().getName().split("\\.")[0] + "_annotated.txt");
        reader = new BufferedReader(new FileReader(App.CORPUSES_PATH + entity.getCorpusFile().getName()));

        List<String> decomposedEntity = entity.getRecognizers();

        String line;

        while((line = reader.readLine()) != null){
            writer.println(line.replaceAll(entity.getRegex(), "<entity name=\"" + entity.getURI().toString() + "\">$0</entity>"));
        }

        reader.close();
        writer.close();
    }


    /**
     * Gets birth date triple.
     *
     * @param entity the entity
     * @return the birth date triple
     * @throws IOException the io exception
     */
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

    /**
     * Gets type triples.
     *
     * @param entity the entity
     * @return the type triples
     * @throws IOException the io exception
     */
    public List<String> getTypeTriples(Entity entity) throws IOException {

        reader = new BufferedReader(new FileReader(App.CORPUSES_PATH + entity.getCorpusFile().getName()));
        List<String> objects = new ArrayList<>();


        for(List<HasWord> sentence : new DocumentPreprocessor(reader)){

            Tree parse = lp.apply(sentence);
            Optional<String> infoTriple = extractInformation(parse, entity);

            infoTriple.ifPresent(objects::add);
            parse.pennPrint();
        }

        reader.close();

        return objects;
    }

    private Optional<String> extractInformation(Tree root, Entity entity) {
        if(!Objects.equals(root.value(), "ROOT")){
            return Optional.empty();
        }

        Tree current = root.firstChild();
        if(!Objects.equals(current.value(), "S")){
            return Optional.empty();
        }

        Tree[] children = current.children();
        if(children.length < 2){
            return Optional.empty();
        }

        if(isEntityInNounPhrase(entity, children[0]) ){
            return extractObject(entity, children[1]);
        }

        return Optional.empty();
    }

    private Optional<String> extractObject(Entity entity, Tree tree) {

        if(tree.value().equals("VP")){
            Tree[] children = tree.children();

            // VB* and NP only
            if(children.length == 2){
                String vc0 = children[0].value();
                String vc01 = children[0].yield().get(0).value();
                // System.out.println(tree.yield() + " => " + vc0 + " : " + vc01);
                if (vc0.startsWith("VB") && (vc01.equals("is") || vc01.equals("was") || vc01.equals("has"))) {
                    return extractObject(entity, children[1]);
                }
            }
        } else if(tree.value().equals("NP")){

            if(tree.children()[0].value().equals("NP")){
                return extractObject(entity, tree.children()[0]);
            }

            List<Tree> found = tree.getChildrenAsList().stream()
                    .filter(t -> t.value().startsWith("JJ") || t.value().startsWith("NN")).collect(Collectors.toList());
            StringBuilder sb = new StringBuilder();

            if(found.isEmpty())
                return Optional.empty();

            found.forEach(t -> {
                sb.append(t.yield()).append(" ");
            });
            sb.deleteCharAt(sb.length() - 1);
            return Optional.of("<\"" + entity.getURI() + "\", \"type\", \"" +
                    sb.toString().replaceAll("\\[", "").replaceAll("\\]","") + "\">");
        } else {
            // Find the first vp
        }

        return Optional.empty();
    }

    private boolean isEntityInNounPhrase(Entity entity, Tree tree) {

        String v = tree.value();
        if (!(v.startsWith("NP") || v.startsWith("NN") || v.startsWith("PR"))) {
            return false;
        }

        // Join the elements with spaces to match the regex easily
        String v2 = String.join(" ", tree.yield().stream().map(Label::value).collect(Collectors.toList()));

        Pattern pattern = Pattern.compile(entity.getRegex());
        Matcher matcher = pattern.matcher(v2);

        return matcher.find() /*|| !tree.getChildrenAsList().stream().filter(node -> isEntityInNounPhrase(entity, node)).collect(Collectors.toList()).isEmpty()*/;
    }


    /**
     * Gets relation triples.
     *
     * @param entity the entity
     * @param uriMap the uri map
     * @return the relation triples
     */
    public List<String> getRelationTriples(Entity entity, Map<String, URI> uriMap) throws IOException {

        reader = new BufferedReader(new FileReader(App.CORPUSES_PATH + entity.getCorpusFile().getName()));

        List<String> objects = new ArrayList<>();

        for (List<HasWord> sentence : new DocumentPreprocessor(reader)) {
            /*Tree parse = lp.apply(sentence);
            Optional<String> infoTriple = extractInformation(parse, entity);

            infoTriple.ifPresent(objects::add);
            parse.pennPrint();*/
        }

        reader.close();

        return objects;
    }
}
