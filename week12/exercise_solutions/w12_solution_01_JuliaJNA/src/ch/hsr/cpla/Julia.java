package ch.hsr.cpla;

import java.util.Arrays;
import java.util.List;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.Structure;
import com.sun.jna.ptr.IntByReference;

public interface Julia extends Library {
	Julia INSTANCE = (Julia) Native.load("julia", Julia.class);

	public static class Window extends Structure implements Structure.ByValue {
		public double x, y, size;

		public Window(double x, double y, double size) {
			this.x = x;
			this.y = y;
			this.size = size;
		}

		@Override
		protected List<String> getFieldOrder() {
			return Arrays.asList(new String[] { "x", "y", "size" });
		}
	}

	public static class Image extends Pointer {
		public Image(int size) {
			super(Pointer.nativeValue(INSTANCE.createImage(size)));
		}

		public void dispose() {
			INSTANCE.disposeImage(this);
		}

		public int getSize() {
			return INSTANCE.getSize(this);
		}

		public byte[] getBitmapData() {
			IntByReference size = new IntByReference();
			Pointer dumped = INSTANCE.dump(this, size);
			byte[] data = dumped.getByteArray(0, size.getValue());
			Native.free(Pointer.nativeValue(dumped));
			return data;
		}
	}

	Pointer createImage(int size);

	void disposeImage(Image image);

	int getSize(Image image);

	Pointer dump(Image image, IntByReference size);

	void render(Image image, Window window, double exponent, double kReal, double kImaginary, int iterations);
}
