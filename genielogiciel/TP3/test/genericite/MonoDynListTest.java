package genericite;

import org.junit.Before;
import org.junit.Test;

public class MonoDynListTest {

	private MonoDynList mdl;
	
	@Before
	public void setUp() throws Exception {
		// TODO cr�er une liste de B
	}

	@Test
	public void testAdd_OK() {
		// TODO 
		// assertTrue("ajout d'un B dans une liste monomorphe de B", ??? );
	}
	
	@Test
	public void testAdd_NOK_up() {
		// TODO
		// assertFalse("ajout d'un A dans une liste monomorphe de B", ??? );
	}

	@Test
	public void testAdd_NOK_down() {
		// TODO
		// assertFalse("ajout d'un C dans une liste monomorphe de B", ??? );
	}

	class A {
	}

	class B extends A {
	}

	class C extends B {
	}

}