public class Exemple4 {

  private static Plugin loadPlugin(String className) {
    Class c = null;   
    try {        
      c = Class.forName(className); 
    } 
    catch(ClassNotFoundException e) {
      System.err.println("Classe " + className + " non trouvée");
      e.printStackTrace();   
      return null;
    }        
        
    try {   
      Object o = c.newInstance();      
      return (Plugin) o;
    } 
    catch(InstantiationException e) {  
      System.err.println("Erreur dans l'instantiation de la classe "
			 + className);
      e.printStackTrace();
      return null;
    }    
    catch(IllegalAccessException e) {  
      System.err.println("Erreur dans l'instantiation de la classe "
			 + className);
      e.printStackTrace();
      return null;
    }    
  }

  public static void main(String[] args) {
    for (int i = 0; i < 5; i++) {
      Plugin plugin = loadPlugin("Plugin1");
      plugin.decrisToi();
      try {
	Thread.sleep(5000);
      }
      catch(InterruptedException e) {
	e.printStackTrace();
      }
    }
  }
}

