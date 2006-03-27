import java.io.File;

import javax.swing.filechooser.FileFilter;

public class CustomFileFilter extends FileFilter {
	
	private String _fileName;
	private String _description;
	
	public CustomFileFilter (String fileName) {
		_description = fileName;
		if (fileName.equals("ProxyLauncher Compositions")) 
			_fileName = "plc";
		else
			_fileName =	fileName;
		
		
	}
	 
	public boolean accept (File f) {
		if (f.isDirectory()) {
			return true;
		}

		// This part is for the plc ending
		if (_fileName.equals("plc")) {
			String ext = "";
			String fileName = f.toString();
			int dotPlace = fileName.lastIndexOf('.');
			if (dotPlace >= 0)
				ext = fileName.substring(dotPlace+1);
			if (ext.equals("plc")){
				return true;
			}
		}
			
		// This part is for whole file names
		if (f.getName().equals(_fileName)) { 
		     return true;
		}
		else {
			return false;
		}
	 }
	
	 public String getDescription () {
		 return (_description);
	 }	
	
}
