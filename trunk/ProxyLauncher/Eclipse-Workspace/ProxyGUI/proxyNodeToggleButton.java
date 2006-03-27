import java.awt.Color;
import java.awt.event.ActionEvent;
import java.io.IOException;

import javax.swing.JComboBox;
import javax.swing.JTextField;

@SuppressWarnings("serial")

// This class extends the ColoredToggleButton class by
// setting corresponding nodes in a Proxytree and corresponding Combo Boxes
// and another button.
public class proxyNodeToggleButton extends ColoredToggleButton {
	
	private showConsoleButton _correspondingButton;
	private JComboBox _correspondingComboBox;
	private JTextField _correspondingTextField;
	private ProxyNode _correspondingProxyNode;
	private String _executablePrefix;
	

	public proxyNodeToggleButton(String label, Color activatedColor, Color deactivatedColor) {
		super (label, activatedColor, deactivatedColor);
	}

	public void actionPerformed(ActionEvent e) {
		if (!isSelected())
		{
			_correspondingProxyNode.setIsRunning(false);
			setBackground(getDeactivatedColor());
			if (_correspondingButton != null)
				_correspondingButton.setSelected(false);
				_correspondingButton.setEnabled(false);
				_correspondingButton.hideBuffer();
				_correspondingProxyNode.stopProxy();
		}
		else
		{
			_correspondingProxyNode.setIsRunning(true);
			if (_correspondingButton != null)
				_correspondingButton.setEnabled(true);
			// Now start the corresponding proxy
			try {
				_correspondingProxyNode.startProxy(_correspondingComboBox.getSelectedItem().toString());
				_correspondingProxyNode.getCorrespondingThread().setTextArea(_correspondingButton.getTextArea());
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		}
	}
	
	public ProxyNode getCorresponingProxyNode (){
		return _correspondingProxyNode;
	}
	
	public void setCorrespondingButton (showConsoleButton cb){
		_correspondingButton = cb;
	}
	
	public showConsoleButton getCorrespondingButton (){
		return _correspondingButton;
	}
	
	public void setCorrespondingComboBox (JComboBox comboBox) {
		_correspondingComboBox = comboBox;
	}
	
	public JComboBox getCorrespondingComboBox(){
		return _correspondingComboBox;
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
			_correspondingProxyNode.startProxy(eventHeap);
		}
	}
	
	public boolean isCorrespondingProxyRunning(){
		return _correspondingProxyNode.isRunning();
	}
	
    public void setCorrespondingTextField (JTextField textField){
    	_correspondingTextField = textField;
    }
    
    public JTextField getCorrespondingTextField (){
    	return _correspondingTextField;
    }
    
} // of class
