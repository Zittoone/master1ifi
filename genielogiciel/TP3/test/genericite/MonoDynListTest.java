package genericite;

import org.junit.Before;
import org.junit.Test;

import static junit.framework.TestCase.assertEquals;

public class MonoDynListTest {

	private MonoDynList mdl;
	
	@Before
	public void setUp() throws Exception {
		mdl = new MonoDynList(new B());
	}

	@Test
	public void testAdd_OK() {
		// TODO 
		// assertTrue("ajout d'un B dans une liste monomorphe de B", ??? );
		assertEquals(true, mdl.add(new B()));
	}
	
	@Test
	public void testAdd_NOK_up() {
		// TODO
		// assertFalse("ajout d'un A dans une liste monomorphe de B", ??? );
		assertEquals(false, mdl.add(new A()));
	}

	@Test
	public void testAdd_NOK_down() {
		// TODO
		// assertFalse("ajout d'un C dans une liste monomorphe de B", ??? );
		assertEquals(false, mdl.add(new C()));
	}

	class A {
	}

	class B extends A {
	}

	class C extends B {
	}

}