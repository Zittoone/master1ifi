package genericite;

import java.util.ArrayList;

public class MonoDynList extends ArrayList<Object> {

	protected Class protoClass;

	public MonoDynList(Class protoClass) {
		super();
		this.protoClass = protoClass;
		
	}
	
	public MonoDynList(Object proto) {
		super();
		this.protoClass = proto.getClass();
		this.add(proto);
	}
	
	public Class getProtoClass() {
		return protoClass;
	}
	
	public boolean add(Object t) {

		if(t.getClass().equals(protoClass)){
			super.add(t);
			return true;
		}

		return false;
	}

}
