import java.awt.Component;
import java.awt.Dimension;
import java.awt.Rectangle;

import javax.swing.JScrollPane;
import javax.swing.Scrollable;

public class CustomScrollPane  extends JScrollPane implements Scrollable{
	
	public CustomScrollPane (Component c) {
		super (c);
	}
	
	public boolean getScrollableTracksViewportWidth () {
		return true;
	}

	public Dimension getPreferredScrollableViewportSize() {
		// TODO Auto-generated method stub
		return (new Dimension (400,200));
	}

	public int getScrollableUnitIncrement(Rectangle arg0, int arg1, int arg2) {
		// TODO Auto-generated method stub
		return 100;
	}

	public int getScrollableBlockIncrement(Rectangle arg0, int arg1, int arg2) {
		// TODO Auto-generated method stub
		return 100;
	}

	public boolean getScrollableTracksViewportHeight() {
		// TODO Auto-generated method stub
		return true;
	}

	
}
