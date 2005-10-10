import javax.swing.*;


import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ConfigureDialog extends JDialog{

    static
    {
            System.loadLibrary("particleJava");
    }

    public ConfigureDialog(Framework f) {
        try {
            main = f;
            jbInit();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    private void jbInit() throws Exception {
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
            cmbRates[i].setBounds(new Rectangle(245, 44 +(i*32), 64, 18));
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

    public void btnCancel_actionPerformed(ActionEvent e)
    {
        cancelled = true;
        this.setVisible(false);
    }

    public void btnOK_actionPerformed(ActionEvent e)
    {
            this.setVisible(false);
    }

}


class ConfigureDialog_btnCancel_actionAdapter implements ActionListener {
    private ConfigureDialog adaptee;
    ConfigureDialog_btnCancel_actionAdapter(ConfigureDialog adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.btnCancel_actionPerformed(e);
    }
}

class ConfigureDialog_btnOK_actionAdapter implements ActionListener {
    private ConfigureDialog adaptee;
    ConfigureDialog_btnOK_actionAdapter(ConfigureDialog adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.btnOK_actionPerformed(e);
    }
}
