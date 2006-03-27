
import javax.swing.*;
import java.awt.*;
import javax.imageio.*;
import java.io.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.util.Vector;

public class Framework extends JFrame{

    String eventHeapIp;
    Scanner scan;
    EventLauncher eventLauncher;

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

    public Framework(String ip) {
        try {
            jbInit();
            this.eventHeapIp = ip;
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    private void jbInit() throws Exception {

        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension scrnsize = toolkit.getScreenSize();

        this.setBounds((int)scrnsize.width/4,(int)scrnsize.height/5,500,500);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setIconImage(null);
        this.setResizable(false);
        this.setTitle("Particle Framework");
        this.getContentPane().setLayout(null);

        lblEvents.setText("Events :");
        lblEvents.setBounds(new Rectangle(14, 292, 136, 20));

        btnScan.setBounds(new Rectangle(330, 108, 138, 29));
        btnScan.setText("Scan Network");
        btnScan.addActionListener(new Framework_btnScan_actionAdapter(this));

        btnConfigure.setBounds(new Rectangle(330, 145, 138, 29));
        btnConfigure.setText("Configure Particle");
        btnConfigure.addActionListener(new Framework_btnConfigure_actionAdapter(this));
        btnConfigure.setEnabled(false);

        btnStart.setBounds(new Rectangle(330, 183, 138, 29));
        btnStart.setText("Start Framework");
        btnStart.addActionListener(new Framework_btnStart_actionAdapter(this));
        btnStart.setEnabled(false);

        btnStop.setBounds(new Rectangle(330, 219, 138, 29));
        btnStop.setText("Stop Framework");
        btnStop.addActionListener(new Framework_btnStop_actionAdapter(this));
        btnStop.setEnabled(false);

        btnExit.setBounds(new Rectangle(330, 256, 138, 29));
        btnExit.setText("Exit");
        btnExit.addActionListener(new Framework_btnExit_actionAdapter(this));

        btnAdd.setBounds(new Rectangle(131, 278, 58, 20));
        btnAdd.setActionCommand("btnAdd");
        btnAdd.setText("Add");
        btnAdd.addActionListener(new Framework_btnAdd_actionAdapter(this));

        lblParticles.setText("Particle List:");
        lblParticles.setBounds(new Rectangle(12, 40, 113, 21));

        lblTitle.setFont(new java.awt.Font("Times New Roman", Font.BOLD, 20));
        lblTitle.setHorizontalAlignment(SwingConstants.CENTER);
        lblTitle.setText("Particle Framework");
        lblTitle.setBounds(new Rectangle(126, 8, 234, 28));

        imgI10 = new ImagePanel("src/img/logo_i10.gif");
        imgI10.setBounds(350,0,180,80);

        scPnParticles.setBounds(new Rectangle(13, 63, 176, 214));

        lstParticles.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        lstParticles.addListSelectionListener(new Framework_particle_ListAdapter(this));

        scPnEvents.setBounds(new Rectangle(13, 317, 371, 131));

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
            pf = new Framework(args[0]);
        else
            System.out.println("Usage: Framework <Event Heap IP Address>");
    }

    public void btnExit_actionPerformed(ActionEvent e)
    {
        System.exit(0);
    }

    public void btnScan_actionPerformed(ActionEvent e)
    {
        scan = new Scanner(this);
        Thread t = new Thread(scan);
        listmodelEvents.addElement("Scanning Network...");
        t.start();
    }

    public void btnConfigure_actionPerformed(ActionEvent e)
    {
        ConfigureDialog cd = new ConfigureDialog(this);
        if (cd.cancelled == false)
        {
              this.listmodelEvents.addElement("Starting Configuration...");
              SensorConfig cf = new SensorConfig(this,lstParticles.getSelectedValue(),cd);
              cf.startConfiguration();

              if (cf.isSuccessful())
              {
                   this.listmodelEvents.addElement("Configuration was successfull");
                   this.configuredParticles.add(lstParticles.getSelectedValue());
                   this.btnStart.setEnabled(true);
              }
              else
                   this.listmodelEvents.addElement("Configuration failed");
        }

    }

    public void btnAdd_actionPerformed(ActionEvent e)
    {
        String s = (String)JOptionPane.showInputDialog(this,"Enter a particle Id:\n","Manually Add Particle Id",JOptionPane.PLAIN_MESSAGE,null,null,"255.255.255.255.255.255.255.255");

        if((s!=null) && (s.length()>0))
            this.listmodelParticles.addElement(s);
    }

    public void btnStart_actionPerformed(ActionEvent e) {

       eventLauncher = new EventLauncher(configuredParticles,eventHeapIp);
       Thread t = new Thread(eventLauncher);
       listmodelEvents.addElement("Starting Framework...");
       btnScan.setEnabled(false);
       btnConfigure.setEnabled(false);
       btnStart.setEnabled(false);
       btnStop.setEnabled(true);
       t.start();

    }

    public void btnStop_actionPerformed(ActionEvent e) {

        eventLauncher.stop();
        btnScan.setEnabled(true);
        btnConfigure.setEnabled(true);
        btnStart.setEnabled(true);
        btnStop.setEnabled(false);
        listmodelEvents.addElement("Framework Stopped");

    }

    public void particleListUpdated(ListSelectionEvent e)
    {
        if(this.lstParticles.getSelectedIndex() == -1)
            btnConfigure.setEnabled(false);
        else
            btnConfigure.setEnabled(true);
    }
}


class Framework_particle_ListAdapter implements  ListSelectionListener{
    private Framework adaptee;
    Framework_particle_ListAdapter(Framework adaptee) {
        this.adaptee = adaptee;
    }

    public void valueChanged(ListSelectionEvent e) {
        adaptee.particleListUpdated(e);
    }
}

class Framework_btnStop_actionAdapter implements ActionListener {
    private Framework adaptee;
    Framework_btnStop_actionAdapter(Framework adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.btnStop_actionPerformed(e);
    }
}


class Framework_btnStart_actionAdapter implements ActionListener {
    private Framework adaptee;
    Framework_btnStart_actionAdapter(Framework adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.btnStart_actionPerformed(e);
    }
}


class Framework_btnConfigure_actionAdapter implements ActionListener {
    private Framework adaptee;
    Framework_btnConfigure_actionAdapter(Framework adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.btnConfigure_actionPerformed(e);
    }
}


class Framework_btnScan_actionAdapter implements ActionListener {
    private Framework adaptee;
    Framework_btnScan_actionAdapter(Framework adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.btnScan_actionPerformed(e);
    }
}


class Framework_btnExit_actionAdapter implements ActionListener {
    private Framework adaptee;
    Framework_btnExit_actionAdapter(Framework adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.btnExit_actionPerformed(e);
    }
}

class Framework_btnAdd_actionAdapter implements ActionListener {
    private Framework adaptee;
    Framework_btnAdd_actionAdapter(Framework adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.btnAdd_actionPerformed(e);
    }
}
