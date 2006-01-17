import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;
import java.util.Vector;

import javax.jmdns.JmDNS;
import javax.jmdns.ServiceEvent;
import javax.jmdns.ServiceListener;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;
import javax.swing.JToggleButton;

import org.jdom.Document;
import org.jdom.Element;
import org.jdom.JDOMException;
import org.jdom.input.SAXBuilder;

@SuppressWarnings("serial")
public class PLMainFrame extends JFrame {

	private Vector _ehList = new Vector<String>();
	private Process _ehProcess;
	private JList _eventHeapsList;
	private DefaultListModel _listModel;
	private ArrayList _proxyButtonsList;
	private DefaultListModel _proxydata;
	private JTabbedPane _proxyTabs;
	private ProxyTree _proxyTree;
	private ArrayList _tabList = new ArrayList<String>();
	private Element _xmlRoot;
	private ColoredToggleButton _startLocalEHButton;
	private JmDNS _jmdns;
	private String _separator;
	
	public PLMainFrame() {
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		// TODO: Add a window listener that ends all open processes when
		// quitting
		// an application
		
		if (System.getProperty("os.name").contains("Windows"))
			_separator = ";";
		else
			_separator = ":";
		
		_proxyTabs = new JTabbedPane();
		try {
			_jmdns = new JmDNS();
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		// Load the configuration file
		File configFile = new File("configStarter.xml");
		Document docWithConfig = new Document();
		SAXBuilder builder = new SAXBuilder();
		try {
			docWithConfig = builder.build(configFile);
			_xmlRoot = docWithConfig.getRootElement();
			System.out.println("Processing XML - file");
		} catch (JDOMException e) {
			e.printStackTrace();
			System.out.println("Error while accessing XML file");
		} 
		catch (IOException e) {
			System.out.println("No configFile found. New file created");
		}
		_proxyButtonsList = new ArrayList<proxyNodeToggleButton>();
		createProxyTree();
		buildUpWindow();
	}

	public void buildUpWindow() {
		// Create three basic panels: The topRowPanel holds SmartIcons
		// bottomRowPanel holds additional information
		// eastPanel holds other panes for control buttons, a list of running
		// proxies
		// and a dynbamic list of event heaps found on the network.

		JPanel topRowPanel = new JPanel();
		topRowPanel.add(new JLabel(
				"This space is reserved for a smarticon list or similar"));
		JPanel bottomRowPanel = new JPanel();
		JPanel eastPanel = new JPanel(); // standard FlowLayout
		eastPanel.setPreferredSize(new Dimension(180, 200));
		JPanel westPanel = new JPanel();
		westPanel.setPreferredSize(new Dimension(180,200));
		add(topRowPanel, BorderLayout.NORTH);
		add(bottomRowPanel, BorderLayout.SOUTH);
		add(eastPanel, BorderLayout.EAST);
		add(westPanel, BorderLayout.WEST);
		add(_proxyTabs, BorderLayout.CENTER);

		// Creation of the panel that holds a list of found event heaps
		JPanel showEventHeaps = new JPanel(new BorderLayout());
		showEventHeaps
				.add(new JLabel("Found Event Heaps:"), BorderLayout.NORTH);
		// Scan for local event heaps
		// This is performed with the help of a ServiceListener
			_jmdns.addServiceListener("_eheap._tcp.local.",
					new ServiceListener() {

						public void serviceAdded(ServiceEvent arg0) {
							//reenable the Start EH button when the local service
							// actually runs.
							//TODO: I need a way to find out the source adress
							// where the service is running --> Problems with
							// Mac and Windows.
							_startLocalEHButton.setEnabled(true);
							_listModel.addElement(arg0.getName());
							String ehName = arg0.getName();
							_ehList.addElement(ehName);
							// If no element was selected in the list, select
							// the first one
							if (_eventHeapsList.getSelectedIndex() == -1)
								_eventHeapsList.setSelectedIndex(0);
							String localhost = _jmdns.getHostName();
								for (Iterator<proxyNodeToggleButton> buttonIt = _proxyButtonsList
										.iterator(); buttonIt.hasNext();) {
									proxyNodeToggleButton currentButton = buttonIt
											.next();
									// Enable the button as soon as there is an
									// Event Heap
									if (!currentButton.isEnabled())
										currentButton.setEnabled(true);

									currentButton.getCorrespondingComboBox()
											.updateUI();
									// select the localhost or the first element
									// in a ComboBox as soon as there is an event
									// heap available.
									if (currentButton
											.getCorrespondingComboBox()
											.getSelectedIndex() == -1)
										if (!_listModel.isEmpty())
											if (_listModel.contains(localhost))
												currentButton
														.getCorrespondingComboBox()
														.setSelectedItem(
																localhost);
											else
												currentButton
														.getCorrespondingComboBox()
														.setSelectedItem(
																arg0.getName());
								}
						}

						public void serviceRemoved(ServiceEvent arg0) {
							_ehList.remove(arg0.getName());
							_listModel.removeElement(arg0.getName());
							boolean emptyModel;
							emptyModel = _listModel.isEmpty();
							// Disconnect proxies that were connected to the
							// removed service
							// and if no service is available, nothing remains
							// enabled.
							for (Iterator<proxyNodeToggleButton> buttonIt = _proxyButtonsList
									.iterator(); buttonIt.hasNext();) {
								proxyNodeToggleButton currentButton = buttonIt
										.next();
								if (currentButton.isSelected())
									currentButton.doClick();
								if (!emptyModel) {
									currentButton.getCorrespondingComboBox()
											.setSelectedIndex(0);
								} else {
									currentButton.getCorrespondingComboBox()
											.setSelectedIndex(-1);
									currentButton.setEnabled(false);
								}
							}
						}

						public void serviceResolved(ServiceEvent arg0) {
							// This method is not needed, therefore the stub
							// remains
							// Everything is done with the serviceAdded - method
						}
					});

		// create command buttons to control proxies and the local event heap.
		JButton connectAllButton = new JButton("Connect All To ...");
		connectAllButton.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent e) {
				// Go through the list of Buttons of the tab and connect them
				// to the selected Event Heap.
				// If some proxies are already running, disconnect them first
				String selectedEventHeap = _listModel.getElementAt(
						_eventHeapsList.getSelectedIndex()).toString();
				System.out
						.println("Connecting all proxies of the current tab to "
								+ selectedEventHeap);

				for (ListIterator<proxyNodeToggleButton> buttonIterator = _proxyButtonsList
						.listIterator(); buttonIterator.hasNext();) {
					proxyNodeToggleButton currentButton = buttonIterator.next();
					// only if the button in the list belongs to the active tab
					// it has to be unselected (if it is selected)
					if (currentButton
							.getCorresponingProxyNode()
							.getproxyClass()
							.equals(_proxyTabs.getSelectedComponent().getName())) {
						if (currentButton.isSelected()) {
							currentButton.doClick();
						}
						try {
							currentButton.startProxy(selectedEventHeap);
							currentButton.getCorrespondingButton().setEnabled(
									true);
							currentButton.setSelected(true);
							currentButton.getCorresponingProxyNode()
									.getCorrespondingThread().setTextArea(
											currentButton
													.getCorrespondingButton()
													.getTextArea());
						} catch (IOException e1) {
							e1.printStackTrace();
						}
					}
				}
			}
		}); // end of ActionListener class

		JButton disconnectAllButton = new JButton("Disconnect All");
		disconnectAllButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				for (ListIterator<proxyNodeToggleButton> buttonIterator = _proxyButtonsList
						.listIterator(); buttonIterator.hasNext();) {
					proxyNodeToggleButton currentButton = buttonIterator.next();
					// only if thecurrent button is selected, the proxy has to
					// be
					// disconnected by simply clicking it.
					if (currentButton
							.getCorresponingProxyNode()
							.getproxyClass()
							.equals(_proxyTabs.getSelectedComponent().getName())) {
						if (currentButton.isSelected()) {
							System.out.println("active");
							currentButton.doClick();
						}
					}
				}
			}
		}); // end of ActionListener class

		_startLocalEHButton = new ColoredToggleButton(
				"Start local EH", Color.RED, Color.ORANGE);
		_startLocalEHButton.setPreferredSize(new Dimension(100, 25));
		_startLocalEHButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				File env = new File(_xmlRoot.getChild("EventHeapLocation").getValue());
				// Construct launch commnand for the event heap
				// from the information in the XML file.
				String iROSLoc = _xmlRoot.getChild("Libraries").getChild("iROS").getValue();
				String jmdnsLoc = _xmlRoot.getChild("Libraries").getChild("JmDNS").getValue();
				String cmd = "java -cp " + iROSLoc 
					+ _separator + jmdnsLoc + " "
					+ "iwork.eheap2.server.EventHeapServer";
				if (_startLocalEHButton.isSelected()) {
					_startLocalEHButton.setText("Stop local EH");
					// lock the button until the service is actually running.
					_startLocalEHButton.setEnabled(false);
					try {
						_ehProcess = Runtime.getRuntime().exec(cmd, null, env);
						System.out.println("Eh is running");
					} catch (IOException e1) {
						e1.printStackTrace();
					}
				} else {
					_startLocalEHButton.setText("Start local EH");
					System.out.println("EH stopped");
					_ehProcess.destroy();
				}
			} // end of method.

		}); // end of ActionListener class

		
		JButton connectSelectedButton = new JButton("Connect Selected To ...");
		_listModel = new DefaultListModel();
		_eventHeapsList = new JList(_listModel);
		
		// set the preferred size for the buttons
		Dimension eastPanelButtonSize = new Dimension(180,35);
		_startLocalEHButton.setPreferredSize(eastPanelButtonSize);
		connectAllButton.setPreferredSize(eastPanelButtonSize);
		disconnectAllButton.setPreferredSize(eastPanelButtonSize);
		connectSelectedButton.setPreferredSize(eastPanelButtonSize);
		
		// add the created panels and buttons
	
		eastPanel.add(_startLocalEHButton);
		eastPanel.add(connectAllButton);
		eastPanel.add(connectSelectedButton);
		eastPanel.add(showEventHeaps);
		showEventHeaps.add(_eventHeapsList, BorderLayout.CENTER);
		bottomRowPanel.add(disconnectAllButton);
		
		// Create a panel that displays all running proxies
		JPanel runningProxies = new JPanel(new BorderLayout());
		runningProxies.add(new JLabel("Proxies currently running"),
				BorderLayout.NORTH);
		_proxydata = new DefaultListModel();
		JList proxyList = new JList(_proxydata);
		runningProxies.add(proxyList, BorderLayout.CENTER);
		westPanel.add(runningProxies);
		// Create a dialog to add proxies from an additional location.
		// After a directory was chosen the List proxyDirectories is updated.
		// TODO: Load and Save Directories

		ActionListener callChooseDialog = new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				JFileChooser chooseProxyDir = new JFileChooser();
				chooseProxyDir
						.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
				chooseProxyDir.setAcceptAllFileFilterUsed(false);
				chooseProxyDir.setFileFilter(new CustomFileFilter());
				int returnVal = chooseProxyDir.showDialog(null,
						"Search Directory");
				// Search the selected directory
				if (returnVal == JFileChooser.APPROVE_OPTION) {
					File searchDirectory = chooseProxyDir.getSelectedFile();
					_proxyTree = new ProxyFinder().getProxyTree(
							searchDirectory, "proxy-description.xml");
					updateWindow();
				}
			}
		};

		// Create a menu bar
		// TODO: Distinguish between Mac- and Windows-style menu positions
		JMenuBar applicationMenuBar = new JMenuBar();
		JMenu fileMenu = new JMenu("File");
		JMenuItem chooseDir = new JMenuItem("choose proxy directory");
		fileMenu.add(chooseDir);
		chooseDir.addActionListener(callChooseDialog);
		applicationMenuBar.add(fileMenu);
		setJMenuBar(applicationMenuBar);

		// Let the OS decide where the new window
		// appears.
		setLocationByPlatform(true);
		updateWindow();
		setSize(800,600);
		setVisible(true);
	}

	@SuppressWarnings("unchecked")
	public void createProxyTree() {
		Element searchDirs = _xmlRoot.getChild("SearchDirectories");
		List<Element> xmlElements = searchDirs.getChildren();
		for (ListIterator<Element> xmlIterator = xmlElements.listIterator(); xmlIterator
				.hasNext();) {
			Element currentElement = xmlIterator.next();
			File searchDirectory = new File(currentElement.getValue());
			System.out.print(searchDirectory);
			_proxyTree = new ProxyFinder().getProxyTree(searchDirectory,
					"proxy-description.xml");
		}
	}

	public void exitApplication() {
		//TODO: implement method that ends all proxies and the current event heap.
	}

	public void updateWindow() {
		Dimension buttonDimension = new Dimension(140, 25);
		GridBagConstraints c = new GridBagConstraints();
		GridBagLayout tabLayout = new GridBagLayout();

		for (Iterator<ProxyNode> classIt = _proxyTree.getTreeRoot()
				.getSuccessors().iterator(); classIt.hasNext();) {
			ProxyNode kind = (ProxyNode) classIt.next();
			for (Iterator<ProxyNode> proxyClassIt = kind.getSuccessors()
					.iterator(); proxyClassIt.hasNext();) {
				ProxyNode proxyClass = (ProxyNode) proxyClassIt.next();
				// If the node was already represented as a tab,
				// it does not have to be created again.
				JPanel newTabForClass = null;
				if (proxyClass.isNew()) {
					// Now the representation is not new anymore
					proxyClass.setIsNew(false);
					newTabForClass = (new JPanel(tabLayout));
					String tabName = proxyClass.getproxyClass();
					newTabForClass.setName(tabName);
					_tabList.add(tabName);
					Collections.sort(_tabList);
					_proxyTabs.insertTab(tabName, null, newTabForClass, "",
							_tabList.indexOf(tabName));
					c.gridx = 0;
					c.gridy = -1;
				} else {
					// Search the right tab for the proxy class
					// It already exists because it is not new!
					int oldIndex = _proxyTabs.getSelectedIndex();
					_proxyTabs.setSelectedIndex(_proxyTabs
							.indexOfTab(proxyClass.getproxyClass()));
					newTabForClass = (JPanel) _proxyTabs.getSelectedComponent();
					_proxyTabs.setSelectedIndex(oldIndex);
				}

				for (Iterator<ProxyNode> proxyIt = proxyClass.getSuccessors()
						.iterator(); proxyIt.hasNext();) {
					ProxyNode proxy = (ProxyNode) proxyIt.next();
					if (proxy.isNew()) {
						proxy.setIsNew(false);
						proxyNodeToggleButton newButtonForTab = new proxyNodeToggleButton(
								proxy.getName(), Color.GREEN, Color.RED);
						newButtonForTab.setPreferredSize(buttonDimension);
						showConsoleButton showConsole = new showConsoleButton(
								newButtonForTab, "Show Console");
						showConsole.setPreferredSize(buttonDimension);
						newButtonForTab.setCorrespondingButton(showConsole);
						newButtonForTab.setCorrerspondingProxyNode(proxy);
						JComboBox newBox = new JComboBox(_ehList);
						newBox.setPreferredSize(new Dimension(100, 25));
						newButtonForTab.setCorrespondingComboBox(newBox);
						showConsole.setCorrespondingCombox(newBox);
						newButtonForTab.addActionListener(new ActionListener() {
							public void actionPerformed(ActionEvent e) {

								proxyNodeToggleButton ccButton = (proxyNodeToggleButton) e
										.getSource();
								if (ccButton.isSelected()) {
									_proxydata.addElement(ccButton
											.getCorresponingProxyNode()
											.getName());
								} else if (_proxydata.contains(ccButton
										.getCorresponingProxyNode().getName()))
									_proxydata.removeElement(ccButton
											.getCorresponingProxyNode()
											.getName());
							}
						});

						if (_ehList.isEmpty())
							newButtonForTab.setEnabled(false);
						
						_proxyButtonsList.add(newButtonForTab);
						newTabForClass.add(newButtonForTab, c);
						c.gridx = c.gridx + 1;
						newTabForClass.add(newBox, c);
						c.gridx = c.gridx + 1;
						newTabForClass.add(showConsole, c);
						c.gridx = 0;
					} // end if (ProxyNode.isNew());
				} // end for-loop
			} // end if proxyClass.isNew();
		} // end of outer loop
	} // end of method

} // end of class

