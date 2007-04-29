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
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

//!  ConfigureDialog class is a Configuration GUI for "Particle" sensor board
/*!  ConfigureDialog class generates a Dialog box when the "Configure Particle"
		 button is clicked on the Framework GUI.
*/

public class ConfigureDialog extends JDialog{

    Framework main;
    boolean cancelled = false;
    JButton btnCancel = new JButton();
    JButton btnOK = new JButton();
    JCheckBox chkAccXY = new JCheckBox();
    JCheckBox chkAccZ = new JCheckBox();
    JCheckBox chkAudio = new JCheckBox();
    JCheckBox chkLight = new JCheckBox();
    JCheckBox chkALight = new JCheckBox();
    JCheckBox chkForce = new JCheckBox();
    JCheckBox chkTemp = new JCheckBox();
    JCheckBox chkVoltage = new JCheckBox();
    JLabel lblSensors = new JLabel();
    JLabel lblRate = new JLabel();
    JComboBox cmbRates[] = new JComboBox[8];
    JLabel lblMs[] = new JLabel[8];

    static
    {
            System.loadLibrary("particleJava");
    }

    public ConfigureDialog(Framework f) {
        try {
            main = f;
            init();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

  	//! Initializes the GUI
		/*! This method is called by the Framework constructor to contruct the GUI
		*/
	
    private void init() throws Exception {
        this.setDefaultCloseOperation(this.HIDE_ON_CLOSE);
        this.setModal(true);
        this.setTitle("Configure Particle");
        this.setBounds(main.getX()+50,main.getY()+50,400,400);
        this.getContentPane().setLayout(null);
        btnCancel.setBounds(new Rectangle(228, 313, 75, 27));
        btnCancel.setActionCommand("jbtnCancel");
        btnCancel.setText("Cancel");
        btnCancel.addActionListener(new ConfigureDialog_btnCancel_actionAdapter(this));
        btnOK.setActionCommand("jbtnOK");
        btnOK.setBounds(new Rectangle(86, 313, 75, 27));
        btnOK.setText("OK");
        btnOK.addActionListener(new ConfigureDialog_btnOK_actionAdapter(this));
        chkAccXY.setText("Acceleration X/Y");
        chkAccXY.setBounds(new Rectangle(22, 44, 133, 23));
        chkAccZ.setText("Acceleration Z");
        chkAccZ.setBounds(new Rectangle(22, 76, 132, 23));
        chkAudio.setText("Audio");
        chkAudio.setBounds(new Rectangle(22, 108, 83, 23));
        chkLight.setText("Light");
        chkLight.setBounds(new Rectangle(22, 140, 83, 23));
        chkALight.setText("Ambientlight");
        chkALight.setBounds(new Rectangle(22, 172, 144, 23));
        chkForce.setText("Force");
        chkForce.setBounds(new Rectangle(22, 204, 83, 23));
        chkTemp.setText("Temparature");
        chkTemp.setBounds(new Rectangle(22, 236, 131, 23));
        chkVoltage.setText("Voltage");
        chkVoltage.setBounds(new Rectangle(22, 268, 83, 23));
        lblSensors.setFont(new java.awt.Font("Dialog", Font.BOLD, 12));
        lblSensors.setHorizontalAlignment(SwingConstants.CENTER);
        lblSensors.setText("Sensors");
        lblSensors.setBounds(new Rectangle(31, 9, 101, 24));
        lblRate.setFont(new java.awt.Font("Dialog", Font.BOLD, 12));
        lblRate.setHorizontalAlignment(SwingConstants.CENTER);
        lblRate.setText("Rate");
        lblRate.setBounds(new Rectangle(223, 9, 101, 24));

        for(int i=0;i<cmbRates.length;i++)
        {
            cmbRates[i] = new JComboBox();
            lblMs[i] = new JLabel("ms");
            cmbRates[i].setBounds(new Rectangle(245, 44 +(i*32), 64, 18));	//increase the location of combo boxes by a factor of 32 on Y-Axis
            lblMs[i].setBounds(new Rectangle(310,44 +(i*32), 64, 18));

            int val = 13;
            for(int j=1;j<=16;j++)
            {
                cmbRates[i].addItem(new Integer(val).toString());
                val = val*2;
            }
            this.getContentPane().add(cmbRates[i]);
            this.getContentPane().add(lblMs[i]);
        }
        this.getContentPane().add(btnOK);
        this.getContentPane().add(btnCancel);
        this.getContentPane().add(chkAccXY);
        this.getContentPane().add(chkAccZ);
        this.getContentPane().add(chkAudio);
        this.getContentPane().add(chkLight);
        this.getContentPane().add(chkALight);
        this.getContentPane().add(chkForce);
        this.getContentPane().add(chkTemp);
        this.getContentPane().add(chkVoltage);
        this.getContentPane().add(lblSensors);
        this.getContentPane().add(lblRate);
        this.setVisible(true);
    }

		//! Exits the configuration dialog by hiding it
		/*! This method is called when the Cancel button on the GUI is clicked. It exits
				the dialog by hiding it.

				\param e as an ActionEvent object. This parameter is never used.
		*/
    public void btnCancel_actionPerformed(ActionEvent e)
    {
        cancelled = true;
        this.setVisible(false);	//hide the dialog
    }

    public void btnOK_actionPerformed(ActionEvent e)
    {
            this.setVisible(false);	//hide the dialog
    }

}

//!  Helper class for the ConfigureDialog class.
/*!  This class a helper class for the ConfigureDialog which implements
	 	 the action adapter for the "Cancel" button on the GUI.
 */

class ConfigureDialog_btnCancel_actionAdapter implements ActionListener {
    private ConfigureDialog adaptee;
    ConfigureDialog_btnCancel_actionAdapter(ConfigureDialog adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.btnCancel_actionPerformed(e);
    }
}

//!  Helper class for the ConfigureDialog class.
/*!  This class a helper class for the ConfigureDialog which implements
	 	 the action adapter for the "OK" button on the GUI.
 */

class ConfigureDialog_btnOK_actionAdapter implements ActionListener {
    private ConfigureDialog adaptee;
    ConfigureDialog_btnOK_actionAdapter(ConfigureDialog adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.btnOK_actionPerformed(e);
    }
}
