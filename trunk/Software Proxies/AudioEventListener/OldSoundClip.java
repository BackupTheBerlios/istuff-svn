// listen for audio events...
import java.net.*;
import java.applet.*;

public class OldSoundClip{

    public static void main(String [] argv) {
        try{
            AudioClip ac = Applet.newAudioClip( new URL( "file://" + System.getProperty("user.dir") +
                                                         System.getProperty("file.separator") + argv[0] ) );
            ac.play();
        }catch( Exception ex ){ ex.printStackTrace(); }
    }
}