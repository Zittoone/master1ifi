package genericite;

import java.util.ArrayList;

public class MonoMultiList<T> extends ArrayList<T> {

	protected Class<?> protoClass = null; // Classe du prototype
	protected boolean isMono; // isMono est vrai si la liste est monomorphe

	public MonoMultiList(T proto) { // Le prototype est fix� � la cr�ation, mais uniquement
		// par une instance, car sinon, on ne pourrait pas v�rifier que le type pass� en 
		// param�tre est un sous-type de T (impossibilit� de Java 5 car T disparait � la
		// compilation par n�cessit� de compatibilit�)
		super();
		protoClass = proto.getClass();
		add(proto);
		isMono = true;  // liste monomorphe stricte
	}
	
	public MonoMultiList() {
		super();
		isMono = false; // autorise le polymorphisme
	}
	
	public Class<?> getProtoClass() {
		return protoClass;
	}
	
	public boolean add(T t) {
		// TODO si on est mode Monomorphe, v�rifier la coh�rence avec la classe prototype
		// TODO ne pas oublier de g�rer le bool�en (vrai si l'ajout s'est bien fait)
		if(isMono){
			if(t.getClass().equals(protoClass)){
				super.add(t);
				return true;
			} else {
				return false;
			}
		} else /*if(t.getClass().isAssignableFrom(this.getClass().getTypeParameters()[0].getClass())) */{
			super.add(t);
			return true;
		}
	}
	
}
