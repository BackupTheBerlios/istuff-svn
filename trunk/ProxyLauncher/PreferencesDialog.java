import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Vector;

import javax.swing.BoxLayout;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.event.EventListenerList;
import javax.swing.filechooser.FileFilter;

import org.jdom.Document;
import org.jdom.Element;
import org.jdom.output.Format;
import org.jdom.output.XMLOutputter;

@SuppressWarnings("serial")
public class PreferencesDialog extends JDialog {

	private DefaultListModel _proxyDirsListModel;
	private JList _proxyDirsList;
	private JTextField _irosTextField;
	private JTextField _jmdnsTextField;
	
	public PreferencesDialog () {
		displayAndSetPreferences();
	}
	
	public void displayAndSetPreferences () {
		// A new dialog is displayed in which the user can specify
		// the directories needed. Values from the XML file are
		// directly read and displayed.
		
		// Create an ActionListener that is responsible for browsing and
		// adding the lines into the textfields.
		
		ActionListener jarBrowser = new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
		// Open a JFileChooser
		// The different Buttons are differentiated by their action commands
		String command = arg0.getActionCommand();
		JFileChooser chooser = new JFileChooser();
		if (command.equals("Proxy Directories")){
			chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
		}
		else {
			chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
		}
		FileFilter filter = new CustomFileFilter(command);
		chooser.setAcceptAllFileFilterUsed(false);
		chooser.setFileFilter(filter);
		
		int returnVal = chooser.showOpenDialog(getInstance());
		if (returnVal == JFileChooser.APPROVE_OPTION) {
			File fileName = chooser.getSelectedFile();
			if (command.equals("iROS.jar"))
				_irosTextField.setText(fileName.getAbsolutePath());
			else if (command.equals("jmdns.jar"))
					// textfield change
				_jmdnsTextField.setText(fileName.getAbsolutePath());
			else
				_proxyDirsListModel.addElement(fileName.getAbsoluteFile());
		}
	}
		};
		
		//Construct the dialog.
		
		JPanel preferencesFrame = new JPanel(new BorderLayout ());		
		preferencesFrame.setLayout(new BorderLayout ());
		JPanel prefPane = new JPanel ();
		prefPane.setLayout(new BoxLayout (prefPane, BoxLayout.Y_AXIS));
		prefPane.setAlignmentX(Component.CENTER_ALIGNMENT);
	
		JPanel p;
		// first row 
		prefPane.add(new JLabel ("Libraries:"));
		
		// Second row Panel construction
		p = new JPanel();
		p.add((new JLabel ("iRos Location:"))).setPreferredSize(new Dimension (120,25));
		_irosTextField = new JTextField ();
		_irosTextField.setEditable(false);
		_irosTextField.setPreferredSize(new Dimension (300,25));
		p.add(_irosTextField);
		JButton irosButton = new JButton("Browse");
		irosButton.setActionCommand("iROS.jar");
		irosButton.addActionListener(jarBrowser);
		p.add(irosButton);
		prefPane.add(p);
		
//		 Third row Panel construction (empty)
		p = new JPanel();
		p.add((new JLabel ("JmDNS Location:"))).setPreferredSize(new Dimension (120,25));
		_jmdnsTextField = new JTextField ();
		_jmdnsTextField.setEditable(false);
		_jmdnsTextField.setPreferredSize(new Dimension (300,25));
		p.add(_jmdnsTextField);
		JButton jmdnsButton = new JButton("Browse");
		jmdnsButton.setActionCommand("jmdns.jar");
		jmdnsButton.addActionListener(jarBrowser);
		p.add(jmdnsButton);
		prefPane.add(p);
		
		// Fourth row
		prefPane.add(new JLabel ());
		
		// Fith row
		prefPane.add(new JLabel ("Proxy Directories:"));
		
		// Sixth row
		p = new JPanel ();
		_proxyDirsListModel = new DefaultListModel();
		_proxyDirsList = new JList (_proxyDirsListModel);
		_proxyDirsList.setPreferredSize(new Dimension (200, 100));
		// fill the list
		Vector <File> searchDirs = ConfigDataHolder.getSearchDirectories();
		for (int i=0; i < searchDirs.size(); i++) 
			_proxyDirsListModel.addElement(searchDirs.get(i));
			
		JScrollPane proxyDirsListScrollPane = new JScrollPane (_proxyDirsList);
		p.add(proxyDirsListScrollPane);
		prefPane.add(p);
		// Right below the list we need a button to add and
		// remove the selected Element
		p = new JPanel();
		JButton removeDirButton = new JButton ("Remove");
		removeDirButton.addActionListener(new ActionListener(){
			public void actionPerformed (ActionEvent e){
				int selectedIndex = _proxyDirsList.getSelectedIndex();
				if (selectedIndex != -1) 
					_proxyDirsListModel.removeElementAt(selectedIndex);
			}
		});
	
		JButton addDirButton = new JButton ("Add");
		addDirButton.setActionCommand("Proxy Directories");
		addDirButton.addActionListener(jarBrowser);
		
		p.add(removeDirButton);
		//p.setAlignmentX(Component.RIGHT_ALIGNMENT);
		p.add(addDirButton);
		prefPane.add(p);
		
		p = new JPanel (new BorderLayout());
		final JButton cancelButton = new JButton ("Cancel");
		cancelButton.addActionListener(new ActionListener () {
			public void actionPerformed (ActionEvent e) {
				dispose();
			}
		});
		JButton applyButton = new JButton ("Apply Settings");
		applyButton.addActionListener(new ActionListener () {
			public void actionPerformed(ActionEvent arg0) {
				savePreferencesValues();
				dispose();
			}
		});
		p.add( (cancelButton), BorderLayout.WEST);
		p.add( (applyButton), BorderLayout.EAST);
		
		
		// Set the textfields
		if (ConfigDataHolder.existsConfigFile()){
			_irosTextField.setText(ConfigDataHolder.getIrosLocation());
			_jmdnsTextField.setText(ConfigDataHolder.getJmdnsLocation());
		}
		
		prefPane.add(p);
		prefPane.add(new JPanel()); // Dummy Panel to increase distance to the bottom
		prefPane.doLayout();
		prefPane.updateUI();
		
		preferencesFrame.add(prefPane, BorderLayout.CENTER);
		add(preferencesFrame);
		pack();
		setResizable(false);
		setAlwaysOnTop(true);
		setLocationRelativeTo(null);
		setVisible(true);
	}
	
	private void savePreferencesValues () {
		//File configFile = new File("configStarter.xml");
		try {
			String path = System.getProperty("user.home");
        		if      (System.getProperty("os.name").contains("Mac"))
        				path = path+"/Library/iStuff/";
        		else if (System.getProperty("os.name").contains("Linux"))
        				path = path+"/.iStuff/";
        		else		path = path+"\\iStuff\\";
        		File configFile = new File(path+"configStarter.xml");
			
			Element root = new Element ("Configuration");
			
			Document configDoc = new Document(root);
			// Now add all the settings:
			root.addContent(new Element ("Libraries"));
			root.addContent(new Element ("SearchDirectories"));
			
			Element libraries =  root.getChild("Libraries");
			libraries.addContent((new Element ("iROS")).addContent(_irosTextField.getText()));
			libraries.addContent((new Element ("JmDNS")).addContent(_jmdnsTextField.getText()));
			
			// Now add the search directories list:
			Element searchDirs = root.getChild("SearchDirectories");
			for (int i=0; i < _proxyDirsListModel.size(); i++){
				searchDirs.addContent((new Element("directory")).addContent(_proxyDirsListModel.get(i).toString()));
			}
			// Save the file
		     XMLOutputter outputter = new XMLOutputter(Format.getPrettyFormat());
		     FileWriter writer = new FileWriter(configFile);
		     outputter.output(configDoc,writer);
		      writer.close();
		      JOptionPane.showMessageDialog(this,"Your settings were saved and will /n" +
		      		"be applied at the next start of the application");
		} catch (IOException e) {
			JOptionPane.showMessageDialog(this,"There was a problem writing the config file. \n" +
					"Maybe the directory is write protected?");
		}
	}
	
	private Component getInstance() {
		return this;
	}

}
