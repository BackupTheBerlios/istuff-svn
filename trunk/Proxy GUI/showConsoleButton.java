import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JComboBox;
import javax.swing.JToggleButton;

@SuppressWarnings("serial")
public class showConsoleButton extends JToggleButton implements ActionListener{
	
	private JToggleButton _correspondingButton;
	private JComboBox _correpsondingComboBox;
	private String _execPrefix;
	
	public showConsoleButton (JToggleButton b, String label){
		super(label);
		_correspondingButton = b;
		addActionListener(this);
		setEnabled(false);		
	}

	public void actionPerformed(ActionEvent e) {
		// TODO Here the proxy should be launched!
		if (_correpsondingComboBox != null)
		System.out.println(_correpsondingComboBox.getSelectedItem());	
		System.out.println("ALIVE!");
	}

	public void setCorrespondingCombox (JComboBox comboBox) {
		_correpsondingComboBox = comboBox;
	}

	public void setExecutablePrefix (String execPrefix){
		_execPrefix = execPrefix;		
	}
}

