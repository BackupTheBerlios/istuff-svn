import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import com.apple.eawt.ApplicationAdapter;
import com.apple.eawt.ApplicationEvent;
import com.apple.eawt.Application;
import com.apple.eawt.ApplicationListener;

import javax.swing.JFrame;
import javax.swing.event.EventListenerList;

import com.apple.eawt.ApplicationAdapter;
import com.apple.eawt.ApplicationEvent;
import com.apple.eawt.Application;
import javax.swing.JFrame;

public class CustomApplication extends Application {

    public CustomApplication() {
        addApplicationListener(new AboutBoxHandler());
    }

    class AboutBoxHandler extends ApplicationAdapter {
        public void handleAbout(ApplicationEvent event) {
         event.isHandled();   
        	new JFrame().show();
            System.out.println("In custom Object");
        }
    }
}

    //class AboutBoxHandler extends ApplicationAdapter {
      //  }
    //}