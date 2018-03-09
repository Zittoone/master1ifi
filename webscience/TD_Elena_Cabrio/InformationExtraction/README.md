# Information Extraction from Wikipedia pages

## Exercise 1

We first decompose the entity name, we add to our regular expression the full entity name, first name, last name.

__Example : Catherine_Deneuve.txt__

1. We extract the entity of the file :  
From __"Catherine Deneuve"__ we create a regular expression matching : *"Catherine Deneuve" | "Catherine" | "Deneuve" | "She" | "she"*.  

    
2. We iterate over the file :  
Each time our regular expression match we add the entity tag.

3. We produce the annotated file :  
"__Catherine_Deneuve_annotated.txt__" under the directory "__annotated__" inside the corpuses.

Pronouns are defined thanks to [the Gender-API](https://gender-api.com).

## Exercise 2  

To extract the birth dates, given the wikipedia pages pattern to put birth dates inside the first sentence.
The regular expression can match a full date (day, month and year), extract it from the first sentence and returns the triple.

It is all assumed upon the wikipedia pages presentation, which is why it works.

__Example : Catherine_Deneuve.txt__

1. We build our regular expression :  
`"([0-9]?[0-9]) ([A-Za-z]+) ([0-9][0-9][0-9][0-9])"`  
  This will match any date format like : **numerical date** then **literal month** then **numerical year**.
    
2. We read the first line and extract if it exists :  
> Catherine Deneuve (French: [katʁin dənœv]; born __22 October 1943__) is a French actress who gained recognition for her portrayal of aloof, mysterious beauties for various directors, including Luis Buñuel and Roman Polanski.

3. We produce the triple :  
__<"http://en.wikipedia.org/wiki/Catherine_Deneuve", "hasDate", "1943-9-22">__

## Exercise 3

For this exercise i wanted something stronger than a regular expression, so i used the [The Stanford Parser](https://nlp.stanford.edu/software/lex-parser.shtml), thanks to this i'm able to produce __Part of Speech__ tagging and **chunked** sentences.  
To extract an information about a given entity i will use the following pattern :

1. break down the file into sentences ;
2. for each sentences check the grammatical structure :
    * use [The Stanford Parser](https://nlp.stanford.edu/software/lex-parser.shtml) to tag the text ;
    * use [The Stanford Parser](https://nlp.stanford.edu/software/lex-parser.shtml) to parse the text and result in a Tree ;
    * the tree gives the grammatical category ;
    * if the sentence (tagged __S__) has the entity as a subject, a __verb__ that is "was" or "is" and then a noun phrase from which we extract adjectives and nouns.
3. we then can build the triple.

I tried to be a bit more complex by extracting recursively information from a noun phrase, because when the sentence does not end after the information we want to extract, this noun phrase is wrapped inside a bigger noun phrase, so until there is a noun phrase children i extract the information from this one.  See `private Optional<String> extractObject(Entity entity, Tree tree) ` method inside `Annotator` class.

__Example : Alessandro_Papetti.txt__

This is the tree that [The Stanford Parser](https://nlp.stanford.edu/software/lex-parser.shtml) gives us, and we can extract one data here with our algorithm : Alessandro Papetti is an Italian painter.
```
(ROOT
  (S
    (NP <--- Noun Phrase detected as a start so we check into for the entity
      (NP (NNP Alessandro) (NNP Papetti))  <--- The entity is recongnized
      (PRN (-LRB- -LRB-)
        (VP (VBN born)
          (NP (CD 1958))
          (PP (IN in)
            (NP (NNP Milan))))
        (-RRB- -RRB-)))
    (VP (VBZ is) <--- Verbal phrase as a second argument recongnized and it's the verb "be"
      (NP (DT an) (JJ Italian) (NN painter))) <--- We look deeper inside and can extract adjectives and nouns.
    (. .)))
```
Thus we can extract these triples from the whole text :  
* <"http://en.wikipedia.org/wiki/Alessandro_Papetti", "type", "Italian painter">
* <"http://en.wikipedia.org/wiki/Alessandro_Papetti", "type", "self-taught artist">

> This is not perfect because it only match one pattern for the moment, but it can be easily improved.

## Exercise 4



## Start the program

## Improvments

For sure resolving coreferences would improve the program a lot beaucause every pronouns would now be replaced by the entity name and would extract the information

Stanford nlp