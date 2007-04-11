import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import javax.swing.JComboBox;
import javax.swing.JTextField;

// This extended JToggleButton changes its color when activated or deactivated

@SuppressWarnings("serial")
public class ProxyToggleButton extends ColoredToggleButton implements
		ActionListener {

	private showConsoleButton _correspondingButton;

	private JComboBox _correspondingComboBox;

	private ProxyNode _correspondingProxyNode;

	private JTextField _correspondingTextField;

	private String _executablePrefix;

	public ProxyToggleButton() {
		super();
	}

	public ProxyToggleButton(Color activatedColor, Color deactivatedColor) {

		super(activatedColor, deactivatedColor);
	}

	public ProxyToggleButton(String label) {

	}

	public ProxyToggleButton(String label, Color activatedColor,
			Color deactivatedColor) {
		super(label, activatedColor, deactivatedColor);
	}

	public void actionPerformed(ActionEvent e) {
		if (!isSelected()) {
			_correspondingProxyNode.setIsRunning(false);
			setBackground(getDeactivatedColor());
			if (_correspondingButton != null)
				_correspondingButton.setSelected(false);
			_correspondingButton.setEnabled(false);
			_correspondingButton.hideBuffer();
			_correspondingProxyNode.stopProxy();
		} else {
			_correspondingProxyNode.setIsRunning(true);
			if (_correspondingButton != null)
				_correspondingButton.setEnabled(true);
			// Now start the corresponding proxy
			try {
				_correspondingProxyNode.startProxy(_correspondingComboBox
						.getSelectedItem().toString());
				_correspondingProxyNode.getCorrespondingThread().setTextArea(
						_correspondingButton.getTextArea());
			} catch (IOException e1) {
				e1.printStackTrace();
			}

		}

	}

	public Color getActivatedColor() {
		return _activatedColor;
	}

	public JComboBox getCorrespondingComboBox() {
		return _correspondingComboBox;
	}

	public JTextField getCorrespondingTextField() {
		return _correspondingTextField;
	}

	public ProxyNode getCorresponingProxyNode() {
		return _correspondingProxyNode;
	}

	public Color getDeactivatedColor() {
		return _deactivatedColor;
	}

	public String getExecutablePrefix() {
		return (_executablePrefix);
	}

	public boolean isCorrespondingProxyRunning() {
		return _correspondingProxyNode.isRunning();
	}

	public void setCorrerspondingProxyNode(ProxyNode proxyNode) {
		_correspondingProxyNode = proxyNode;
	}

	public void setCorrespondingButton(showConsoleButton cb) {
		_correspondingButton = cb;
	}

	public void setCorrespondingComboBox(JComboBox comboBox) {
		_correspondingComboBox = comboBox;
	}

	public void setCorrespondingTextField(JTextField textField) {
		_correspondingTextField = textField;
	}

	public void setExecutablePrefix(String execPrefix) {
		_executablePrefix = execPrefix;
	}

	public void startProxy(String eventHeap) throws IOException {
		if (!_correspondingProxyNode.isRunning()) {
			_correspondingProxyNode.startProxy(eventHeap);
		}

	}

} // end of class
