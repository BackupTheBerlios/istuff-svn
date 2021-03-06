import java.awt.AWTEvent;
import java.awt.Dimension;
import java.awt.Event;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.awt.event.HierarchyEvent;
import java.awt.event.HierarchyListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.awt.event.WindowStateListener;
import java.io.IOException;

import javax.swing.DefaultListModel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.JToggleButton;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.event.EventListenerList;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.net.URL;

//import com.apple.component.Component;

public class ProxyEntry extends JPanel implements ListSelectionListener, HierarchyListener, ActionListener {
	
	private ProxyNode _proxy;
	private JLabel _proxyNameLabel;
	private JTextField _proxyIDTextField;
	private PossibleStates _proxyStatus;
	private JButton _connectionButton;
	private JToggleButton _proxyLog;
	private JButton _removeProxyButton;
	private enum PossibleStates {
			CONNECTED,
			STANDBY,
			DISCONNECTED
		}
	private String _currentEventHeapName;
	private String _eventHeapToConnectTo;
	private JFrame _displayBufferFrame;
	private JTextArea _textArea;
	private JLabel _statusLabel;
	private ImageIcon _stopped;
	private ImageIcon _standby;
	private ImageIcon _running;
	private ImageIcon _showLogIcon;
	private ImageIcon _hideLogIcon;
	private Boolean _eventHeapsAvailable;
	private ProxyEntry _ownReference;
	
    // Create the a custom EventListener list
    protected EventListenerList _myListenerList =
    		new EventListenerList();
    protected EventListenerList _entryDeletedListenerList =
		new EventListenerList();
    protected EventListenerList _isSavedListenerList =
		new EventListenerList();
	
	private ImageIcon getImageIcon(String relPath){
		URL url = this.getClass().getResource(relPath);
		if (url != null) {
			return new ImageIcon(url);
		}
		return null;
	}
	
	
	ProxyEntry (ProxyNode proxy, Boolean activate){
		Dimension preferredSize = new Dimension(150,25);
		addHierarchyListener(this);
		_proxy = proxy;
		_ownReference = this;
		_stopped = getImageIcon("icons/manStop.gif");
		_standby = getImageIcon("icons/manSuspend.gif");
		_running = getImageIcon("icons/manRunning.gif");
		_showLogIcon = getImageIcon("icons/notepad.gif");
		_hideLogIcon = getImageIcon("icons/hideNotepad.gif");
		_statusLabel = new JLabel(_stopped);
		_statusLabel.setToolTipText("The " + proxy.getName() +
				" is currently not running");
		
		// Construction of the different elemets.
		_proxyNameLabel = new JLabel (proxy.getName());
		_proxyNameLabel.setPreferredSize(preferredSize);
		_proxyNameLabel.setHorizontalAlignment(JLabel.CENTER);
		_proxyIDTextField = new JTextField(_proxy.getProxyID());
		_proxyIDTextField.addFocusListener(new FocusListener() {
			// Make sure to update the proxy's ID when it was changed
			// The update is needed when another UI element is clicked. -->FocusLost
			public void focusGained(FocusEvent e) {
				//Nothing happens
				}
			
			public void focusLost(FocusEvent e) {
				JTextField textfield = (JTextField) e.getSource();
				String stringWithoutSpaces = ((JTextField)e.getSource()).getText();
				stringWithoutSpaces = stringWithoutSpaces.replaceAll(" ","_");
				_proxy.setProxyID(textfield.getText());
				((JTextField) e.getSource()).setText(stringWithoutSpaces);
				System.out.println(_proxyIDTextField.getText());
				FireActionEvent.fireEvent(new ActionEvent(this,ActionEvent.ACTION_PERFORMED,
						"TextFieldChanged"),_isSavedListenerList);
			}
		});
		_proxyIDTextField.setPreferredSize(preferredSize);

		// Console Button Construction:
		_displayBufferFrame = new JFrame (proxy.getName() +" Output");
		_textArea = new JTextArea();
		JScrollPane bufferScrollPane = new JScrollPane(_textArea);
		_displayBufferFrame.add(bufferScrollPane);
		_proxyLog = new JToggleButton (_showLogIcon);
		_proxyLog.setToolTipText("Show the output of the " + _proxy.getName() + 
				" proxy.");
		_proxyLog.addActionListener(new ActionListener (){
			public void actionPerformed(ActionEvent arg0) {
				if (_displayBufferFrame.isVisible()){
					_displayBufferFrame.setVisible(false);
					_proxyLog.setIcon(_showLogIcon);
					_proxyLog.setToolTipText("Hide the output of the " +
							_proxy.getName() + " proxy.");
				}
				else {
					_displayBufferFrame.setVisible(true);
					_displayBufferFrame.pack();
					_proxyLog.setIcon(_hideLogIcon);
					_proxyLog.setToolTipText("Show the output of the " + 
							_proxy.getName() + " proxy.");
				}
			}
		});
		_displayBufferFrame.addWindowListener(new WindowListener () {
		public void windowClosing(WindowEvent arg0) {
			_proxyLog.setSelected(false);
			_proxyLog.setIcon(_showLogIcon);
			_proxyLog.setToolTipText("Show the output of the local Event Heap");
			}
			public void windowOpened(WindowEvent arg0) {
			}
			public void windowClosed(WindowEvent arg0) {
			}
			public void windowIconified(WindowEvent arg0) {
			}
			public void windowDeiconified(WindowEvent arg0) {
			}
			public void windowActivated(WindowEvent arg0) {
			}
			public void windowDeactivated(WindowEvent arg0) {
			}
		});
	
		_proxyStatus = PossibleStates.DISCONNECTED;
		_connectionButton = new JButton ("Start");
		_connectionButton.setEnabled(activate);
		_eventHeapsAvailable = activate;
		_connectionButton.addActionListener(new ActionListener(){

			public void actionPerformed(ActionEvent arg0) {
				// Check wether the proxy is already connected or not
				if (_proxyStatus.equals(PossibleStates.DISCONNECTED))
					startProxy();
				else {
					stopProxy();
					if (!_eventHeapsAvailable)
						_connectionButton.setEnabled(false);
				}
			}
		});
		
		// Create a button to remove the proxy from the workspace again.
		_removeProxyButton = new JButton (getImageIcon("icons/trashcan.jpg"));
		_removeProxyButton.setToolTipText("Remove this proxy from the list and stop it");
		_removeProxyButton.addActionListener(new ActionListener () {
			public void actionPerformed (ActionEvent e){
				removeProxy();
			}
		});
		
		// construct the Panel by adding its components
		add (_statusLabel);
		add (_proxyNameLabel);
		add (_proxyIDTextField);
		add (_connectionButton);
		add (_proxyLog);
		add (_removeProxyButton);
		}
	
	public void valueChanged(ListSelectionEvent arg0) {
		JList eventHeapList = (JList) arg0.getSource();
		DefaultListModel listModel = (DefaultListModel) eventHeapList.getModel();
		int listIndex = eventHeapList.getSelectedIndex();
		if (listIndex != -1){
			_eventHeapToConnectTo = listModel.getElementAt(listIndex).toString();
			_connectionButton.setEnabled(true);
			_eventHeapsAvailable = true;
		}
		else {
			if (_proxyStatus != PossibleStates.STANDBY){
			_connectionButton.setEnabled(false);
			_eventHeapsAvailable = false;
			}
		}	
	}
	
	public void stopProxy (){
		_proxy.stopProxy();
		setStatusDisconnected();
		FireActionEvent.fireEvent (new ActionEvent(this, 101, 
				_proxy.getProxyID()), _myListenerList);
	}
	
	public void startProxy (){
		if (_eventHeapToConnectTo != null) {
			try {
				_currentEventHeapName = _eventHeapToConnectTo;
				_proxy.startProxy(_currentEventHeapName);
				_proxy.getCorrespondingThread().setTextArea(_textArea);
				setStatusConnected();
				// Add a listener to the proxy thread in order to change the button status.
				_proxy.getCorrespondingThread().addProcessQuitEventListener(new ActionListener(){
					public void actionPerformed(ActionEvent arg0) {
						stopProxy();
					}
				});
				// fire an event that a new proxy is running.100 means here that a proxy should be added
				FireActionEvent.fireEvent (new ActionEvent(this, 100, 
						_proxy.getProxyID()), _myListenerList);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	public void removeProxy () {
		stopProxy();
		// fire an event that this proxy should be removed
		FireActionEvent.fireEvent (new ActionEvent(_ownReference, ActionEvent.ACTION_PERFORMED, 
				"Remove proxy Entry"), _entryDeletedListenerList);
	}
		
	private void setStatusConnected () {
		_proxy.setProxyID(_proxyIDTextField.getText());
		_proxyStatus = PossibleStates.CONNECTED;
		_statusLabel.setIcon(_running);
		_statusLabel.setToolTipText("The " + _proxy.getName() + 
				" is running.");
		_proxyIDTextField.setEnabled(false);
		_connectionButton.setText("Stop");
	}
	
	private void setStatusDisconnected () {
		_proxyStatus = PossibleStates.DISCONNECTED;
		_statusLabel.setIcon(_stopped);
		_statusLabel.setToolTipText("The " + _proxy.getName() + 
				" is currently not running");
		_proxyIDTextField.setEnabled(true);
		_connectionButton.setText("Start");
	}
	
	private void setStatusStandy () {
		_proxyStatus = PossibleStates.STANDBY;
		_connectionButton.setEnabled(true);
		_statusLabel.setIcon(_standby);
		_statusLabel.setToolTipText("The " + _proxy.getName() + 
				"proxy is in Standby-Mode. It will reconnect automatically");
	}
	
    // This method allows other classes to register for MyEvents
    public void addProxyRemovedEventListener(ActionListener listener) {
    		_myListenerList.add(ActionListener.class, listener);
    }
    
    public void addisSaveChangedEventListener(ActionListener listener) {
		_isSavedListenerList.add(ActionListener.class, listener);
}

	public void actionPerformed(ActionEvent arg0) {
		if( (_proxyStatus.equals(PossibleStates.CONNECTED)) 
				&& (_currentEventHeapName.equals(arg0.getActionCommand())) ) {
			setStatusStandy();
			System.out.println("StatusStandby");
		}
		else if( (_proxyStatus.equals(PossibleStates.STANDBY)) 
				&& (_currentEventHeapName.equals(arg0.getActionCommand())) ) { 
			// wer are in standby --> EH recoverd --> thread is connected again.
			setStatusConnected();
		}		
	}
	
	public void setEHName (String newName) {
		_eventHeapToConnectTo = newName;
	}
	
	public void addEntryDeletedListener (ActionListener listener) {
		_entryDeletedListenerList.add(ActionListener.class, listener);
	}
	
	public ProxyNode getProxyNode (){
		return _proxy;
	}

	public void hierarchyChanged(HierarchyEvent arg0) {
		// Fire an event to the listeners
		// Because also the JTextfields send events, they are grouped
		// here and the objects in the listener list below are notified.
		FireActionEvent.fireEvent(new ActionEvent(this,ActionEvent.ACTION_PERFORMED,
		"TextFieldChanged"),_isSavedListenerList);
	}

}// end of class
