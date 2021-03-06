import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.awt.event.ContainerEvent;
import java.awt.event.ContainerListener;
import java.awt.event.HierarchyEvent;
import java.awt.event.HierarchyListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;
import java.util.TreeSet;
import java.util.Vector;

import javax.jmdns.JmDNS;
import javax.jmdns.ServiceEvent;
import javax.jmdns.ServiceListener;
import javax.swing.BoxLayout;
import javax.swing.DefaultListModel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.JToggleButton;
import javax.swing.JTree;
import javax.swing.JViewport;
import javax.swing.ScrollPaneConstants;
import javax.swing.SpringLayout;
import javax.swing.event.EventListenerList;
import javax.swing.filechooser.FileFilter;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeSelectionModel;
import java.net.URL;

import org.jdom.Document;
import org.jdom.Element;
import org.jdom.JDOMException;
import org.jdom.input.SAXBuilder;
import org.jdom.output.Format;
import org.jdom.output.XMLOutputter;

import com.apple.eawt.Application;
import com.apple.eawt.ApplicationEvent;
import com.apple.eawt.ApplicationListener;

@SuppressWarnings("serial")

/*Class: PLMainFrame
 *Function: Called from ProxyLauncher.java - main(...) method.
 *Modified: 27/02/2006 by Siddhu
 */

public class PLMainFrame extends JFrame implements WindowListener, ServiceListener, ActionListener {

	private JList _eventHeapsList;
	private DefaultListModel _listModel;
	private DefaultListModel _runningProxiesListModel;
	private JTabbedPane _proxyTabs = new JTabbedPane();
	private ProxyTree _proxyTree;
	private JButton _startLocalEHButton;
	private JmDNS _jmdns;
	private JTree _dynamicProxyTree;
	private DefaultTreeModel _treeModel;
	private JTree proxyTree;
	private JButton _disconnectAllButton;
	private ProxyThread _localEHThread;
	private 	ProxyThread _ehLoggerThread;
    final int smallWidth = 125;
    final int medWidth = 220;
    final int largeWidth = 580;
    final int application_Min_Height = 500;
	private JFrame _displayEHBufferFrame;
	private JToggleButton _ehLogButton;
	private boolean _unsaved = false;
	private File _fileName;
	protected TreeSet _availableTabNumbers = new TreeSet();
	private final PLMainFrame _ownRefernce = this;

    protected EventListenerList _myListenerList =
		new EventListenerList();

	public PLMainFrame () {
		loadSettings();
		createMenuBar();
		buildUpWindow();
	}
	
	public void quitAllProxies() {
		for (int i = 0; i < _proxyTabs.getTabCount(); i++){
			_proxyTabs.setSelectedIndex(i);
			_disconnectAllButton.doClick();
		}
	}

	/*Method: loadSetings()
         *Function: Adds a listener to the local TCP host
         *More importantly, it also checks if the config file exists, and if it doesn't, it used to call the PreferencesDialog constructor.
         *This creates a configstarter.xml file filled in with values from the Preferences Dialog, as it was assumed that configstarter.xml
         *would be bundled with the installer. 
         *But now, instead, the installer includes all the JAR files in the lib subdirectory in Siddhu's modification to the application.
         *So a new class called CreateConfigFile will be added, the constructor of which will add the
         *default values in. However, PreferencesDialog is retained, and can be invoked using the Menu system.
         */
        
        public void loadSettings () {
		setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		addWindowListener(this);
	
		try {
			_jmdns = new JmDNS();
			_jmdns.addServiceListener("_eheap._tcp.local.", this);
		} catch (IOException e1) {
			e1.printStackTrace();
			System.out.println("There was a problem resolving the localhost");
		}
			if (ConfigDataHolder.existsConfigFile())
				buildTreeFactory ();
			else 
                        {
				new CreateConfigFile();
                                buildTreeFactory();
                        }
	}

	private void buildTreeFactory () {
                Vector <File> searchDirectories = ConfigDataHolder.getSearchDirectories();
		_proxyTree = new ProxyTree ();
		for (int i=0; i < searchDirectories.size(); i++) 
			_proxyTree.addProxyDirectory(searchDirectories.get(i));
	}

	public JTabbedPane constructProxyTree() {
		
		JTabbedPane tabbedTreePane = new JTabbedPane(JTabbedPane.LEFT);

		MouseListener ml = new MouseAdapter() {
		     public void mousePressed(MouseEvent e) {
		    	 JTree selectedTree = (JTree) e.getSource(); // The currently displayed JTree has to
		    	 // be determined.
		    	 	
		        int selRow = selectedTree.getRowForLocation(e.getX(), e.getY());
		        GridBagConstraints c = new GridBagConstraints();
				c.gridx = 0;
				c.anchor = GridBagConstraints.NORTH;
		        if(selRow != -1) {
		        		if (e.getClickCount() == 2) {
		        			// Create a new instance of that proxy 
	        				// but only if it is really a proxy (not a class)
	        				// and not the root
		        			DefaultMutableTreeNode selectedNode = (DefaultMutableTreeNode) selectedTree.getLastSelectedPathComponent();
		        			if (selectedNode != selectedTree.getModel().getRoot()){
			        			ProxyNode selectedProxyNode = (ProxyNode) selectedNode.getUserObject();
			        			if (!selectedProxyNode.hasSuccessors()){
			        				ProxyNode proxyNode;
			        				proxyNode = selectedProxyNode.clone();
			        				proxyNode.addProxyDecreaseInstanceListener(selectedProxyNode);
			        	
			        			if (_proxyTabs.getSelectedComponent() == null){
			        				// If there is no tab, create a new one
			        				createProxyTab();
			        				_proxyTabs.setTitleAt(_proxyTabs.getSelectedIndex(), proxyNode.getProxyClass());
			        			}
			        			Boolean isEHListFilled;
			        			if (_eventHeapsList.getSelectedIndex() == -1)
			        				isEHListFilled = false;
			        			else
			        				isEHListFilled = true;
			        				
			        			ProxyEntry newEntry = new ProxyEntry(proxyNode, isEHListFilled);
			        			_eventHeapsList.addListSelectionListener(newEntry);

			        			if (isEHListFilled)
			        				newEntry.setEHName(_listModel.elementAt(_eventHeapsList.getSelectedIndex()).toString());
			        			addEventHeapRemovedEventListener(newEntry);
			        			newEntry.addProxyRemovedEventListener(new ActionListener(){
									public void actionPerformed(ActionEvent arg0) {
										String proxyName = arg0.getActionCommand();
										if (arg0.getID() == 100){
											_runningProxiesListModel.addElement(proxyName);
										}
										else 
											_runningProxiesListModel.removeElement(proxyName);
									}
								});
			        			newEntry.addisSaveChangedEventListener(_ownRefernce);

			        			JScrollPane currentProxyTab = (JScrollPane) _proxyTabs.getSelectedComponent();
		        				JViewport currentPanelViewPort = (JViewport) currentProxyTab.getComponent(0);
		        				ProxyHolderPanel currentProxyHolderPanel = (ProxyHolderPanel) currentPanelViewPort.getComponent(0);
		        				System.out.println("Y value before removal: " + c.gridy);
		        				// Remove the filling label first!
		        				if (currentProxyHolderPanel.getComponentCount() > 0)
		        					currentProxyHolderPanel.remove(currentProxyHolderPanel.getComponentCount() -1);
		        				
		        				c.weighty = 0;
		        				currentProxyHolderPanel.add(newEntry,c);
		        				c.weighty=1;
		        				currentProxyHolderPanel.add(new JLabel(),c); // This filling label is needed to fill
		        				// the rest of the display area. With that method, the components are displayed top down.
		        				
			        			// Add a listener that removes the Entry again when it is not longer needed
			        			newEntry.addEntryDeletedListener (currentProxyHolderPanel);			        				
		        		
			        			_proxyTabs.updateUI();
			        			}
		        			}
		        		}
		         }
		     }
		 };
		// Traverse the custom structure and construct the JTree
		if (_proxyTree != null)
		for (Iterator<ProxyNode> kindIterator = _proxyTree.getRoot().getSuccessors()
				.iterator(); kindIterator.hasNext();) {
			ProxyNode currentKindNode = (ProxyNode) kindIterator.next();
			// Create a new branch
			//newKindNode = new DefaultMutableTreeNode(currentKindNode);
			//root.add(newKindNode); // Here a new tab is constructed
			// with a new tree. This tree gets added a Mouse Listener
			DefaultMutableTreeNode root = new DefaultMutableTreeNode (currentKindNode.getKind());
			DefaultTreeModel treeModel = new DefaultTreeModel(root);
			DefaultMutableTreeNode newKindNode;
			DefaultMutableTreeNode newClassNode;
			DefaultMutableTreeNode newProxyNode;
			proxyTree = new JTree(treeModel);
			proxyTree.setAlignmentX(Component.LEFT_ALIGNMENT);
			proxyTree.getSelectionModel().setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);

			//Expand all rows of the tree	
	
			// Now search each kind node's class nodes
			for (Iterator<ProxyNode> pClassIterator = currentKindNode
					.getSuccessors().iterator(); pClassIterator.hasNext();) {
				ProxyNode currentProxyClassNode = (ProxyNode) pClassIterator
						.next();
				// Create a new branch for each class
				newClassNode = new DefaultMutableTreeNode(currentProxyClassNode);
				root.add(newClassNode);
				for (Iterator<ProxyNode> proxyIterator = currentProxyClassNode
						.getSuccessors().iterator(); proxyIterator.hasNext();) {
					ProxyNode currentProxyNode = (ProxyNode) proxyIterator
							.next();
					// Add the proxy to the tree model
					newProxyNode = new DefaultMutableTreeNode(currentProxyNode);
					newClassNode.add(newProxyNode);
				}
			}
			for (int i = 0; i < proxyTree.getRowCount(); i++) 
				proxyTree.expandRow(i);
				
			 proxyTree.addMouseListener(ml);
			// create a new tab with the constucted JTree
			 tabbedTreePane.addTab(currentKindNode.getKind(),proxyTree);
		} // If there are more kinds, create a new tab with a new tree

		return tabbedTreePane;
	}
	
	private ImageIcon getImageIcon(String relPath){
		URL url = this.getClass().getResource(relPath);
		if (url != null) {
			return new ImageIcon(url);
		}
		return null;
	}

	public void buildUpWindow() {
		
		JPanel smartIconsTopPanel = new JPanel();
		//smartIconsTopPanel.add(new JLabel(
		//		"This space is reserved for a smarticon list or similar"));
		
		JScrollPane availableProxiesTree = new JScrollPane (constructProxyTree());

		// Creation of the panel that holds a list of found event heaps
		JPanel showEventHeaps = new JPanel(new BorderLayout());
		//showEventHeaps.setPreferredSize(new Dimension (100,200));
		showEventHeaps.add(new JLabel("Found Event Heaps:"), BorderLayout.NORTH);
		_listModel = new DefaultListModel();
		_eventHeapsList = new JList(_listModel);
		_eventHeapsList.setAlignmentX(Component.CENTER_ALIGNMENT);
		JScrollPane ehListScrollPane = new JScrollPane(_eventHeapsList);
		showEventHeaps.add(ehListScrollPane, BorderLayout.CENTER);

		// create command buttons to control proxies and the local event heap.
		
		JButton connectAllButton = new JButton("Start whole Pane");
		connectAllButton.setToolTipText("Connect all proxies displayed in the current" +
				"tab to the selected Event Heap");
		connectAllButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (!_listModel.isEmpty()){
						String selectedEventHeap = _listModel.getElementAt(
							_eventHeapsList.getSelectedIndex()).toString();
					System.out
							.println("Connecting all proxies of the current tab to "
									+ selectedEventHeap);
					// Go through the list of Buttons of the tab and connect them
					// to the selected Event Heap.
					// If some proxies are already running, disconnect them first
					if (_proxyTabs.getSelectedComponent() != null) {
						JScrollPane activeTab = (JScrollPane) _proxyTabs.getSelectedComponent();
						JViewport currentViewPort = (JViewport) activeTab.getComponent(0);
						ProxyHolderPanel proxyPanel = (ProxyHolderPanel) currentViewPort.getComponent(0);
						Component [] proxyEntryList = proxyPanel.getComponents();
					
						// Start all proxies displayed in the active tab
						if (proxyEntryList != null) 
							try {
								for (int i = 0; i < proxyEntryList.length; i++){
									ProxyEntry currentEntry = (ProxyEntry) proxyEntryList [i];
									currentEntry.stopProxy();
									currentEntry.setEHName(selectedEventHeap);
									currentEntry.startProxy();
									} 
							}catch (ClassCastException exception){
									// Just ignore it - the filling label was found
							}
					}
				}
			}
		});	// end of ActionListener class

		// Create a button to create a new tab for proxies.
		JButton createNewProxyTabButton = new JButton ("Create New Tab");
		createNewProxyTabButton.addActionListener(new ActionListener () {
			public void actionPerformed (ActionEvent e) {
				createProxyTab ();
			}
		});
		
		// Create a button to rename the current tab.
		JButton renameCurrentTabButton = new JButton ("Rename Tab");
		renameCurrentTabButton.addActionListener(new ActionListener (){
			public void actionPerformed (ActionEvent e) {
				if (_proxyTabs.getTabCount() != 0){
					String newTabName = JOptionPane.showInputDialog("New Name:",
							_proxyTabs.getTitleAt(_proxyTabs.getSelectedIndex()));
					if (newTabName != null)
						_proxyTabs.setTitleAt(_proxyTabs.getSelectedIndex(),newTabName);
				}
			}
		});
		
		// Create a button to remove the current tab.
		JButton removeCurrentTabButton = new JButton ("Remove Tab");
		removeCurrentTabButton.addActionListener(new ActionListener () {
			public void actionPerformed (ActionEvent e){	
				removeTab(_proxyTabs.getSelectedIndex());
			}
		});
		
		// Create a button to start the Event Logger
		final JButton startEHLoggerButton = new JButton("Start EH Logger");
		startEHLoggerButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (startEHLoggerButton.getText().equals("Start EH Logger"))	{
					// Construct the launch command
					String launchCommand = "java -cp iStuff.jar" 
						//+ ConfigDataHolder.getIrosLocation() 
						//+ ConfigDataHolder.getCommandSeparator() 
						+ " "
						+ "iwork.eheap2.logger.EventLogger";
					_ehLoggerThread= new ProxyThread(launchCommand,null);
					_ehLoggerThread.start();
					_ehLoggerThread.addProcessQuitEventListener(new ActionListener() {
						public void actionPerformed (ActionEvent e) {
							startEHLoggerButton.setText("Start EH Logger");
						}
					});
					startEHLoggerButton.setText ("Stop EH Logger");
				}
				else {
					_ehLoggerThread.kill();
					startEHLoggerButton.setText("Start EH Logger");
				}
			}
		});

		// Construct a button that launches the local Event Heap.
		final JTextArea textArea = new JTextArea();
		_startLocalEHButton = new JButton("Start local EH");
		_startLocalEHButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (_startLocalEHButton.getText().equals("Start local EH"))	{
					// construct the launch command
					String launchCommand = "java -classpath iStuff.jar"
		       				//+ ConfigDataHolder.getIrosLocation()
						//+ ConfigDataHolder.getCommandSeparator() 
						//+ ConfigDataHolder.getJmdnsLocation() 
						+ " "
						+ "iwork.eheap2.server.EventHeapServer";
					_localEHThread = new ProxyThread(launchCommand, null);
					_localEHThread.start();
					_localEHThread.setTextArea(textArea);
					_localEHThread.addProcessQuitEventListener(new ActionListener() {
						public void actionPerformed (ActionEvent e) {
							_startLocalEHButton.setText("Start local EH");
						}
					});
					_startLocalEHButton.setText ("Stop local EH");
				}
				else {
					_localEHThread.kill();
					_startLocalEHButton.setText("Start local EH");
				}
			}
		});
		
		// Construct a button that displays the output of the local EH
		_displayEHBufferFrame = new JFrame ("Local Event Heap Output");
		JScrollPane bufferScrollPane = new JScrollPane(textArea);
		_displayEHBufferFrame.add(bufferScrollPane);
		
		// load images from inside the jar-file (by tim)
		final ImageIcon _showLogIcon = getImageIcon("icons/notepad.gif");
		final ImageIcon _hideLogIcon = getImageIcon("icons/hideNotepad.gif");
		
		_ehLogButton = new JToggleButton (_showLogIcon);
		_ehLogButton.setToolTipText("Show the output of the local Event Heap");
		_ehLogButton.addActionListener(new ActionListener (){
			
			public void actionPerformed(ActionEvent arg0) {
				if (_displayEHBufferFrame.isVisible()){
					_displayEHBufferFrame.setVisible(false);
					_ehLogButton.setIcon(_showLogIcon);
					_ehLogButton.setToolTipText("Hide the output of the local Event Heap");
				}
				else {
					_displayEHBufferFrame.setVisible(true);
					_displayEHBufferFrame.pack();
					_ehLogButton.setIcon(_hideLogIcon);
					_ehLogButton.setToolTipText("Show the output of the local Event Heap");
				}
			}
			
		});
		_displayEHBufferFrame.addWindowListener(new WindowListener () {
			public void windowClosing(WindowEvent arg0) {
				_ehLogButton.setIcon(_showLogIcon);
				_ehLogButton.setToolTipText("Show the output of the local Event Heap");
				_ehLogButton.setSelected(false);
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

		_disconnectAllButton = new JButton("Stop All Proxies");
		_disconnectAllButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// Go through the list of Buttons of the tab and stop them
				try	{
					JScrollPane activeTab = (JScrollPane) _proxyTabs.getSelectedComponent();							
					JViewport currentViewPort = (JViewport) activeTab.getComponent(0);
					ProxyHolderPanel proxyPanel = (ProxyHolderPanel) currentViewPort.getComponent(0);
					Component [] proxyEntryList = proxyPanel.getComponents();
				
					// Stop all proxies displayed in the active tab
					if (proxyEntryList != null) 
						for (int i = 0; i < proxyEntryList.length; i++){
							Object currentEntry = proxyEntryList [i];
							if (currentEntry.getClass() == ProxyEntry.class) //if not, it was the filling label.
								((ProxyEntry) currentEntry).stopProxy();
						}
					}
				catch (NullPointerException exception) {
					// Just ignore the button press.
				}
			}
			}); 
		
		// Let the OS decide where the new window
		// appears.
		setLocationByPlatform(true);
		
		// Construct the application window with a scrollable JPanel.
		// The components are laid out wiith the help of a GridBagLayout.
		
		JPanel contentPane = new JPanel (new GridBagLayout ());
		GridBagConstraints c = new GridBagConstraints();
		
		// First row
		c.gridx = 0;
		c.gridy = 0;
		c.gridwidth = 4;
		c.weightx = 0;
		c.weighty = 0;
		c.insets = new Insets (10, 10, 0, 10);
	//	c.anchor = GridBagConstraints.NORTHWEST;
//			contentPane.add(smartIconsTopPanel, c);
	
		c.weightx = 0;
		// Second row: Labels
		c.gridwidth = 1;
		c.anchor = GridBagConstraints.CENTER;
		c.gridy = 1;
		c.weighty = 1;
		
			contentPane.add (new JLabel ("Found Event Heaps:"),c);
		c.gridx = 1;
			contentPane.add (new JLabel ("Available Proxies:"), c);
		c.gridx = 2;
		// Nothing to add
		c.gridx = 3;
		c.fill = GridBagConstraints.BOTH;
			contentPane.add (new JLabel ("Running proxies:"),c);
		
		// Third row: Scrollable Panels with different weight and fill factor
		c.gridy = 2;
		c.gridx = 0;
		c.weighty = 2;
			JPanel ehListAndControlsPanel = new JPanel();
			ehListAndControlsPanel.setPreferredSize(new Dimension(smallWidth,application_Min_Height));
			ehListAndControlsPanel.add(ehListScrollPane);
			ehListAndControlsPanel.add(connectAllButton);
			ehListScrollPane.setPreferredSize(new Dimension (smallWidth,application_Min_Height / 2 ));
			ehListAndControlsPanel.add(_startLocalEHButton);
			ehListAndControlsPanel.add(_ehLogButton);
			ehListAndControlsPanel.add(startEHLoggerButton);
			contentPane.add (ehListAndControlsPanel,c);
		c.gridx = 1;
			availableProxiesTree.setPreferredSize(new Dimension (medWidth,application_Min_Height));
			contentPane.add (availableProxiesTree,c);
		c.gridx = 2;
		c.weightx = 1;  // Additonal space should only be given to the tabbed pane.
			//c.gridheight = 2;
			_proxyTabs.setPreferredSize(new Dimension (largeWidth,application_Min_Height));
			contentPane.add (_proxyTabs,c);
		c.gridx = 3;
		c.weightx = 0;
			_runningProxiesListModel = new DefaultListModel();
			JList runningProxiesList = new JList(_runningProxiesListModel);
			JScrollPane proxyListScrollPane = new JScrollPane(runningProxiesList);
			proxyListScrollPane.setPreferredSize(new Dimension (smallWidth,application_Min_Height));
			contentPane.add(proxyListScrollPane,c);
		
		// Fourth row: Buttons - weight and fill factors back to standard
		c.gridy = 3;
		c.gridx = 0;
		c.weighty = 0;
		c.fill = GridBagConstraints.NONE;
			//contentPane.add (connectAllButton,c);
		c.gridx = 1;
		// Nothing to add
		c.gridx = 2;
			// Create a panel with three buttons.
			JPanel tabButtonsPanel = new JPanel();
			tabButtonsPanel.add (createNewProxyTabButton);
			tabButtonsPanel.add (renameCurrentTabButton);
			tabButtonsPanel.add (removeCurrentTabButton);
			// Add the panel to the framegrid.
			contentPane.add (tabButtonsPanel, c);
         c.gridx = 3;
         	contentPane.add (_disconnectAllButton,c);
		
         // Fith row - additional buttons (one at the moment)
		//c.gridy = 4;
		//c.gridx = 0;
		
		JPanel wholeContent = new JPanel(new BorderLayout ());
		wholeContent.add(smartIconsTopPanel, BorderLayout.NORTH);
		wholeContent.add(contentPane, BorderLayout.CENTER);
		JScrollPane scrollContentPane = new JScrollPane (wholeContent);
		add (scrollContentPane);
		setTitle("Untitled Composition");
		pack();
		setResizable(false);
		_startLocalEHButton.requestFocus();
		//setSize(1024,400);
		setVisible(true);
	}

	// This methods allows classes to register for MyEvents
    public void addEventHeapRemovedEventListener(ActionListener listener) {
    	_myListenerList.add(ActionListener.class, listener);
    }

	public void windowOpened(WindowEvent arg0) {
	}

	public void windowClosing(WindowEvent arg0) {
		int quitResult = JOptionPane.showConfirmDialog(_ownRefernce,"Do you really want to quit the application?");
		if (quitResult == JOptionPane.YES_OPTION) {
			boolean reallyQuit = true;
			if (_unsaved) {
				int result = JOptionPane.showConfirmDialog(null, 
					"The current composition is not saved." +
					"Do you want to save it?");
				if (result == JOptionPane.YES_OPTION) 
					if (_fileName !=null)
						writeComposition(_fileName);
					else
						writeComposition(getFileNameToWriteTo());
				else if (result == JOptionPane.CANCEL_OPTION)
					reallyQuit = false;
			}
			if (reallyQuit) {
				quitAllProxies();
				if (_startLocalEHButton.getText().equals("Stop local EH"))
					_startLocalEHButton.doClick();
				if (_ehLoggerThread != null)
					_ehLoggerThread.kill();
				System.out.println("All processes were successfully ended. \n " +
					"Have a nice day!");
				System.exit(0);
			}
		}
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

	public void serviceAdded(ServiceEvent arg0) {
		String newServiceName = arg0.getName(); 
		String localHostName;
		_listModel.addElement(newServiceName);
		try {
			localHostName = InetAddress.getLocalHost().getHostName();
		// Select the local host, if available, otherwise the first in
		// the list if nothing is selected
			if (newServiceName.equals(localHostName)){
				_eventHeapsList.setSelectedValue(localHostName,true);
			}
		}
		catch (UnknownHostException e) {
			System.out.println("The localhost name could not be retrieved." +
					"Please check your network settings");
			e.printStackTrace();
		}
		// if nothing is selected, select the first index in the list.
		if (_eventHeapsList.getSelectedIndex() == -1) {
			_eventHeapsList.setSelectedIndex(0);
		}
		// Fire an event to notify the listenening proxyEntry objects
		// that a new servic occured. Standby proxies will change
		// their status.
		FireActionEvent.fireEvent (new ActionEvent(this, 
				ActionEvent.ACTION_PERFORMED, arg0.getName()),
				_myListenerList);
	}

	public void serviceRemoved(ServiceEvent arg0) {
		int lastIndex = _eventHeapsList.getSelectedIndex();
		_listModel.removeElement(arg0.getName());

		if (!_listModel.isEmpty())
			if (lastIndex != 0)
				_eventHeapsList.setSelectedIndex(lastIndex -1);
			else
				_eventHeapsList.setSelectedIndex(0);				
		
		// Fire a custom event that contains information about
		// the removed event heap.	
		FireActionEvent.fireEvent (new ActionEvent(this, 
				ActionEvent.ACTION_PERFORMED, arg0.getName()),
				_myListenerList);
	}
	
	public void serviceResolved(ServiceEvent arg0) {
		// This method is not needed.
		// Everything is done with the serviceAdded - method
	}

	public void createProxyTab (){
		String newTabName;
		int newTabNumber = 1;
		while (_availableTabNumbers.contains(newTabNumber)) 
			newTabNumber++;
		newTabName = "ProxyTab #" + newTabNumber;
		_availableTabNumbers.add(newTabNumber);
		_proxyTabs.setSelectedIndex(_proxyTabs.getTabCount()- 1);
		ProxyHolderPanel proxyHolderPanel = new ProxyHolderPanel(new GridBagLayout(),newTabNumber);
		JScrollPane proxyTabScrollPane = new JScrollPane(proxyHolderPanel);
		proxyTabScrollPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		_proxyTabs.addTab(newTabName, proxyTabScrollPane);
		_proxyTabs.setSelectedIndex(_proxyTabs.getComponentCount() - 1);
		_proxyTabs.doLayout();
	}
	
	private void createMenuBar() {
		// Implement the dialogs and ActionListeners
	    if (System.getProperty("mrj.version") == null) {   
	       // Your are running on a non-Mac platform

	     }  else {
	    	 Application macApp = new Application();
	    	 macApp.addPreferencesMenuItem();
	    	 macApp.setEnabledPreferencesMenu(true);
	    	 macApp.addApplicationListener(new ApplicationListener () {

				public void handleAbout(ApplicationEvent arg0) {
					arg0.setHandled(true); // This avoids displayin the standard dialog.
					// TODO: Implement a metod that displays an about Window
					// for all platforms and call it from here.
					JFrame aboutMenu = new JFrame();
					aboutMenu.add(new JLabel ("Welcome To the ProxyLauncher"));
					aboutMenu.setVisible(true);
				}
				
				public void handleOpenApplication(ApplicationEvent arg0) {
				}
				
				public void handleOpenFile(ApplicationEvent arg0) {
				}
				
				public void handlePreferences(ApplicationEvent arg0) {
					new PreferencesDialog ();
				}
				
				public void handlePrintFile(ApplicationEvent arg0) {
				}
				
				public void handleQuit(ApplicationEvent arg0) {
					int quitResult = JOptionPane.showConfirmDialog(_ownRefernce,"Do you really want to quit the application?");
					if (quitResult == JOptionPane.YES_OPTION) {
						boolean reallyQuit = true;
						if (_unsaved) {
							int result = JOptionPane.showConfirmDialog(null, 
								"The current composition is not saved." +
								"Do you want to save it?");
							if (result == JOptionPane.YES_OPTION) 
								if (_fileName != null)
									writeComposition(_fileName);
								else
									writeComposition(getFileNameToWriteTo());
							else if (result == JOptionPane.CANCEL_OPTION)
								reallyQuit = false;
						}
						if (reallyQuit) {
							quitAllProxies();
							if (_startLocalEHButton.getText().equals("Stop local EH"))
								_startLocalEHButton.doClick();
							if (_ehLoggerThread != null)
								_ehLoggerThread.kill();
							System.out.println("All processes were successfully ended. \n " +
								"Have a nice day!");
							System.exit(0);
						}
					}
				}
				
				public void handleReOpenApplication(ApplicationEvent arg0) {
				}
	    	 	});	            
	     }
	

	    ActionListener selectNewFile = new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				boolean reallyNew = true;
				if (_unsaved) {
					int result = JOptionPane.showConfirmDialog(null, 
						"The current composition is not saved." +
						"Do you want to save it?");
					if (result == JOptionPane.YES_OPTION)
						if (_fileName != null)
							writeComposition(_fileName);
						else	
							writeComposition(getFileNameToWriteTo());
					else if (result == JOptionPane.CANCEL_OPTION)
						reallyNew = false;
				}
				if (reallyNew) {
					removeAllTabs();
					setTitle ("Untitled Composition");
					_unsaved = false;
					_fileName = null;
				}
			}
		};
		
		ActionListener selectOpenFile = new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				boolean reallyNew = true;
				if (_unsaved) {
					int result = JOptionPane.showConfirmDialog(null, 
						"The current composition is not saved." +
						"Do you want to save it?");
					if (result == JOptionPane.YES_OPTION)
						if (_fileName != null)
							writeComposition(_fileName);
						else	
							writeComposition(getFileNameToWriteTo());
					else if (result == JOptionPane.CANCEL_OPTION)
						reallyNew = false;
				}
				if (reallyNew) {
					//implement loader
					removeAllTabs();
					JFileChooser fileChooser = new JFileChooser ();
					fileChooser.setAcceptAllFileFilterUsed(false);
					fileChooser.setFileFilter(new CustomFileFilter("ProxyLauncher Compositions"));
					int returnVal = fileChooser.showOpenDialog(_ownRefernce);
					if (returnVal == JFileChooser.APPROVE_OPTION) {
						File fileToLoad = fileChooser.getSelectedFile();
						loadComposition (fileToLoad);
					}
				}
			}
		};
		ActionListener selectSaveFile = new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (_fileName != null) 
					writeComposition(_fileName);
				else {
					_fileName = getFileNameToWriteTo();
					writeComposition(_fileName);
				}
				_unsaved = false;
				setTitle (_fileName.getName());
			}
		};
		
		ActionListener selectSaveFileAs = new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try{
					_fileName = getFileNameToWriteTo();
					if (_fileName != null){
						writeComposition(_fileName);
						_unsaved = false;
						setTitle(_fileName.getName());
					}
				} catch (NullPointerException exception) {
					// Everything stays as it is
				}
			}
		};
		
		ActionListener selectPreferences = new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				PreferencesDialog d = new PreferencesDialog();
			}
		};
		
		// Create a menu bar
		JMenuBar applicationMenuBar = new JMenuBar();
		JMenu fileMenu = new JMenu("File");
		JMenuItem newComposition = new JMenuItem ("New Composition");
		JMenuItem loadComposition = new JMenuItem ("Open Existing Composition");
		JMenuItem saveComposition = new JMenuItem ("Save Current Composition");
		JMenuItem saveCompositionAs = new JMenuItem ("Save Current Composition As...");
		JMenuItem preferences = new JMenuItem ("Preferences");
		JMenuItem chooseDir = new JMenuItem("Import Proxy Directory...");
		
		(fileMenu.add(newComposition)).addActionListener(selectNewFile);
		(fileMenu.add(loadComposition)).addActionListener(selectOpenFile);
		fileMenu.addSeparator();
		(fileMenu.add(saveComposition)).addActionListener(selectSaveFile);
		(fileMenu.add(saveCompositionAs)).addActionListener(selectSaveFileAs);
		fileMenu.addSeparator();
		(fileMenu.add(preferences)).addActionListener(selectPreferences);

		applicationMenuBar.add(fileMenu);

		setJMenuBar(applicationMenuBar);
	}

	
	//public void searchDirectoriesDialog () {
	/*	JFileChooser chooseProxyDir = new JFileChooser();
		chooseProxyDir
				.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
		chooseProxyDir.setAcceptAllFileFilterUsed(false);
		chooseProxyDir.setFileFilter(new CustomFileFilter(null));
		int returnVal = chooseProxyDir.showDialog(null,
				"Search Directory");
		// Search the selected directory
		if (returnVal == JFileChooser.APPROVE_OPTION) {
			File searchDirectory = chooseProxyDir.getSelectedFile();
			_proxyTree.addProxyDirectory(searchDirectory, "proxy-description.xml");
			_dynamicProxyTree = constructProxyTree();// does not work anymore
			_dynamicProxyTree.updateUI();
			// Maybe leave out this functionality.
			
			//_treeModel.reload(); // Maybe possible when the data model was changed.
			updateWindow(); // better: Update Tree Model
		} 
		*/



	public void removeTab (int index) {
		
		try	{
			JScrollPane activeTab = (JScrollPane) _proxyTabs.getComponentAt(index);							
			JViewport currentViewPort = (JViewport) activeTab.getComponent(0);
			ProxyHolderPanel proxyPanel = (ProxyHolderPanel) currentViewPort.getComponent(0);
			Component [] proxyEntryList = proxyPanel.getComponents();
		
			// Stop all proxies displayed in the active tab
			if (proxyEntryList != null) 
				for (int i = 0; i < proxyEntryList.length; i++){
					Object currentEntry = proxyEntryList [i];
					if (currentEntry.getClass() == ProxyEntry.class) //if not, it was the filling label.
						((ProxyEntry) currentEntry).removeProxy();
				}
			_proxyTabs.remove(index);
			_availableTabNumbers.remove(proxyPanel.getTabNumber());
		}
		catch (Exception exception) {
			// Just ignore that. the same as checking for null pointers and index bounds
			// --> If that happens, do nothing.
		}
	}

	public void removeAllTabs () {
		while (_proxyTabs.getTabCount() != 0)
			removeTab(0);
	}
	
	private void writeComposition (File fileName) {
		System.out.println("Test FileName: "+ fileName);
		if (fileName != null){
			try {
				Element root = new Element ("Composition");
				Document compDoc = new Document(root);
				// For each Tab add an entry
				// and go through the added components
				// as long as they are Proxyentries
				
					for (int i=0; i < _proxyTabs.getTabCount(); i++) {
						try	{
						JScrollPane activeTab = (JScrollPane) _proxyTabs.getComponentAt(i);							
						JViewport currentViewPort = (JViewport) activeTab.getComponent(0);
						ProxyHolderPanel proxyPanel = (ProxyHolderPanel) currentViewPort.getComponent(0);
						Component [] proxyEntryList = proxyPanel.getComponents();
						// Save the TabName
						
						Element currentTabElement = new Element("ProxyTab");
						root.addContent(currentTabElement);
						currentTabElement.addContent((new Element("TabName")).addContent(_proxyTabs.getTitleAt(i)));
						if (proxyEntryList != null) 
							for (int j = 0; j < proxyEntryList.length; j++){
								if (proxyEntryList [j].getClass().equals(ProxyEntry.class)){
									ProxyEntry currentEntry = (ProxyEntry) proxyEntryList [j];
									ProxyNode currentProxy = currentEntry.getProxyNode();
									Element currentProxyElement = new Element("Proxy");
									currentTabElement.addContent(currentProxyElement);
									// save the ProxyNode and the ID
									currentProxyElement.addContent((new Element("ProxyClass")).addContent(currentProxy.getClassName()));
									currentProxyElement.addContent((new Element("ProxyID")).addContent(currentProxy.getProxyID()));
								}
							}
					} 	catch (Exception exception) {
						// Just ignore that. the same as checking for null pointers and index bounds
						// --> If that happens, do nothing.
						System.out.println("In exception");
						exception.printStackTrace();
						}
					}
				// Save the file
			     XMLOutputter outputter = new XMLOutputter(Format.getPrettyFormat());
			     FileWriter writer = new FileWriter(fileName);
			     outputter.output(compDoc,writer);
			    //  writer.close();
			      JOptionPane.showMessageDialog(this,"Your settings were saved.");
			      // Still needed because the tree model is not yet dynamic.
			} catch (IOException e) {
				JOptionPane.showMessageDialog(this,"There was a problem writing the config file. \n" +
						"Maybe the directory is write protected?");
			}
			// Update the window title to the fileName;
			setTitle(fileName.getName());
		}
	}
	
	private Component getMainFrame () {
		return this;
	}
	
	private File getFileNameToWriteTo () {
		System.out.println("Someone called me!");
		File saveFileName = null;
		JFileChooser chooser = new JFileChooser();
		FileFilter filter = new CustomFileFilter("ProxyLauncher Compositions");
		chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
		chooser.setAcceptAllFileFilterUsed(false);
		chooser.setFileFilter(filter);
		chooser.setDialogTitle("Save Current Composition As...");
		int returnVal = chooser.showDialog(getMainFrame(),"Save");
		if (returnVal == JFileChooser.APPROVE_OPTION) {
			String ext=null;
			saveFileName = chooser.getSelectedFile();
			String fileName = saveFileName.toString();
			int dotPlace = fileName.lastIndexOf('.');
			if (dotPlace >= 0)
				ext = fileName.substring(dotPlace+1);
			if (ext == null) {
				ext = "plc";
				saveFileName = new File(fileName.concat("." + ext));
			}
			if (saveFileName.exists()){
//				check if file has an extension other than .plc
				if (! ext.equals("plc")) {
					// Ask to add the extension
					int result = JOptionPane.showConfirmDialog(null,"Only the extension .plc is allowed." +
							"\n Should it be added to the filename?", "Add file extension", JOptionPane.YES_NO_OPTION);
					if (result == JOptionPane.YES_OPTION) 
						saveFileName = new File(fileName.concat(".plc"));
				}
				else { // The selected file is an existing plc file.
					// Ask if it should be overwritten.
					int result = JOptionPane.showConfirmDialog(null,"Overwrite the existing file?", "File already exists", JOptionPane.YES_NO_OPTION);
					if (result != JOptionPane.YES_OPTION)
						saveFileName = getFileNameToWriteTo (); // Do it all once again
				}	
			}
		}
		return saveFileName;
	}
	
	private void loadComposition (File fileName) {
		// Load the configuration file
		try {
			Document docWithConfig;
			Element xmlRoot;
			SAXBuilder builder = new SAXBuilder();
			docWithConfig = builder.build(fileName);
			xmlRoot = docWithConfig.getRootElement();
			
			// Start to restore the saved composition
			List proxyTabList = xmlRoot.getChildren("ProxyTab");
			// For each tab, create a new Tab in the pane
			// and fill it with Proxy Entries
			// and set the IDs
			for (int i=0; i < proxyTabList.size(); i++) {
				Element currentTab = (Element) proxyTabList.get(i);
				String tabName = currentTab.getChildText("TabName");
				// create the new tab
				createProxyTab();
				_proxyTabs.setTitleAt(_proxyTabs.getSelectedIndex(), tabName);
				JScrollPane currentProxyTab = (JScrollPane) _proxyTabs.getSelectedComponent();
				JViewport currentPanelViewPort = (JViewport) currentProxyTab.getComponent(0);
				ProxyHolderPanel currentProxyHolderPanel = (ProxyHolderPanel) currentPanelViewPort.getComponent(0);
				
				List proxyList = currentTab.getChildren();
				for (int j=1; j < proxyList.size(); j++){
					try {
					Element currentProxy = (Element) proxyList.get(j);
					// Construct an new Entry
					Boolean isEHListFilled;
        				if (_eventHeapsList.getSelectedIndex() == -1)
        					isEHListFilled = false;
        				else
        					isEHListFilled = true;
        				ProxyNode proxyModelNode = _proxyTree.searchNodeClass(currentProxy.getChildText("ProxyClass"));
        				ProxyNode proxyNodeToInsert = proxyModelNode.clone();
        				proxyNodeToInsert.addProxyDecreaseInstanceListener(proxyModelNode);
        				proxyNodeToInsert.setProxyID(currentProxy.getChildText("ProxyID"));
        				ProxyEntry newEntry = new ProxyEntry(proxyNodeToInsert, isEHListFilled);
        				_eventHeapsList.addListSelectionListener(newEntry);

        				if (isEHListFilled)
        				newEntry.setEHName(_listModel.elementAt(_eventHeapsList.getSelectedIndex()).toString());
        				addEventHeapRemovedEventListener(newEntry);
        				newEntry.addProxyRemovedEventListener(new ActionListener(){
        					public void actionPerformed(ActionEvent arg0) {
        						String proxyName = arg0.getActionCommand();
							if (arg0.getID() == 100){
								_runningProxiesListModel.addElement(proxyName);
							}
							else 
								_runningProxiesListModel.removeElement(proxyName);
						}
					});
        				newEntry.addisSaveChangedEventListener(_ownRefernce);
        				//****** End of construction
        				// Add all to the new panel
        				// Remove the filling label first!
        				GridBagConstraints c = new GridBagConstraints();
        				c.gridx = 0;
        				c.anchor = GridBagConstraints.NORTH;
        				if (currentProxyHolderPanel.getComponentCount() > 0)
        					currentProxyHolderPanel.remove(currentProxyHolderPanel.getComponentCount() -1);
        				c.weighty = 0;
        				currentProxyHolderPanel.add(newEntry,c);
        				c.weighty=1;
        				currentProxyHolderPanel.add(new JLabel(),c); // This filling label is needed to fill
        				// the rest of the display area. With that method, the components are displayed top down.
        				
	        			// Add a listener that removes the Entry again when it is not longer needed
	        			newEntry.addEntryDeletedListener (currentProxyHolderPanel);
					}catch (NullPointerException exception) {
						JOptionPane.showMessageDialog(this,"The composition could not properly" +
								"be reconstruce \n because some of the proxies contained were removed.");
					}
				}
			}
			_proxyTabs.updateUI();
			_unsaved = false;
		} catch (JDOMException e) {
			JOptionPane.showMessageDialog(this,"The Composition could not be restored. \n" +
					"The XML - file may be corrupt");
			System.out.println("The Composition could not be restored. \n" +
					"The XML - file may be corrupt");
		} 
		catch (IOException e) {
			System.out.println("Error while accessing the file");
		}
	}

	public void actionPerformed(ActionEvent arg0) {
		_unsaved = true;
		if (_fileName == null)
			setTitle ("Untitled Composition *");
		else
			setTitle(_fileName.getName().concat("*"));
	}
		
} // end of class

