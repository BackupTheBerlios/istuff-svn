/*
 * Copyright (c) 2006
 * Media informatics Department
 * RWTH Aachen Germany
 * http://media.informatik.rwth-aachen.de
 *
 * Redistribution and use of the source code and binary, with or without
 * modification, are permitted under OPI Artistic License
 * (http://www.opensource.org/licenses/artistic-license.php) provided that
 * the source code retains the above copyright notice and the following
 * disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors:	  Faraz Ahmed Memon
 *			  Tico Ballagas
 *
 * Version:	  1.0
 */

import javax.swing.*;
import java.awt.*;
import javax.imageio.*;
import java.io.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.util.Vector;

//!  Framework class is a proxy program to communicate with the "Smart-Its" and the "Event Heap".
/*!  The four main functionalities of this class are:
  		-# Create a GUI for the "Smart-Its" proxy.
  		-# Use Scanner class to scan the "Smart-Its" availble in the network.
  		-# Use ConfigureDialog class to configure a particular "Smart-Its".
  		-# Use EventLauncher class to post the "Smart-Its" sensor values as events onto the "Event Heap".
*/

public class Framework extends JFrame{
	private String proxyID;
    String eventHeapIp;		//"Event Heap" class object to post events
    Scanner scan;			//"Scanner" class object to scan for "Particles (Smart-Its)" in the network
    EventLauncher eventLauncher;	//"EventLauncher" to post "Particle" sensor values as events onto the "Event Heap"

    JLabel lblParticles = new JLabel();
    JLabel lblEvents = new JLabel();
    JButton btnScan = new JButton();
    JButton btnConfigure = new JButton();
    JButton btnStart = new JButton();
    JButton btnStop = new JButton();
    JButton btnExit = new JButton();
    JLabel lblTitle = new JLabel();
    JScrollPane scPnParticles = new JScrollPane();
    DefaultListModel listmodelParticles = new DefaultListModel();
    DefaultListModel listmodelEvents = new DefaultListModel();
    JList lstParticles = new JList(listmodelParticles);
    ImagePanel imgI10;
    JScrollPane scPnEvents = new JScrollPane();
    JList lstEvents = new JList(listmodelEvents);
    JButton btnAdd = new JButton();
    Vector configuredParticles = new Vector();

    //! Framework class constructor
	/*! The constructor take "Event Heap" IP address and the current
		proxy Id as an input parameters. The constructor initializes
		the Particle Framework GUI and the "Event Heap".

		\param ip as a String. Specifies the IP address of the "Event Heap".
		\param proxyID as a String. Specifies the proxy ID to be used while
			   posting Events and to be checked while receiving events.
	*/

    public Framework(String ip, String proxyID) {
        try {
            init();
            this.eventHeapIp = ip;
            this.proxyID = proxyID;
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    //! Initializes the GUI
		/*! This method is called by the Framework constructor to contruct the GUI
	*/

    private void init() throws Exception {

        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension scrnsize = toolkit.getScreenSize();

        this.setBounds((int)scrnsize.width/4,(int)scrnsize.height/5,500,500);	//show the GUI in the middle of the screen
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);	//Exit the application on clicking the red cross on the top right corner
        this.setIconImage(null);
        this.setResizable(false);
        this.setTitle("Particle Framework");
        this.getContentPane().setLayout(null);

        lblEvents.setText("Events :");							//A label
        lblEvents.setBounds(new Rectangle(14, 292, 136, 20));

        btnScan.setBounds(new Rectangle(330, 108, 138, 29));	//A button with "Scan Network" label
        btnScan.setText("Scan Network");
        btnScan.addActionListener(new Framework_btnScan_actionAdapter(this));	//call to helper class to receive events related to "Scan Network" button

        btnConfigure.setBounds(new Rectangle(330, 145, 138, 29));	//A button with "Configure Particle" label
        btnConfigure.setText("Configure Particle");
        btnConfigure.addActionListener(new Framework_btnConfigure_actionAdapter(this));	//call to helper class to receive events related to "Configure Particle" button
        btnConfigure.setEnabled(false);

        btnStart.setBounds(new Rectangle(330, 183, 138, 29));
        btnStart.setText("Start Framework");
        btnStart.addActionListener(new Framework_btnStart_actionAdapter(this));	//call to helper class to receive events related to "Start Framework" button
        btnStart.setEnabled(false);

        btnStop.setBounds(new Rectangle(330, 219, 138, 29));
        btnStop.setText("Stop Framework");
        btnStop.addActionListener(new Framework_btnStop_actionAdapter(this));	//call to helper class to receive events related to "Stop Framework" button
        btnStop.setEnabled(false);

        btnExit.setBounds(new Rectangle(330, 256, 138, 29));
        btnExit.setText("Exit");
        btnExit.addActionListener(new Framework_btnExit_actionAdapter(this));	//call to helper class to receive events related to "Exit" button

        btnAdd.setBounds(new Rectangle(131, 278, 58, 20));
        btnAdd.setActionCommand("btnAdd");
        btnAdd.setText("Add");
        btnAdd.addActionListener(new Framework_btnAdd_actionAdapter(this));	//call to helper class to receive events related to "Add" button

        lblParticles.setText("Particle List:");						//label for "Particle" id list
        lblParticles.setBounds(new Rectangle(12, 40, 113, 21));

        lblTitle.setFont(new java.awt.Font("Times New Roman", Font.BOLD, 20));
        lblTitle.setHorizontalAlignment(SwingConstants.CENTER);
        lblTitle.setText("Particle Framework");
        lblTitle.setBounds(new Rectangle(126, 8, 234, 28));

        imgI10 = new ImagePanel("src/img/logo_i10.gif");			//i10 logo image
        imgI10.setBounds(350,0,180,80);

        scPnParticles.setBounds(new Rectangle(13, 63, 176, 214));

        lstParticles.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);		//list of "Particle" ids
        lstParticles.addListSelectionListener(new Framework_particle_ListAdapter(this));

        scPnEvents.setBounds(new Rectangle(13, 317, 371, 131));

        //add all the components to the GUI

        this.getContentPane().add(lblEvents);
        this.getContentPane().add(imgI10);
        this.getContentPane().add(btnScan);
        this.getContentPane().add(btnConfigure);
        this.getContentPane().add(btnStart);
        this.getContentPane().add(btnStop);
        this.getContentPane().add(btnExit);
        this.getContentPane().add(lblTitle);
        this.getContentPane().add(scPnParticles);
        scPnParticles.getViewport().add(lstParticles);
        scPnEvents.getViewport().add(lstEvents);
        this.getContentPane().add(lblParticles);
        this.getContentPane().add(scPnEvents);
        this.getContentPane().add(btnAdd);
        this.setVisible(true);
    }

    public static void main(String args[])
    {
        Framework pf;

        if(args.length == 1)
            pf = new Framework(args[0],"");
        else if (args.length >=2)
        		pf = new Framework(args[0], args[1]);
        else
            System.out.println("Usage: Framework <Event Heap IP Address> [ProxyID]" +
						"[ProxyID] = an optional parameter to be checked in the events received and sent in events generated e.g. proxy1\n");
    }

    //! Exits the application
	/*! This method is called when the Exit button on the GUI is clicked. It exits
		the application.

		\param e as an ActionEvent object. This parameter is never used.
	*/

    public void btnExit_actionPerformed(ActionEvent e)
    {
        System.exit(0);
    }

    //! Starts the Scanner for network scanning of Particles
	/*! This method is called when the "Scan Network" button on the GUI is hit. It
		constructs an Object of Scanner class and starts scanning the network
		for "Particles" in a separate thread

		\param e as an ActionEvent object. This parameter is never used.
	*/

    public void btnScan_actionPerformed(ActionEvent e)
    {
        scan = new Scanner(this);
        Thread t = new Thread(scan);
        listmodelEvents.addElement("Scanning Network...");
        t.start();
    }

	//! Starts the configuration dialog for configuring "Particle" sensor module
	/*! This method is called when the "Configure Particle" button on the GUI is hit.
		It constructs an Object of ConfigureDialog class and starts a dialog box using
		which one can configure "Particle" sensor module.

		\param e as an ActionEvent object. This parameter is never used.
	*/

    public void btnConfigure_actionPerformed(ActionEvent e)
    {
        ConfigureDialog cd = new ConfigureDialog(this);
        if (cd.cancelled == false)
        {
              this.listmodelEvents.addElement("Starting Configuration...");				//list where you can see the output from the particle framework
              SensorConfig cf = new SensorConfig(this,lstParticles.getSelectedValue(),cd);
              cf.startConfiguration();

              if (cf.isSuccessful())	//check for success after the configuration is complete
              {
                   this.listmodelEvents.addElement("Configuration was successfull");
                   this.configuredParticles.add(lstParticles.getSelectedValue());	//maintain a list of all the configured "Particles"
                   this.btnStart.setEnabled(true);	//enable the start button on the GUI after even a single "Particle" is configured
              }
              else
                   this.listmodelEvents.addElement("Configuration failed");
        }

    }


	//! Allows to add a "Particle" manually to availble Particles list on the GUI
	/*! This method is called when the "Add" button just below the "Particle List"on
		the GUI is hit. It constructs a dialog box which can be used to manually add
		a particle to the "Particle List".

		\param e as an ActionEvent object. This parameter is never used.
	*/

    public void btnAdd_actionPerformed(ActionEvent e)
    {
        String s = (String)JOptionPane.showInputDialog(this,"Enter a particle Id:\n","Manually Add Particle Id",JOptionPane.PLAIN_MESSAGE,null,null,"255.255.255.255.255.255.255.255");

        if((s!=null) && (s.length()>0))
            this.listmodelParticles.addElement(s);
    }


	//! Constructs a object of EventLauncher class which starts to post the "Particle" sensor data.
	/*! This method is called when the "Start Framework" button on the GUI is hit. This
		causes the EventLauncher class to start posting sensor values as events from
		"Particles" onto the "Event Heap".

		\param e as an ActionEvent object. This parameter is never used.
	*/

    public void btnStart_actionPerformed(ActionEvent e) {

       eventLauncher = new EventLauncher(configuredParticles,eventHeapIp, proxyID);
       Thread t = new Thread(eventLauncher);	//start the event launcher in a separate thread
       listmodelEvents.addElement("Starting Framework...");
       btnScan.setEnabled(false);	//disable the "Scan Network" button
       btnConfigure.setEnabled(false);	//disable the "Configure Particle" button
       btnStart.setEnabled(false);	//disable the "Start Framework" button
       btnStop.setEnabled(true);	//enable the "Stop Framework" button
       t.start();

    }



	//! Stops the posting of "Particle" sensor data onto the "Event Heap"
	/*! This method is called when the "Stop Framework" button on the GUI is hit.
		It causes the EventLaucher object to stop posting the "Particle" sensor
		data onto the "Event Heap".

		\param e as an ActionEvent object. This parameter is never used.
	*/

    public void btnStop_actionPerformed(ActionEvent e) {

        eventLauncher.stop();
        btnScan.setEnabled(true);
        btnConfigure.setEnabled(true);
        btnStart.setEnabled(true);
        btnStop.setEnabled(false);
        listmodelEvents.addElement("Framework Stopped");

    }


	//! Called whenever the particle list is updated
	/*! This method is called whenever the list of particles is updated.

		\param e as an ListSelectionEvent object. This parameter is never used.
	*/

    public void particleListUpdated(ListSelectionEvent e)
    {
        if(this.lstParticles.getSelectedIndex() == -1) //disable the "Configure Particle" button when some particle is selected
            btnConfigure.setEnabled(false);
        else
            btnConfigure.setEnabled(true); //and enable the "Configure Particle" button when some particle is selected
    }
}


//!  Helper class for the Framework class.
/*!  This class a helper class for the Framework which implements
	 the ListSelectionListener for the "Particle List" inside the
	 Framework class.
 */


class Framework_particle_ListAdapter implements  ListSelectionListener{
    private Framework adaptee;
    Framework_particle_ListAdapter(Framework adaptee) {
        this.adaptee = adaptee;
    }

    public void valueChanged(ListSelectionEvent e) {
        adaptee.particleListUpdated(e);
    }
}

//!  Helper class for the Framework class.
/*!  This class a helper class for the Framework which implements
	 the action adapter for the "Stop Framework" button on the GUI.
 */

class Framework_btnStop_actionAdapter implements ActionListener {
    private Framework adaptee;
    Framework_btnStop_actionAdapter(Framework adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.btnStop_actionPerformed(e);
    }
}


//!  Helper class for the Framework class.
/*!  This class a helper class for the Framework which implements
	 the action adapter for the "Start Framework" button on the GUI.
 */


class Framework_btnStart_actionAdapter implements ActionListener {
    private Framework adaptee;
    Framework_btnStart_actionAdapter(Framework adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.btnStart_actionPerformed(e);
    }
}


//!  Helper class for the Framework class.
/*!  This class a helper class for the Framework which implements
	 the action adapter for the "Configure Particle" button on the GUI.
 */

class Framework_btnConfigure_actionAdapter implements ActionListener {
    private Framework adaptee;
    Framework_btnConfigure_actionAdapter(Framework adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.btnConfigure_actionPerformed(e);
    }
}


//!  Helper class for the Framework class.
/*!  This class a helper class for the Framework which implements
	 the action adapter for the "Scan Network" button on the GUI.
 */


class Framework_btnScan_actionAdapter implements ActionListener {
    private Framework adaptee;
    Framework_btnScan_actionAdapter(Framework adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.btnScan_actionPerformed(e);
    }
}


//!  Helper class for the Framework class.
/*!  This class a helper class for the Framework which implements
	 the action adapter for the Exit button on the GUI.
 */

class Framework_btnExit_actionAdapter implements ActionListener {
    private Framework adaptee;
    Framework_btnExit_actionAdapter(Framework adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.btnExit_actionPerformed(e);
    }
}


//!  Helper class for the Framework class.
/*!  This class a helper class for the Framework which implements
	 the action adapter for the Add button on the GUI.
 */

class Framework_btnAdd_actionAdapter implements ActionListener {
    private Framework adaptee;
    Framework_btnAdd_actionAdapter(Framework adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.btnAdd_actionPerformed(e);
    }
}
