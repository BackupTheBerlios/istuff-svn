//
//  iStuff.java
//  iStuff
//
//  Created by Tim Hemig on 5/10/07.
//  Copyright (c) 2007 __MyCompanyName__. All rights reserved.
//
//	For information on setting Java configuration information, including 
//	setting Java properties, refer to the documentation at
//		http://developer.apple.com/techpubs/java/java.html
//

public class iStuff {
    
    public static void main(String args[]) {
        if (System.getProperty("os.name").contains("Mac")) {
	    System.setProperty("apple.laf.useScreenMenuBar","true");
	    System.setProperty("com.apple.mrj.application.growbox.intrudes","false");
	}
	new PLMainFrame();
	System.out.println("Main application window instantiated. " +
			   "You can now connect to different Event Heap Proxies " +
			   "graphically. Have a good time");
    }
    
}
