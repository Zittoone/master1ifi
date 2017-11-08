public class ClasseA {
  // ClasseB ne sera jamais chargée !
  private ClasseB objet1;
  private ClasseC objet2;
    
  static {
    System.out.println("Chargement de ClasseA");
  }

  public ClasseA() {
    objet2 = new ClasseC();
  }
}
