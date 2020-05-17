package ch.hsr.cpla;

import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import ch.hsr.cpla.Julia.Image;

public class JuliaJNA {

	static ImageViewer imageViewer;

	public static void main(String[] args) {
		SwingUtilities.invokeLater(() -> {
			imageViewer = new ImageViewer(500);
			imageViewer.setVisible(true);
		});
	}

	public static class ImageViewer extends JFrame {
		private static final long serialVersionUID = -9127187659667855390L;

		public ImageViewer(int size) {
			this.setTitle("CplA Image Viewer");
			this.setSize(size, size);
			this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

			Image image = new Julia.Image(size);
			Julia.INSTANCE.render(image, new Julia.Window(0.0, 0.0, 1.0), 2.0, 0.0, -1.0, 100);
			byte[] rendered = image.getBitmapData();
			image.dispose();

			BufferedImage bitmap = null;
			try {
				bitmap = ImageIO.read(new ByteArrayInputStream(rendered));
			} catch (IOException e) {
				e.printStackTrace();
			}

			JPanel panel = new JPanel();

			if (image != null) {
				JLabel imageView = new JLabel(new ImageIcon(bitmap));
				panel.add(imageView);
			}

			this.add(panel);
		}
	}
}
