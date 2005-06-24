// listen for audio events...
import java.util.*;
import java.io.*;
import iwork.eheap2.*;

public class testSoundClip {
    public static void main(String [] argv) {
        try{
            EventHeap eh = new EventHeap("iw-room2");
            Event e = new Event("AudioEvent");
            e.addField("AudioCommand", "Play" );
            e.addField("Name", "dogbrk.wav" );
            eh.putEvent( e );
        }catch(Exception ex){ ex.printStackTrace(); }
    }
}