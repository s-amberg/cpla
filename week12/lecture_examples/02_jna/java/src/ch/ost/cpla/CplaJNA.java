package ch.ost.cpla;

import com.sun.jna.Pointer;
import com.sun.jna.ptr.IntByReference;

public class CplaJNA {

	public static void main(String[] args) {
		CplaLib.Point p = new CplaLib.Point(12, 90);
		CplaLib.INSTANCE.printPoint(p);
		
		CplaLib.Unicorn u = new CplaLib.Unicorn("freddy");
		CplaLib.INSTANCE.printUnicorn(u);
		u.dispose();
		
		IntByReference size = new IntByReference(); 
		Pointer data = CplaLib.INSTANCE.getData(size);
		byte[] javaData = data.getByteArray(0, size.getValue());
		CplaLib.INSTANCE.freeData(data);
		for(byte b : javaData) {
			System.out.println(b);
		}		
	}

}
