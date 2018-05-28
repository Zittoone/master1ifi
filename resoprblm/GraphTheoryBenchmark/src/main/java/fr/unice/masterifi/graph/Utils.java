package fr.unice.masterifi.graph;

import java.util.List;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

/**
 * Created by Alexis Couvreur on 28/05/2018.
 */
public class Utils {

    private static char[] alphabet = "abcdefghijklmnopqrstuvwxyz".toCharArray();
    private Utils() {}

    public static char toAlphabet(Integer i) { return alphabet[i]; }

    public static <T> String toStringListCustom(List<T> l, Function<T, ?> function) {
        StringBuilder sb = new StringBuilder();
        sb.append("{");
        l.forEach(e -> {
            sb.append(function.apply(e));
            if(l.indexOf(e) != l.size() - 1)
                sb.append(", ");
        });
        sb.append("}");
        return sb.toString();
    }

    public static <T> List<T> toList(final Iterable<T> iterable) {
        return StreamSupport.stream(iterable.spliterator(), false)
                .collect(Collectors.toList());
    }
}
