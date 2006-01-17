import java.io.File;

import javax.swing.filechooser.FileFilter;

public class CustomFileFilter extends FileFilter {
	 
	public boolean accept (File f) {
		 if (f.isDirectory())
			 {return (true);}
		 return(false);
	 }
	 public String getDescription () {
		 return ("Proxy Directories");
	 }	
	
}
