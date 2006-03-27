
public class ProxyLauncher {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// Distinguish between Mac- and Windows-style menu positions
		// This has to be done here - otherwise is will have no effect.
		if (System.getProperty("os.name").contains("Mac")) {
			System.setProperty("apple.laf.useScreenMenuBar","true");
			//System.setProperty("apple.awt.showGrowBox", "false");
			System.setProperty("com.apple.mrj.application.growbox.intrudes","false");
		}
		//TODO: It is not clear whether customLibs are really needed.
		// When removed, think of inserting ".." into launch statements.
		new PLMainFrame();
		System.out.println("Main application window instantiated. " +
				"You can now connect to different Even Heap Proxies " +
				"graphically. Have a good time");
	}

}
