package fr.alexisc.webscience;

import java.io.File;
import java.net.URI;

/**
 * Created by Alexis Couvreur on 07/03/2018.
 */
public class Entity {

    private URI uri;
    private String name;
    private File corpus;

    public Entity(URI uri, File corpus) {
        this.uri = uri;
        this.corpus = corpus;
        this.name = corpus.getName().split("\\.")[0].replace("_", " ");
    }

    public URI getURI() {
        return uri;
    }

    public String getName() {
        return name;
    }

    public String[] getDecomposedName(String delimiter){
        return name.split(delimiter);
    }

    public String[] getEntityRecongnizers(){
        return null;
    }

    public File getCorpusFile() {
        return corpus;
    }
}
