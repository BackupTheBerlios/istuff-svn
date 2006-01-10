import java.awt.Color;
import java.awt.GradientPaint;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

import javax.swing.JComboBox;
import javax.swing.JToggleButton;

// This extended JToggleButton changes its color when activated or deactivated
@SuppressWarnings("serial")
public class ChangeColorButton extends JToggleButton implements ActionListener{

	private Color _activatedColor;
	private Color _deactivatedColor;
	private JToggleButton _correspondingButton;
	private JComboBox _correspondingComboBox;
	private ProxyNode _correspondingProxyNode;
	private String _executablePrefix;

	// Standard JToggleButton with ActionListeners atteched 
	public ChangeColorButton () {
		super();
		setSelected(false);
		addActionListener(this);
	}
	
	// Standard JToggleButton with ActionListeners atteched
	public ChangeColorButton (String label) {
		super(label);
		setSelected(false);
		addActionListener(this);
	}
	
	public ChangeColorButton (Color activatedColor, Color deactivatedColor){
		super();
		_activatedColor = activatedColor;
		_deactivatedColor = deactivatedColor;
		setSelected(false);
		// Set a new UI because of the toggle button
		setUI(new CustomButtonUI(activatedColor));
		setBackground(deactivatedColor);
		addActionListener(this);
        setContentAreaFilled(false);
	}
	
	public ChangeColorButton (String label, Color activatedColor, Color deactivatedColor){
		super(label);
		_activatedColor = activatedColor;
		_deactivatedColor = deactivatedColor;
		setSelected(false);
		// Set a new UI because of the toggle button 
		setUI(new CustomButtonUI(activatedColor));
		setBackground(deactivatedColor);
		addActionListener(this);
        setContentAreaFilled(false);
	}
	
	public void actionPerformed(ActionEvent e) {
		if (!isSelected())
		{
			_correspondingProxyNode.setIsRunning(false);
			setBackground(getDeactivatedColor());
			if (_correspondingButton != null)
				_correspondingButton.setSelected(false);
				_correspondingButton.setEnabled(false);
		}
		else
		{
			_correspondingProxyNode.setIsRunning(true);
			if (_correspondingButton != null)
				_correspondingButton.setEnabled(true);
			// Now start the corresponding proxy
			try {
				System.out.println("BIS HIER");
				_correspondingProxyNode.startProxy("HALLO");
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		}
	}
	
	public Color getActivatedColor (){
		return _activatedColor;
	}
	
	public Color getDeactivatedColor (){
		return _deactivatedColor;
	}
	
	public ProxyNode getCorresponingProxyNode (){
		return _correspondingProxyNode;
	}
	
	public void setCorrespondingButton (JToggleButton cb){
		_correspondingButton = cb;
	}
	
	public void setCorrespondingComboBox (JComboBox comboBox) {
		_correspondingComboBox = comboBox;
	}

	public void setExecutablePrefix (String execPrefix) {
		_executablePrefix = execPrefix;
	}
	
	public String getExecutablePrefix (){
		return (_executablePrefix);
	}
	
	public void setCorrerspondingProxyNode (ProxyNode proxyNode){
		_correspondingProxyNode = proxyNode;
	}
	
	public void startProxy(String eventHeap) throws IOException{
		if (!_correspondingProxyNode.isRunning())
		{
			//_correspondingComboBox.setSelectedItem(eventHeap);
			_correspondingProxyNode.startProxy(eventHeap);
			//_correspondingProxyNode.setIsRunning(true);
			//doClick();		
		}
	}
	
	public boolean isCorrespondingProxyRunning(){
		return _correspondingProxyNode.isRunning();
	}

    // Overloaded in order to paint the background
    protected void paintComponent(Graphics g) {
        Graphics2D g2 = (Graphics2D) g;
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                            RenderingHints.VALUE_ANTIALIAS_ON);
        int w = getWidth();
        int h = getHeight();
        GradientPaint gradient = new GradientPaint(20, 0, Color.WHITE, 20, h, getBackground(), true);
        g2.setPaint(gradient);
        g2.fillRect(0, 0, w, h);
        super.paintComponent(g);
    }
    
}
 