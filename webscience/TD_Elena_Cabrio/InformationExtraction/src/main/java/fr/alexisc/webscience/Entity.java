package fr.alexisc.webscience;

import com.google.gson.Gson;
import com.google.gson.JsonObject;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URI;
import java.net.URL;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Created by Alexis Couvreur on 07/03/2018.
 */
public class Entity {

    private URI uri;
    private String name;
    private File corpus;
    private String gender;

    public Entity(URI uri, File corpus) {
        this.uri = uri;
        this.corpus = corpus;
        this.name = corpus.getName().split("\\.")[0].replace("_", " ");
        this.gender = GenderAPI.getGender(getDecomposedName(" ")[0]);
    }

    public URI getURI() {
        return uri;
    }

    public String getName() {
        return name;
    }

    public String[] getDecomposedName(String delimiter) {
        return name.split(delimiter);
    }

    public List<String> getRecognizers() {

        List<String> recognizers = new ArrayList<>();
        String[] decomposedName = getDecomposedName(" ");
        Collections.addAll(recognizers, decomposedName);
        if (gender.equals("female")) {
            recognizers.add("she");
            recognizers.add("She");
        } else if (gender.equals("male")) {
            recognizers.add("he");
            recognizers.add("He");
        }
        return recognizers;
    }

    public String getRegex() {
        StringBuilder regexp = new StringBuilder();
        regexp.append("\\b(").append(getName()).append("\\b)");
        getRecognizers().forEach(part -> regexp.append("|").append("\\b(").append(part).append(")\\b"));

        return regexp.toString();
    }

    public File getCorpusFile() {
        return corpus;
    }

    private static class GenderAPI {

        public static String getGender(String name) {

            try {

                String myKey = "QZxwMorsEARZadRGse";

                URL url = new URL("https://gender-api.com/get?key=" + myKey + "&name=" + name);

                HttpURLConnection conn = (HttpURLConnection) url.openConnection();


                if (conn.getResponseCode() != 200) {

                    throw new RuntimeException("Error: " + conn.getResponseCode());

                }


                InputStreamReader input = new InputStreamReader(conn.getInputStream());

                BufferedReader reader = new BufferedReader(input);


                Gson gson = new Gson();

                JsonObject json = gson.fromJson(reader, JsonObject.class);

                String gender = json.get("gender").getAsString();

                conn.disconnect();
                return gender;
            } catch (IOException e) {

                e.printStackTrace();

            }
            return null;
        }
    }

}
