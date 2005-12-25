import java.awt.Color;
import java.awt.Graphics;

import javax.swing.AbstractButton;
import javax.swing.plaf.basic.BasicToggleButtonUI;

public class CustomButtonUI extends BasicToggleButtonUI{
	
	private Color _selectedColor; 

	public CustomButtonUI (Color selectedColor){
		_selectedColor = selectedColor;
	}
		
	public void paintButtonPressed (Graphics g, AbstractButton b){
		if (b.getBackground() != getSelectedColor())
			b.setBackground(getSelectedColor());
	}
	
	public Color getSelectedColor (){
		return _selectedColor;
	}
}

