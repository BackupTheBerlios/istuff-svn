import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
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
import javax.swing.JTextField;
import javax.swing.JTree;
import javax.swing.ListModel;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;

import org.jdom.Document;
import org.jdom.Element;
import org.jdom.JDOMException;
import org.jdom.input.SAXBuilder;

public class PLMainFrame extends JFrame{
  
	private Vector _ehList = new Vector<String>();//<String>;// _ehList;// = {"localhost", "testhost"};
	private GridBagLayout tabLayout = new GridBagLayout();
	private GridBagConstraints c = new GridBagConstraints();
	private List<File> proxyDirectories = new ArrayList<File> (1024);
	private JTabbedPane proxyTabs = new JTabbedPane();
	private ProxyTree proxyTree;
	private DefaultMutableTreeNode root = new DefaultMutableTreeNode("STARTUP");
	private DefaultTreeModel model = new DefaultTreeModel(root);
	private JTree proxyClassesTree = new JTree(model);
	private JPanel treePanel = new JPanel();
	private SAXBuilder builder = new SAXBuilder();
	private ArrayList tabList = new ArrayList<String>();
	private Dimension buttonDimension = new Dimension(140,25);
	private FindProxyStarters proxyFinder = new FindProxyStarters();//(searchDirectory, "proxy-description.xml",proxyTree);
	private DefaultListModel proxydata;// = new DefaultListModel();
	private JList proxyList;// = new JList (proxydata);

	
	public PLMainFrame() {  
	  this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	  scanForEventHeaps();
	  buildUpWindow();
	}
	
	@SuppressWarnings("unchecked")
	public void buildUpWindow () {

		// Load the configuration file
		File configFile = new File("configStarter.xml");
		Document docWithConfig = new Document();
        try {
			docWithConfig = builder.build(configFile);
			Element xmlFileRoot = docWithConfig.getRootElement();
			if (xmlFileRoot != null)
			{
				System.out.println("Processing XML - file");
				System.out.println(xmlFileRoot.getChildText("dir"));
				List<Element> xmlElements = xmlFileRoot.getChildren();
				for (ListIterator<Element> xmlIterator = xmlElements.listIterator(); xmlIterator.hasNext();)
				{
					File searchDirectory = new File(xmlIterator.next().getText());
					proxyTree = proxyFinder.getProxyTree(searchDirectory, "proxy-description.xml");
				}
			  }
        }
			catch (JDOMException e) {
			e.printStackTrace();
		} catch (IOException e) {
			System.out.println("No configFile found. New file created");
			//e.printStackTrace();
		}
		
		
		//NOTE: The XML-reading works.
		// TODO: Now a way to precheck the XML descriptions is needed.
		// That can be postponed
		

		
	 // add a tabbed pane to the center. This pane holds the different proxy 
	 // classes view.
	 // At this stage of development, the first tab is directly initialized with
	 // a JPanel.
	 
	 
	 // For all tabs the same GridBagLayout is to be used.
	 // The constraints are defined here.
	 
	 //TODO: Now a method that scans directories for availiable proxies
	 // on the current system is needed.
	 // With that method, the JTree can be filled
	 // and the tabs instantiated as soon as a user wants to see them.
	 
	 add(treePanel, BorderLayout.WEST);
	 treePanel.add(proxyClassesTree);
	 //this.add(proxyClassesTree, BorderLayout.WEST);
	 JPanel topRowPanel = new JPanel();
	 topRowPanel.add(new JLabel("This space is reserved for a smarticon list or similar"));
	 add(topRowPanel, BorderLayout.NORTH);
	 
	 JPanel bottomRowPanel = new JPanel();
	 bottomRowPanel.add(new JLabel ("Here some other Panel can be added"));
	 add(bottomRowPanel, BorderLayout.SOUTH);
	 
	 JPanel eastPanel = new JPanel (new GridLayout(0,1));
	 
	 JPanel runningProxies = new JPanel(new BorderLayout());
	 runningProxies.add(new JLabel("Proxies currently running"),BorderLayout.NORTH);
	 proxydata = new DefaultListModel();
	 proxyList = new JList (proxydata);
	 
	 runningProxies.add (proxyList, BorderLayout.CENTER);
	 eastPanel.add(runningProxies);
	 
	 JPanel showEventHeaps = new JPanel (new BorderLayout());
	 showEventHeaps.add(new JLabel ("Found Event Heaps:"), BorderLayout.NORTH);
	 Object[] listOfEHeaps = _ehList.toArray();
	 JList eventHeapsList = new JList (listOfEHeaps);
	 showEventHeaps.add(eventHeapsList, BorderLayout.CENTER);
	 eastPanel.add(showEventHeaps);
		//TODO A button is needed to scan for existing Event Heaps
	 // TODO Add real scanning functionality to the button
	 JButton startLocalEHButton = new JButton("Start local EH");
	 startLocalEHButton.addActionListener(new ActionListener(){

		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			//TODO Modify the Config.xml file --> Enter path to local EH program
			System.out.println("JOJO, local event heap is being started!");
		}
		 
	 });
	 
	 JButton eHeapScanButton = new JButton ("Scan for EventHeaps");
	 eHeapScanButton.addActionListener(new ActionListener (){

		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			System.out.println("Scanning for available Event Heaps...");
			
			
		}
		 
	 });
	 bottomRowPanel.add(eHeapScanButton, BorderLayout.CENTER);
	 bottomRowPanel.add(startLocalEHButton, BorderLayout.EAST);
	 add(eastPanel, BorderLayout.EAST);
	 
	 // ActionListeners
	 // After a directory was chosen the List proxyDirectories is updated
	 // TODO: Load and Save Directories
	 // TODO: Add support to extend existing lists
	 
	 ActionListener callChooseDialog = new ActionListener(){
		 public void actionPerformed (ActionEvent e){
			 JFileChooser chooseProxyDir = new JFileChooser();
			 chooseProxyDir.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
			 chooseProxyDir.setAcceptAllFileFilterUsed(false);
			 chooseProxyDir.setFileFilter(new CustomFileFilter());	
			 int returnVal = chooseProxyDir.showDialog(null,"Search Directory");
			 // Search the selected directory 
			 if (returnVal == JFileChooser.APPROVE_OPTION){
			   File searchDirectory = chooseProxyDir.getSelectedFile();
			   //FindProxyStarters proxyStarters = new FindProxyStarters(searchDirectory, "proxy-description.xml",proxyTree);
			  proxyTree = proxyFinder.getProxyTree(searchDirectory, "proxy-description.xml");
			  System.out.println("DIR NAME:" + searchDirectory);
			  updateWindow();
			}	
		 }
		 };
	 
			   //TODO A JTree should be returned that holds the directory structur for the
			   // proxy classes and for each class a list of the directories such that a tab can be filled.
			   //On double click: Open a tab
			   //on expanding: Enable Drag and Drop to create an own tab
			   // or extend the existing one
			   
		 			 
	 
	 // Fill the tabbed Pane with the nodes from the proxy tree
	 // each new kind is presented on a new tab
		 
	
	
	 
	 JMenuBar applicationMenuBar = new JMenuBar();
	 JMenu fileMenu = new JMenu ("File");
	 JMenuItem chooseDir = new JMenuItem("choose proxy directory");
	 fileMenu.add(chooseDir);
	 chooseDir.addActionListener(callChooseDialog);
	 applicationMenuBar.add(fileMenu);
	 this.setJMenuBar(applicationMenuBar);
	 
	 treePanel.remove(proxyClassesTree);
	   
	   
     treePanel.updateUI();
	 
	 setMinimumSize(new Dimension(800,500));
	 setSize(getMinimumSize());
	 this.setLocationByPlatform(true); 
	 // Let the OS decide where the new window
	 // appears.
	 updateWindow();
	 //TODO Time for some manual testing
	 // it is not clear wether inserting or creating the tabs does not work
	 //TODO Inserting does not work correctly
	 System.out.println("TreeTest:");
	 //ListIterator it = proxyTree.getTreeRoot().getSuccessors().getFirst().getSuccessors().listIterator();
	//ProxyNode node;	
	 //for (ListIterator<ProxyNode> it = proxyTree.getTreeRoot().getSuccessors().getFirst().getSuccessors().getLast().getSuccessors().listIterator(); it.hasNext();)
		//{
			//node = it.next();
			//System.out.println(node.getName());
		//}
	 this.add(proxyTabs, BorderLayout.CENTER); 
	 this.setVisible(true);
	
	 
	 
	 // After choosing the corresponding command, a dialog should be displayed
	 // that lets the user choose a directory where to scan for proxies
	 
	 // Instantiate another floating window in that the running proxies are displayed.
	 
	
	// These lines can be used to make use of a floating window without decorations
	// RollDownWindow runningProxies = new RollDownWindow ("Running Proxies NEW");
	// JPanel titleBar = new JPanel();
	// titleBar.add(new JLabel("Running Proxies"));
	 //runningProxies.add(titleBar, BorderLayout.NORTH);
	 //runningProxies.getRootPane().setWindowDecorationStyle(JRootPane.FRAME);
	 
	 //runningProxies.setLocation(this.getLocationOnScreen().x+(int)this.getSize().getWidth(),this.getY());//(int)this.getLocationOnScreen().getY()+(int)this.getSize().height);
	 //runningProxies.setLocationRelativeTo(this);
	 //runningProxies.pack();
	// add(runningProxies,BorderLayout.EAST);
	 
	 //update(getGraphics());
	 //runningProxies.setVisible(true);
	}
	
	
	public void updateWindow(){
		//IDEA: Delete the whole Panel and rebuild it
		// Activate the buttons that were activated before
		// The buttons "know" about that
		
		//delete the proxyTabs
		//proxyTabs.removeAll();
		//this.remove(proxyTabs);	
		//this.add(proxyTabs);
		
		
		//Now each tab has to be cleared
		
		for ( Iterator<ProxyNode> i = proxyTree.getTreeRoot().getSuccessors().iterator(); i.hasNext();)
		 {
		    ProxyNode kind = (ProxyNode) i.next();
		    for (Iterator<ProxyNode> i2 = kind.getSuccessors().iterator(); i2.hasNext();)
		    	{
		    		ProxyNode proxyClass = (ProxyNode) i2.next();
		    		//if the node was already represented as a tab,
		    		//it does not have to be created again
		    		JPanel newTabForClass = null;
		    		if (proxyClass.isNew())		
		    		{	
		    		  //Now the representation is not new anymore
		    		  proxyClass.setIsNew(false);
		    		  newTabForClass = (new JPanel(tabLayout));
		    		  String tabName = proxyClass.getproxyClass();
		    		  newTabForClass.setName(tabName);
		    		  tabList.add(tabName);
		    		  Collections.sort(tabList);
		    		  proxyTabs.insertTab(tabName,null,newTabForClass,"",tabList.indexOf(tabName)); 
		    		  c.gridx = 0;
		    		  c.gridy = -1;
		    		 }
		    		else
		    		{
		    			//Search the right tab for the proxy class
			    		  // It already exists because it is not new!
		    			int oldIndex = proxyTabs.getSelectedIndex();
		    			proxyTabs.setSelectedIndex(proxyTabs.indexOfTab(proxyClass.getproxyClass()));
		    			newTabForClass = (JPanel) proxyTabs.getSelectedComponent();
		    			proxyTabs.setSelectedIndex(oldIndex);
		    		}	
		    		
		    		  for (Iterator<ProxyNode> i3 = proxyClass.getSuccessors().iterator(); i3.hasNext();)
		    	    	{
		    		      ProxyNode proxy = (ProxyNode) i3.next();
		    			  if (proxy.isNew())
		    			  {
		    				proxy.setIsNew(false);
		    				ChangeColorButton newButtonForTab = new ChangeColorButton (proxy.getName(),Color.GREEN,Color.RED);
		    				newButtonForTab.setPreferredSize(buttonDimension);
		    			    showConsoleButton showConsole = new showConsoleButton(newButtonForTab, "Show Console");
		    			    showConsole.setPreferredSize(buttonDimension);
		    			    newButtonForTab.setCorrespondingButton(showConsole);
		    			    newButtonForTab.setCorrerspondingProxyNode(proxy);
		    			    if (newButtonForTab.isCorrespondingProxyRunning())
		    			      newButtonForTab.doClick();
		    			
		    			    JComboBox newBox = new JComboBox(_ehList);
		    			    newButtonForTab.setCorrespondingComboBox(newBox);
		    			    showConsole.setExecutablePrefix(proxy.getExecutableName());
		    			    showConsole.setCorrespondingCombox(newBox);
		    			    showConsole.setExecutablePrefix(proxy.getExecutableName());
		    			    newButtonForTab.addActionListener(new ActionListener(){
		    			    	public void actionPerformed (ActionEvent e){
		    			    		
		    			    		ChangeColorButton ccButton = (ChangeColorButton) e.getSource();
		    			    		if (ccButton.isSelected())
		    			    		{
		    			    			proxydata.addElement(ccButton.getCorresponingProxyNode().getName());
		    			    		}
		    			    		else 
										if(proxydata.contains(ccButton.getCorresponingProxyNode().getName()))
												proxydata.removeElement(ccButton.getCorresponingProxyNode().getName());
		    			    		}
		    			    		});
		    				
		    			    // Add an additonal field to manually specify an Event Heap
		    			    JTextField manualEHName = new JTextField("Custom EH Name");
		    			    manualEHName.setPreferredSize(new Dimension(120,25));
		    			   
		    			    // TODO Add button to run a local Event Heap
		    				// An additional field should be able to specify the
		    				//name of the Even Heap

		    			    newTabForClass.add (newButtonForTab,c);
		    			    c.gridx = c.gridx + 1;
		    			    newTabForClass.add(newBox,c);
		    			    c.gridx = c.gridx + 1;
		    			    newTabForClass.add(manualEHName,c);
			    			c.gridx = c.gridx +1;
			    			newTabForClass.add (showConsole,c);
			    			c.gridx = 0;
		    		    } // end if (ProxyNode.isNew());
		    	      } // end for-loop
		    	    } // end if proxyClass.isNew();
		          } // end of outer loop
	}// end outer for-loop
			  // end of method
	public void scanForEventHeaps (){
		_ehList.add("localhost");
		_ehList.add("another machine");
		//System.out.println(_ehList[1]+ "Array value");
	}
	
	public void loadAndStartProxies (){
		
	}
			 
		 
} // end of class



