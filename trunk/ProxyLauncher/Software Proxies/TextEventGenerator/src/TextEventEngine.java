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
 *
 * Version:	  1.0
 */

import javax.swing.*;
import java.awt.*;
import java.io.*;
import java.awt.event.KeyListener;
import java.awt.event.KeyEvent;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import iwork.eheap2.*;


//!  TextEventEngine posts Keys typed into its Text field on the "Event Heap".
/*!  The TextEventEngine class communicates with the "Event Heap". This class
	 produces a GUI which consists of a text field. Whatever is typed in this
	 text field is posed onto the "Event Heap" as a Text Events.

 */

public class TextEventEngine extends JFrame{

    private JLabel lblText = new JLabel();
    private JButton btnExit = new JButton();
    private JLabel lblTitle = new JLabel();
    private JTextArea txtText = new JTextArea();
    private JScrollPane spnText;
    private ImagePanel imgI10;
    private EventHeap eventHeap;
    private String proxyID;

    //! TextEventEngine class constructor
	/*! The constructor constructs the GUI for the TextEventEngine, initializes
		the eventHeap and proxyID class variables.

		\param ip as a String. Specifies the IP address of the "Event Heap".
		\param proxyID as a String. Specifies the proxy ID to be used while
			   posting Events and to be checked while receiving events.
	*/

    public TextEventEngine(String ip, String proxyID) {
        try {
            eventHeap = new EventHeap(ip);
            this.proxyID = proxyID;
            init();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }


	//! Initializes the GUI
	/*! This method is called by the TextEventEngine constructor to contruct the GUI
	*/


    private void init() throws Exception {

        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension scrnsize = toolkit.getScreenSize();

        this.setBounds((int)scrnsize.width/4,(int)scrnsize.height/5,500,500); //place the GUI in the middle of the screen
        this.setDefaultCloseOperation(EXIT_ON_CLOSE); //Exit the application on clicking the red cross on the top right corner
        this.setIconImage(null);
        this.setResizable(false);
        this.setTitle("Text Event Engine");
        this.getContentPane().setLayout(null);

        btnExit.setBounds(new Rectangle(190, 400, 138, 29));
        btnExit.setText("Exit");
        btnExit.addActionListener(new TextEventEngine_btnExit_actionAdapter(this)); //use a helper class to receive exit button events

        lblText.setText("Enter the text:");
        lblText.setBounds(new Rectangle(12, 100, 113, 21));

        txtText.setLineWrap(true);
        txtText.addKeyListener(new TextEventEngine_txtText_documentAdapter(this)); //use a helper class to receive key events from the

        spnText = new JScrollPane(txtText);	//create a scroll pane for the text field
        spnText.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        spnText.setBounds(new Rectangle(12, 130, 300, 250));

        lblTitle.setFont(new java.awt.Font("Times New Roman", Font.BOLD, 20));
        lblTitle.setHorizontalAlignment(SwingConstants.CENTER);
        lblTitle.setText("Text Event Engine");
        lblTitle.setBounds(new Rectangle(126, 8, 234, 28));

        imgI10 = new ImagePanel("img/logo_i10.gif"); //reading i10 logo
        imgI10.setBounds(350,0,180,80);

		//add all the components to the GUI
        this.getContentPane().add(imgI10);
        this.getContentPane().add(btnExit);
        this.getContentPane().add(lblTitle);
        this.getContentPane().add(lblText);
        this.getContentPane().add(spnText);
        this.setVisible(true);
    }

    public static void main(String args[])
    {
		if(args.length == 1)
			new TextEventEngine (args[0],"");
		else if (args.length > 1)
			new TextEventEngine (args[0], args[1]);
		 else
        	System.out.println("Usage: java TextEventEngine <Event Heap IP> [ProxyID]" +
					"[ProxyID] = an optional parameter to be checked in the events received and sent in events generated e.g. proxy1\n");
    }


    //! Exits the application
	/*! This method is called when the Exit button on the GUI is hit. It exits
		the application.

		\param e as an ActionEvent object. This parameter is never used.
	*/

    public void btnExit_actionPerformed(ActionEvent e)
    {
        System.exit(0);
    }

    //! Posts the typed key onto the "Event Heap"
	/*! This method is called whenever a key is typed into the text field.
		The ascii of the key is extracted and posted onto the "Event Heap"
		as a Text Event.

		\param e as an KeyEvent object. Contains the information related
			   to the typed key.
	*/

    public void txtText_keyTyped(KeyEvent e)
    {
		Integer code = new Integer(e.getKeyChar());	//get the ascii code of the character typed into the text field
		System.out.println("Sent Code = " + code);

    	try
    	{
			iwork.eheap2.Event event = new iwork.eheap2.Event("TextEvent"); //create a new event
	      	event.addField("Character",code);	//add the ascii code to the event
	      	event.addField("ProxyID", proxyID);	//add the proxy ID to the event
	      	if (eventHeap.isConnected()) {
			eventHeap.putEvent(event);			//publish the event onto the "Event Heap"
			}
      	}
      	catch(Exception ex)
      	{
      		ex.printStackTrace();
      	}
    }
}


//!  Helper class for TextEventEngine class.
/*!  This class a helper class for TextEventEngine which implements
	 the action adapter for the Exit button on the GUI.
 */

class TextEventEngine_btnExit_actionAdapter implements ActionListener {
    private TextEventEngine adaptee;
    TextEventEngine_btnExit_actionAdapter(TextEventEngine adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.btnExit_actionPerformed(e);
    }
}

//!  Helper class for TextEventEngine class.
/*!  This class a helper class for TextEventEngine which implements
	 the keyListener. This class passes the typed keys into the text
	 field to the TextEventEngine class.
 */

class TextEventEngine_txtText_documentAdapter implements KeyListener {
    private TextEventEngine adaptee;
    TextEventEngine_txtText_documentAdapter(TextEventEngine adaptee) {
        this.adaptee = adaptee;
    }

     public void keyPressed(KeyEvent e)
     {}
     public void keyReleased(KeyEvent e)
     {}
     public void keyTyped(KeyEvent e)
     {
     	adaptee.txtText_keyTyped(e);
     }
}
