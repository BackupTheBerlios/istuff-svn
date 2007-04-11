import java.awt.GridBagLayout;
import java.awt.LayoutManager;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JPanel;

public class ProxyHolderPanel extends JPanel implements ActionListener{
	private int _tabNumber; 
	
	public ProxyHolderPanel(LayoutManager layout, int tabNumber) {
		super (layout);
		_tabNumber = tabNumber;
	}
	
	public void actionPerformed (ActionEvent e){ // Invoked, when a proxy remove button is pressed
		ProxyEntry entryToRemove = (ProxyEntry) e.getSource();
		entryToRemove.getProxyNode().fireEventRemoved();
		remove(entryToRemove);
		updateUI();
	}
	
	public int getTabNumber (){
		return _tabNumber;
	}

}
