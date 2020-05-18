package ch.hsr.cpla;

import java.util.Arrays;
import java.util.List;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.Structure;
import com.sun.jna.ptr.IntByReference;


public interface CplaLib extends Library {
	CplaLib INSTANCE = (CplaLib) Native.load("cpla", CplaLib.class);

	public static class Point extends Structure implements Structure.ByValue {
		public int x, y;
		
		Point(int x, int y) {
			this.x = x;
			this.y = y;
		}
		
		@Override
		protected List<String> getFieldOrder() {
			return List.of("x", "y");
		}
	}
	
	public static class Unicorn extends Pointer {
		
		Unicorn(String name) {
			super(Pointer.nativeValue(INSTANCE.createUnicorn(name)));
		}
		
		void dispose() {
			INSTANCE.disposeUnicorn(this);
		}
		
	}
	
	Pointer createUnicorn(String name);
	
	void disposeUnicorn(Unicorn instance);
	
	void printUnicorn(Unicorn unicorn);
	
	void printPoint(Point point);
	
	void printInt(int prefix);
	
	Pointer getData(IntByReference size);
	
	void freeData(Pointer data);
}


