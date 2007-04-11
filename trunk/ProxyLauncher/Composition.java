import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Image;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.io.File;
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

import org.jdom.Document;
import org.jdom.Element;
import org.jdom.JDOMException;
import org.jdom.input.SAXBuilder;

import com.apple.eawt.Application;
import com.apple.eawt.ApplicationEvent;
import com.apple.eawt.ApplicationListener;
// Maybe this class can be used for future purpose in order to create several 
// composition windows...
@SuppressWarnings("serial")
public class Composition extends JFrame implements WindowListener, ServiceListener {

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
	private ConfigDataHolder _dataHolder;
	protected TreeSet _availableTabNumbers = new TreeSet();

    protected EventListenerList _myListenerList =
		new EventListenerList();

	public Composition() {
		setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		loadSettings();
		buildUpWindow();
	}
	
	public void quitAllProxies() {
		for (int i = 0; i < _proxyTabs.getTabCount(); i++){
			_proxyTabs.setSelectedIndex(i);
			_disconnectAllButton.doClick();
		}
	}

	public void loadSettings () {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		addWindowListener(this);
	
		try {
			_jmdns = new JmDNS();
			_jmdns.addServiceListener("_eheap._tcp.local.", this);
		} catch (IOException e1) {
			e1.printStackTrace();
			System.out.println("There was a problem resolving the localhost");
		}
		
		Vector <File> searchDirectories = ConfigDataHolder.getSearchDirectories();
		System.out.println(searchDirectories);
	
		_proxyTree = new ProxyTree ();
		for (int i=0; i < searchDirectories.size(); i++) 
			_proxyTree.addProxyDirectory(searchDirectories.get(i));
	}


	public JTree constructProxyTree() {
		
		DefaultMutableTreeNode root = new DefaultMutableTreeNode ("Proxies");
		DefaultTreeModel treeModel = new DefaultTreeModel(root);
		DefaultMutableTreeNode newKindNode;
		DefaultMutableTreeNode newClassNode;
		DefaultMutableTreeNode newProxyNode;

		// Traverse the custom structure and construct the JTree
		if (_proxyTree != null)
		for (Iterator<ProxyNode> kindIterator = _proxyTree.getRoot().getSuccessors()
				.iterator(); kindIterator.hasNext();) {
			ProxyNode currentKindNode = (ProxyNode) kindIterator.next();
			// Create a new branch
			newKindNode = new DefaultMutableTreeNode(currentKindNode);
			root.add(newKindNode);
			
			// Now search each kind node's class nodes
			for (Iterator<ProxyNode> pClassIterator = currentKindNode
					.getSuccessors().iterator(); pClassIterator.hasNext();) {
				ProxyNode currentProxyClassNode = (ProxyNode) pClassIterator
						.next();
				// Create a new branch for each class
				newClassNode = new DefaultMutableTreeNode(currentProxyClassNode);
				newKindNode.add(newClassNode);
				for (Iterator<ProxyNode> proxyIterator = currentProxyClassNode
						.getSuccessors().iterator(); proxyIterator.hasNext();) {
					ProxyNode currentProxyNode = (ProxyNode) proxyIterator
							.next();
					// Add the proxy to the tree model
					newProxyNode = new DefaultMutableTreeNode(currentProxyNode);
					newClassNode.add(newProxyNode);
				}
			}
		}

		// TODO: Think about a splitted pane
		// Divide HW and SW proxies
		// Generate two trees for two views.
		// TODO: If no way to dynamically change the tree view
		// Leave it statically;

		proxyTree = new JTree(treeModel);
		proxyTree.setAlignmentX(Component.LEFT_ALIGNMENT);
		proxyTree.getSelectionModel().setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);
		MouseListener ml = new MouseAdapter() {
		     public void mousePressed(MouseEvent e) {
		        int selRow = proxyTree.getRowForLocation(e.getX(), e.getY());
		        GridBagConstraints c = new GridBagConstraints();

		        if(selRow != -1) {
		        		if (e.getClickCount() == 2) {
		        			// Create a new instance of that proxy 
	        				// but only if it is really a proxy (not a class)
	        				// and not the root
		        			DefaultMutableTreeNode selectedNode = (DefaultMutableTreeNode) proxyTree.getLastSelectedPathComponent();
		        			if (selectedNode != proxyTree.getModel().getRoot()){
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
			        			JScrollPane currentProxyTab = (JScrollPane) _proxyTabs.getSelectedComponent();
		        				JViewport currentPanelViewPort = (JViewport) currentProxyTab.getComponent(0);
		        				ProxyHolderPanel currentProxyHolderPanel = (ProxyHolderPanel) currentPanelViewPort.getComponent(0);
		        				
		        				// Remove the filling label first!
		        				c.gridy = currentProxyHolderPanel.getComponentCount();
		        				if (c.gridy !=0)
		        				currentProxyHolderPanel.remove(currentProxyHolderPanel.getComponentCount() -1);
		        				c.anchor = GridBagConstraints.NORTHWEST;
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
		 proxyTree.addMouseListener(ml);
		//Expand all rows of the tree	
		for (int i = 0; i < proxyTree.getRowCount(); i++) {
				proxyTree.expandRow(i);
		}
		return proxyTree;
	}

	public void buildUpWindow() {
		
		JPanel smartIconsTopPanel = new JPanel();
		smartIconsTopPanel.add(new JLabel(
				"This space is reserved for a smarticon list or similar"));
		
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
					String launchCommand = "java -cp " 
						+ ConfigDataHolder.getIrosLocation() 
						+ ConfigDataHolder.getCommandSeparator() 
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
					String launchCommand = "java -cp " + ConfigDataHolder.getIrosLocation()
						+ ConfigDataHolder.getCommandSeparator() 
						+ ConfigDataHolder.getJmdnsLocation() 
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
		final ImageIcon _showLogIcon = new ImageIcon ("icons/notepad.gif");
		final ImageIcon _hideLogIcon = new ImageIcon ("icons/hideNotepad.gif");
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
		pack();
		setResizable(false);
		_startLocalEHButton.requestFocus();
		//setSize(1024,400);
		setVisible(true);
	}

	public void updateWindow() {
		Dimension buttonDimension = new Dimension(140, 25);
		GridBagConstraints c = new GridBagConstraints();
		GridBagLayout tabLayout = new GridBagLayout();
/*
		for (Iterator<ProxyNode> classIt = _proxyTree.getTreeRoot()
				.getSuccessors().iterator(); classIt.hasNext();) {
			ProxyNode kind = (ProxyNode) classIt.next();
			for (Iterator<ProxyNode> proxyClassIt = kind.getSuccessors()
					.iterator(); proxyClassIt.hasNext();) {
				ProxyNode proxyClass = (ProxyNode) proxyClassIt.next();
				// If the node was already represented as a tab,
				// it does not have to be created again.
				ProxyTabPanel newTabForClass = null;
			//	if (proxyClass.isNew()) {
					// Now the representation is not new anymore
					proxyClass.setIsNew(false);
					//newTabForClass = (new JPanel(tabLayout));
					//String tabName = proxyClass.getproxyClass();
					//newTabForClass.setName(tabName);
					newTabForClass = new ProxyTabPanel(_proxyTabs.countComponents() +1);
					String tabName = newTabForClass.getName();
					_tabList.add(tabName);
					Collections.sort(_tabList);
					JScrollPane scrollTab =  new JScrollPane(newTabForClass); 
					_proxyTabs.insertTab(tabName, null, scrollTab, "",
							_tabList.indexOf(tabName)); 
							
				// Check wether a tab is selected. If no tab is availabe,
				//create one
					c.gridx = 0;
					c.gridy = -1;
			//	} else {
					// Search the right tab for the proxy class
					// It already exists because it is not new!
				//	int oldIndex = _proxyTabs.getSelectedIndex();
				//	_proxyTabs.setSelectedIndex(_proxyTabs
				//			.indexOfTab(proxyClass.getproxyClass()));
				//	newTabForClass = () _proxyTabs.getSelectedComponent();
				//	_proxyTabs.setSelectedIndex(oldIndex);
				}

				for (Iterator<ProxyNode> proxyIt = proxyClass.getSuccessors()
						.iterator(); proxyIt.hasNext();) {
					ProxyNode proxy = (ProxyNode) proxyIt.next();
					if (proxy.isNew()) {
						proxy.setIsNew(false);
						// To get rid of the point at the end of the name.
						//JTextField proxyIdentifier = new JTextField  (_localhostName.substring(0,_localhostName.length() -1 ));
						//proxyIdentifier.setPreferredSize(new Dimension(100,25));



						ProxyEntry proxyEntry = new ProxyEntry(proxy);
						// Add custom listener to update the list
						// that displays the currently running proxies
						proxyEntry.addProxyRemovedEventListener(new ActionListener(){
							public void actionPerformed(ActionEvent arg0) {
								
								String proxyName = arg0.getActionCommand();
								if (arg0.getID() == 100){
									_proxydata.addElement(proxyName);
								}
								else {
								_proxydata.removeElement(proxyName);
								}
							}
						});
						_eventHeapsList.addListSelectionListener(proxyEntry);
						addEventHeapRemovedEventListener(proxyEntry);
						
						
						newTabForClass.add(proxyEntry,c);
						c.gridx = 0;
					} // end if (ProxyNode.isNew());
				} // end for-loop
			} // end if proxyClass.isNew();
		} // end of outer loop*/
	} // end of method
	
    // This methods allows classes to register for MyEvents
    public void addEventHeapRemovedEventListener(ActionListener listener) {
    	_myListenerList.add(ActionListener.class, listener);
    }

	public void windowOpened(WindowEvent arg0) {
	}

	public void windowClosing(WindowEvent arg0) {
		quitAllProxies();
		if (_startLocalEHButton.getText().equals("Stop local EH"))
			_startLocalEHButton.doClick();
		if (_ehLoggerThread != null)
			_ehLoggerThread.kill();
		System.out.println("All processes were successfully ended. \n " +
				"Have a nice day!");
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
				if (_startLocalEHButton.getText().equals("Stop Local EH"))
					_startLocalEHButton.setEnabled(false);
			}
		}
		catch (UnknownHostException e) {
			System.out.println("The localhost name could not be retrieved." +
					"Please check your network settings");
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
		try {
			String localHostName = InetAddress.getLocalHost().getHostName();
		// if the local host EH was removed, reenable the button
			if ((arg0.getName().equals(localHostName)) && (_startLocalEHButton.getText().equals("Stop Local EH"))) 
					_startLocalEHButton.setEnabled(true);
		} catch (UnknownHostException e) {
			System.out.println("The localhost name could not be retrieved." +
			"Please check your network settings");
		}

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
		ProxyHolderPanel proxyHolderPanel = new ProxyHolderPanel(new GridBagLayout (),newTabNumber);
		JScrollPane proxyTabScrollPane = new JScrollPane(proxyHolderPanel);
		proxyTabScrollPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		_proxyTabs.addTab(newTabName, proxyTabScrollPane);
		_proxyTabs.setSelectedIndex(_proxyTabs.getComponentCount() - 1);
		_proxyTabs.doLayout();
	}
	
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
	

} // end of class

