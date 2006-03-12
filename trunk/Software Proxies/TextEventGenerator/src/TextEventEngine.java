import javax.swing.*;
import java.awt.*;
import java.io.*;
import java.awt.event.KeyListener;
import java.awt.event.KeyEvent;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import iwork.eheap2.*;

public class TextEventEngine extends JFrame{

    JLabel lblText = new JLabel();
    JButton btnExit = new JButton();
    JLabel lblTitle = new JLabel();
    JTextArea txtText = new JTextArea();
    JScrollPane spnText;
    ImagePanel imgI10;
    EventHeap eventHeap;

    public TextEventEngine(String ip) {
        try {
            eventHeap = new EventHeap(ip);
            init();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    private void init() throws Exception {

        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension scrnsize = toolkit.getScreenSize();

        this.setBounds((int)scrnsize.width/4,(int)scrnsize.height/5,500,500);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setIconImage(null);
        this.setResizable(false);
        this.setTitle("Text Event Engine");
        this.getContentPane().setLayout(null);

        btnExit.setBounds(new Rectangle(190, 400, 138, 29));
        btnExit.setText("Exit");
        btnExit.addActionListener(new TextEventEngine_btnExit_actionAdapter(this));

        lblText.setText("Enter the text:");
        lblText.setBounds(new Rectangle(12, 100, 113, 21));

        txtText.setLineWrap(true);
        txtText.addKeyListener(new TextEventEngine_txtText_documentAdapter(this));

        spnText = new JScrollPane(txtText);
        spnText.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        spnText.setBounds(new Rectangle(12, 130, 300, 250));

        lblTitle.setFont(new java.awt.Font("Times New Roman", Font.BOLD, 20));
        lblTitle.setHorizontalAlignment(SwingConstants.CENTER);
        lblTitle.setText("Text Event Engine");
        lblTitle.setBounds(new Rectangle(126, 8, 234, 28));

		System.out.println(System.getProperty("user.dir"));
        imgI10 = new ImagePanel("./img/logo_i10.gif");
        imgI10.setBounds(350,0,180,80);

        this.getContentPane().add(imgI10);
        this.getContentPane().add(btnExit);
        this.getContentPane().add(lblTitle);
        this.getContentPane().add(lblText);
        this.getContentPane().add(spnText);
        this.setVisible(true);
    }

    public static void main(String args[])
    {
        TextEventEngine tee;

        if (args.length == 1)
        	tee = new TextEventEngine(args[0]);
        else
        	System.out.println("Usage: java TextEventEngine <Event Heap IP>\n");
    }

    public void btnExit_actionPerformed(ActionEvent e)
    {
        System.exit(0);
    }

    public void txtText_keyTyped(KeyEvent e)
    {
	Integer code = new Integer(e.getKeyChar());
	System.out.println("Sent Code = " + code);

    	try
    	{
		iwork.eheap2.Event event = new iwork.eheap2.Event("TextEvent");
	      	event.addField("Character",code);
	      	eventHeap.putEvent(event);
      	}
      	catch(Exception ex)
      	{
      		ex.printStackTrace();
      	}
    }
}


class TextEventEngine_btnExit_actionAdapter implements ActionListener {
    private TextEventEngine adaptee;
    TextEventEngine_btnExit_actionAdapter(TextEventEngine adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.btnExit_actionPerformed(e);
    }
}

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
