import java.awt.BorderLayout;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;

import javax.swing.*;

public class RollDownWindow extends JWindow {
	  
	BorderLayout borderLayout1 = new BorderLayout();
	  JPanel titleBar = new JPanel();
	  JLabel title = new JLabel();
	  
	  int x=-1;
	  int y=-1;
	 
	  public RollDownWindow(String windowTitle) {
	   /* try {
	      jbInit();
	    }
	    catch(Exception e) {
	      e.printStackTrace();
	    }*/
	    //this.setUndecorated(true);
	    titleBar.add(new JLabel(windowTitle));
	    titleBar.add(new JButton ("Ein/Aus-Rollen"));
	    this.add(titleBar,BorderLayout.NORTH);
	    //TODO: Add icon and corresponding listener to roll in / out the
	    // dialog.
	    //Maybe also add another icon to close tha window. It can be reactivated
	    // vian the menu
	    this.setAlwaysOnTop(true);
	    titleBar.addMouseListener(new MouseAdapter(){
	      public void mouseReleased(MouseEvent e){
	        x = e.getX();
	        y = e.getY();
	      }
	       public void mousePressed(MouseEvent e){
	        x = e.getX();
	        y = e.getY();
	      }      
	    });
	    
	    titleBar.addMouseMotionListener(new MouseMotionAdapter(){
	      public void mouseDragged(MouseEvent e){
	        int xx = getLocation().x;
	        int yy = getLocation().y;
	        setLocation(xx+(e.getX()-x),yy+(e.getY()-y));
	      }
	    });
	    //pack();
	    //setVisible(true);
	    
	  }
}