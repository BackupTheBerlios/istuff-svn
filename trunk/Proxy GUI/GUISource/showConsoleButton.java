import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JTextArea;
import javax.swing.JToggleButton;

@SuppressWarnings("serial")
public class showConsoleButton extends JToggleButton implements ActionListener{
	
	private JToggleButton _correspondingButton;
	private JComboBox _correpsondingComboBox;
	private JTextArea _textArea;
	private JFrame _displayBuffer;
	private boolean _isEnabled;

	public showConsoleButton (JToggleButton b, String label){
		super(label);
		_correspondingButton = b;
		addActionListener(this);
		setEnabled(false);	
		_displayBuffer = new JFrame ("Proxy Output");
		_textArea = new JTextArea();
		_displayBuffer.add(_textArea);
		_isEnabled = false;
	}

	public void actionPerformed(ActionEvent e) {
		if (!_isEnabled){
			_isEnabled = true;
			_displayBuffer.pack();
			_displayBuffer.setVisible(true);	
		}
		else
		{
			_isEnabled = false;
			hideBuffer();
		}
	}

	public void setCorrespondingCombox (JComboBox comboBox) {
		_correpsondingComboBox = comboBox;
	}
	
	public JComboBox getCorrespondingComboBox(){
		return _correpsondingComboBox;
	}
	
	public JToggleButton getCorrespondingButton(){
		return _correspondingButton;
	}
	
	public void setCorrespondingButton (JToggleButton button){
		_correspondingButton = button;
	}
	public JTextArea getTextArea (){
		return _textArea;
	}
	
	public void hideBuffer(){
		_isEnabled = false;
		_displayBuffer.setVisible(false);
	}
	
}

