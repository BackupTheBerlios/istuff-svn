//
//  GameController.java
//  
//  Created by Andy Szybalski on Sat Feb 01 2003.
//
// JXInput is a bridge between DirectX and Java:
// http://www.hardcode.de/jxinput/

package iwork.gamecontroller;

import de.hardcode.jxinput.*;
import de.hardcode.jxinput.directinput.*;
import de.hardcode.jxinput.event.*;
import de.hardcode.jxinput.test.*;

import iwork.IWRoomConfigValues;
import iwork.eheap2.*;
import iwork.eheap2.EventHeap;
import iwork.gamecontroller.JoystickTableModel;

import javax.swing.*;
import javax.swing.table.*;
import javax.swing.event.*;
import javax.swing.border.*;

import java.awt.Toolkit;
import java.awt.Container;
import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.Dimension;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.WindowEvent;
import java.awt.event.WindowAdapter;
import java.lang.Math;
import java.util.Timer;
import iwork.util.timer.*; // for HiResTimer class

import java.text.DateFormat;


//import javax.jnlp.BasicService;

import java.io.*;

import java.util.*;
import java.net.URL;


public class GameController extends JFrame {
    public File propsFile;
    public static final int DEFAULT_TRIGGER_INTERVAL = 200;
    public static HiResTimer hiResTimer = null;
	
    public ArrayList joysticks = new ArrayList();
    public Properties props = new Properties();
    public static final boolean BENCHMARK = true;
    public static double triggerTime = 0;

    private static final String DEFAULT_MACHINE_STRING = "iw-room2.stanford.edu";
    private static final String DEFAULT_PORT_STRING = "4535";

    private static final String DEFAULT_MACHINE = "iw-room2.stanford.edu";
    private static final int DEFAULT_PORT = IWRoomConfigValues.IROOM_DEFAULT_PORT;
    SimpleEventHandler eventHandler = null;
    private static final int SERVER_TIMEOUT = 10000; // 10 sec timeout

    private final JButton startButton = new JButton("Connect");
    private final JButton stopButton = new JButton("Disconnect");
    private JTextField hostName = new JTextField();
    private JTextField hostPort = new JTextField();
    private final JLabel status = new JLabel("Specify a server and click Start");

    private final JFrame inspectorFrame = new JFrame("Joystick Inspector");
    private final JoystickInspectorModel inspectorModel = new JoystickInspectorModel();
    private final JTable inspectorTable = new JTable(inspectorModel);
    private int triggerInterval;
    private JoystickTableModel jTableModel = new JoystickTableModel(this);

    int numAxes, numDirectionals, numButtons, i,j;
    int numEventsSent = 0;
    private final JCheckBox printEvents = new JCheckBox("Print events to console", false);
    public Timer timer = new Timer();
    
    public GameController(int triggerInterval) {		this.triggerInterval = triggerInterval;
        this.setTitle("Game Controller");
        JXInputEventManager.setTriggerIntervall(0); // trigger manually

        if( BENCHMARK ){
            try{
                hiResTimer = new HiResTimer();
                if( hiResTimer.isHighResTimerAvailable() )
                    System.out.println("high res timer is available" );
            }catch( UnsatisfiedLinkError ex ){
                /* ignore unsatisfied link */
                hiResTimer = null;
                System.out.println("Unable to find HiResTimer library, using standard timer");
                System.out.println("Library path: " + System.getProperties().get("java.library.path") );
            }
        }        
        
        propsFile = new File("GameController.prefs");
        try {
            loadProperties();
        } catch (FileNotFoundException ex) {
            System.out.println("No properties file found.");
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        
        String prevHostName = props.getProperty("HostName", DEFAULT_MACHINE_STRING);
        String prevHostPort = props.getProperty("HostPort", DEFAULT_PORT_STRING);
        hostName.setText(prevHostName);
        hostPort.setText(prevHostPort);


        // need thread to call JXInputManager.updateFeatures()?
        //int numDevices = DirectInputDevice.getNumberOfDevices();
        int numDevices = JXInputManager.getNumberOfDevices();
        if (numDevices == 0) {
            System.out.println("Error: no DirectInput devices available.");
            //System.exit(-1);
        }
        
        Joystick joystick;
        

        //DirectInputDevice.update(); // not sure if necessary
        
        for (i = 0; i < numDevices; i++) {
            JXInputDevice dev = JXInputManager.getJXInputDevice( i );
            if ( null != dev )
            {
                    //
                    // Setup an own panel for each device.
                    //
                    //JPanel panel = new JXInputDevicePanel( dev );
                    //mDevicesTabbedPane.addTab( dev.getName(), panel );
                    joystick = new Joystick(i, this, dev);
                    if (joystick.hasFeatures()) {
                            joysticks.add(joystick);
                            jTableModel.fireTableDataChanged();
                    }            
            }
			
            //joystick = new Joystick(i, this);

        }
        
        //Joystick debugJoy = new Joystick(0, this); // dummy joystick
        
        initMenuBar();
        initInterface();
        initInspector();

        timer.schedule(new UpdateAllTask(), 0, this.triggerInterval);
    }
    
    private void initMenuBar() {
        JMenuBar menuBar = new JMenuBar();
        this.setJMenuBar(menuBar);
        
        KeyStroke stroke;
        Toolkit tk = Toolkit.getDefaultToolkit();
        int mask = tk.getMenuShortcutKeyMask();
                
        JMenu fileMenu = new JMenu("File");
        JMenuItem quitMenuItem = new JMenuItem("Quit");
        
        stroke = KeyStroke.getKeyStroke(new Character('Q'), mask);
        quitMenuItem.setAccelerator(stroke);
                
        menuBar.add(fileMenu);
        fileMenu.add(quitMenuItem);
        

        JMenu helpMenu = new JMenu("Help");
        
        JMenuItem aboutLogger = new JMenuItem("About GameController...");
        aboutLogger.addActionListener(new AboutBoxAction());
        stroke = KeyStroke.getKeyStroke(new Character('?'), mask);
        aboutLogger.setAccelerator(stroke);
        //JMenuItem webPage = new JMenuItem("Open Web Page...");
        //webPage.addActionListener(new BrowserAction());
        menuBar.add(helpMenu);
        helpMenu.add(aboutLogger);
        //helpMenu.add(webPage);
    }
    
    private void initInspector() {
        inspectorFrame.setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
        inspectorFrame.getContentPane().setLayout(new BorderLayout());
        
        JScrollPane inspectorScrollPane = new JScrollPane(inspectorTable);
        Box southBox = Box.createHorizontalBox();
        //southBox.add(exportInspectorButton);
        inspectorFrame.getContentPane().add(southBox, BorderLayout.SOUTH);
        //exportInspectorButton.addActionListener(new InspectorExportAction());
        //exportInspectorButton.setBorder(new EmptyBorder(5, 5, 5, 5));
        
        Box inspectorBox = Box.createHorizontalBox();
        inspectorBox.setBorder(new EmptyBorder(5, 5, 5, 5));
        inspectorBox.add(inspectorScrollPane);
        inspectorFrame.getContentPane().add(inspectorBox, BorderLayout.CENTER);        
        inspectorFrame.setSize(new Dimension(400,200));
        inspectorFrame.setVisible(true);
        inspectorFrame.setLocationRelativeTo(this);	// puts the inspector window to the right of main window
        this.toFront();					// brings the main window to front.
        
    }


    private void initInterface() {
        this.setSize(450, 350);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.addWindowListener(new GameControllerWindowAdapter());
        
        status.setText("Enter a server and push Start");
        status.setBorder(new EmptyBorder(5, 5, 5, 5));
        
        Container contentPane = this.getContentPane();
        contentPane.setLayout(new BorderLayout());
        
        JPanel joysticksPanel = new JPanel();
        joysticksPanel.setLayout(new BorderLayout());
        
        JTabbedPane tabbedPane = new JTabbedPane();
        tabbedPane.addTab("Joysticks", joysticksPanel);

        Box northBox = Box.createHorizontalBox();
        Box serverPortBox = Box.createVerticalBox();
        Box northServerBox = Box.createHorizontalBox();
        Box northPortBox = Box.createHorizontalBox();
        Box northButtonsBox = Box.createVerticalBox();
        serverPortBox.add(northServerBox);
        serverPortBox.add(northPortBox);
        
        northBox.add(serverPortBox);
        northBox.add(northButtonsBox);
        
        northServerBox.add(new JLabel("EventHeap server: "));
        northServerBox.add(hostName);
        northServerBox.setBorder(new EmptyBorder(5, 5, 5, 5));
        
        northPortBox.add(new JLabel("Port: "));
        northPortBox.add(hostPort);
        northPortBox.setBorder(new EmptyBorder(5, 5, 5, 5));

        northButtonsBox.add(startButton);
        northButtonsBox.add(stopButton);
        
        JTable jTable = new JTable(jTableModel);
        JScrollPane jScrollPane = new JScrollPane(jTable);
        jTable.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        ListSelectionModel rowSM = jTable.getSelectionModel();
        rowSM.addListSelectionListener(new ListSelectionListener() {
            public void valueChanged(ListSelectionEvent e) {
                //Ignore extra messages.
                if (e.getValueIsAdjusting()) return;
                
                ListSelectionModel lsm =
                    (ListSelectionModel)e.getSource();
                if (lsm.isSelectionEmpty()) {
                    inspectorModel.setJoystick(null);
                    //exportInspectorButton.setEnabled(false);
                } else {
                    int selectedRow = lsm.getMinSelectionIndex();
                    Joystick selectedJoystick = (Joystick)joysticks.get(selectedRow);
                    inspectorModel.setJoystick(selectedJoystick);
                    //exportInspectorButton.setEnabled(true);
                }
            }
        });

        
        Box centerBox = Box.createVerticalBox();
        centerBox.add(jScrollPane);
        
        JButton savePropsButton = new JButton("Save Names");
        Box joySouthBox = Box.createHorizontalBox();
        joySouthBox.add(savePropsButton);
        joySouthBox.add(printEvents);
        
        joysticksPanel.add(centerBox, BorderLayout.CENTER);
        joysticksPanel.add(joySouthBox, BorderLayout.SOUTH);
        
        contentPane.add(northBox, BorderLayout.NORTH);
        contentPane.add(tabbedPane, BorderLayout.CENTER);
        contentPane.add(status, BorderLayout.SOUTH);
        
        savePropsButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    saveProperties();
                } catch (Exception ex) {
                    ex.printStackTrace();
                }
            }
        });
        
        startButton.addActionListener( new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                status.setText("Connecting to server...");
                eventHandler = new SimpleEventHandler("GameController", hostName.getText(), Integer.parseInt(hostPort.getText()));
                boolean success = eventHandler.validEventHeap();
                if (success) {
                    status.setText("Connected to Event Heap server version " + eventHandler.getServerVersion() + " on " + eventHandler.getMachine());
                    startButton.setEnabled(false);
                    stopButton.setEnabled(true);
                    hostName.setEnabled(false);
                    hostPort.setEnabled(false);
                    
                    // next startup, host and port will be configured to last successful value
                    props.setProperty("HostName", hostName.getText());
                    props.setProperty("HostPort", hostPort.getText());
                } else {
                    status.setText("Unable to find Event Heap server at " + hostName.getText());
                    eventHandler = null;
                }
            }
        });
        
        stopButton.setEnabled(false);
        stopButton.addActionListener( new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                eventHandler.deregister();
                eventHandler = null;
                stopButton.setEnabled(false);
                startButton.setEnabled(true);
                hostName.setEnabled(true);
                hostPort.setEnabled(true);
                status.setText("Enter a server and push Start");
            }
        });
        
        
        this.setVisible(true);
    }
    
    public void sendEventNow(Event ev) {
        if (eventHandler != null) {
            eventHandler.sendEventNow(ev);
        }
    }

    public void sendEventAndWait(Event ev) {
        if (eventHandler != null) {
            eventHandler.sendEventAndWait(ev);
        }
    }    

    private class AboutBoxAction extends AbstractAction implements Action {
        public void actionPerformed(ActionEvent e) {
            JOptionPane.showMessageDialog(GameController.this,
                                          "Game Controller 0.72 for Windows.\n(revised 9 July 2003)\nSends iStuff events from any DirectInput joystick.\nRequires Windows 98 or later, DirectX 8 or later, and JXInput 0.33.\nFor use with iROS.");
        }
    }
    
    public class GameControllerWindowAdapter extends WindowAdapter {
        public void windowClosing(WindowEvent e) {
            try {
                saveProperties();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
    }
    
    public void loadProperties() throws FileNotFoundException, IOException {
        if (propsFile != null) {
            FileInputStream in = new FileInputStream(propsFile);
            props.load(in);
            in.close();
        } else {
            System.out.println("Error: can't load properties. propsFile == null");
        }
    }
    
    public void saveProperties() throws FileNotFoundException, IOException {
        if (propsFile != null) {
            FileOutputStream out = new FileOutputStream(propsFile);
            props.store(out, "Game Controller Properties");
            out.close();
        } else {
            System.out.println("Error: can't save properties. propsFile == null");
        }    }
    

    public static void main(String args[]) {
		int triggerInterval = DEFAULT_TRIGGER_INTERVAL;
		try {			if (args.length > 0) {				triggerInterval = Integer.parseInt(args[0]) ;			}		} catch (NumberFormatException ex) {			ex.printStackTrace();		}
        new GameController(triggerInterval);
    }

    public class UpdateAllTask extends TimerTask {
        public void run() {
            if (BENCHMARK) {
                triggerTime = hiResTimer.startTiming();
            }
            JXInputManager.updateFeatures();
            Iterator it = joysticks.iterator();
            while (it.hasNext()) {
                Joystick j = (Joystick)it.next();
                j.sendEvent();
            }
        }
    }
    
}

