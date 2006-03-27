import java.awt.Color;
import java.awt.GradientPaint;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JToggleButton;

// This extended JToggleButton changes its color when activated or deactivated
@SuppressWarnings("serial")
public class ColoredToggleButton extends JToggleButton implements ActionListener{

	protected Color _activatedColor;

	protected Color _deactivatedColor;

	// Standard JToggleButton with ActionListeners attached
	public ColoredToggleButton() {
		super();
		setSelected(false);
	}

	// Standard JToggleButton with ActionListeners attached
	public ColoredToggleButton(String label) {
		super(label);
		setSelected(false);
	}

	public ColoredToggleButton(Color activatedColor, Color deactivatedColor) {
		super();
		_activatedColor = activatedColor;
		_deactivatedColor = deactivatedColor;
		setSelected(false);
		// Set a new UI because of the toggle button
		setUI(new CustomButtonUI(activatedColor));
		setBackground(deactivatedColor);
		setContentAreaFilled(false);
		addActionListener(this);
	}

	public ColoredToggleButton(String label, Color activatedColor,
			Color deactivatedColor) {
		super(label);
		_activatedColor = activatedColor;
		_deactivatedColor = deactivatedColor;
		setSelected(false);
		// Set a new UI because of the toggle button
		setUI(new CustomButtonUI(activatedColor));
		setBackground(deactivatedColor);
		setContentAreaFilled(false);
		addActionListener(this);
	}

	public Color getActivatedColor() {
		return _activatedColor;
	}

	public Color getDeactivatedColor() {
		return _deactivatedColor;
	}

	// Overloaded in order to paint the background
	protected void paintComponent(Graphics g) {
		Graphics2D g2 = (Graphics2D) g;
		g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
				RenderingHints.VALUE_ANTIALIAS_ON);
		int w = getWidth();
		int h = getHeight();
		GradientPaint gradient = new GradientPaint(20, 10, Color.WHITE, 20, h,
				getBackground(), true);
		g2.setPaint(gradient);
		g2.fillRoundRect(0, 0, w, h, 10,10);
		super.paintComponent(g);
	}

	public void actionPerformed(ActionEvent arg0) {
		if (!isSelected())
			setBackground(getDeactivatedColor());
		
	}

} // of class
