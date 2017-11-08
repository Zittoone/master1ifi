public class Exemple2 {    
  public static void main(String []args) {
    Class c = null;      
    
    try {        
      c = Class.forName("ClasseC");      
    } 
    catch(ClassNotFoundException e) {   
      System.err.println("Classe ClasseC non trouvée");
      e.printStackTrace();
    }  

    try {    
      c.newInstance();   
    } 
    catch(InstantiationException e) {  
      System.err.println("Erreur dans l'instatiation de la classe ClasseC");
      e.printStackTrace();
    }    
    catch(IllegalAccessException e) {  
      System.err.println("Erreur dans l'instatiation de la classe ClasseC");
      e.printStackTrace();
    }    
  }
}
