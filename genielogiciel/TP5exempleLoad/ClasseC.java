public class ClasseC {
  static {
    System.out.println("Chargement de ClasseC");
  }
    
  public ClasseC() {
    System.out.println("Exécution du constructeur de la classe C, et attente de 5 secondes");
    try {
      Thread.sleep(5000);
    } catch(InterruptedException e) {
      e.printStackTrace();
    }
    methode1();
  }
    
  public void methode1() {
    // ClasseD ne sera pas chargée avant l'exécution de cette instruction
    ClasseD o = new ClasseD();
  }
}
