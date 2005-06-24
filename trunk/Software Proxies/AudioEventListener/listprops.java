// listen for audio events...
import java.util.*;
import java.io.*;

public class listprops {
    public static void main(String [] argv) {
        try{
            Properties sysprops = System.getProperties();
            sysprops.list(System.out);
        }catch(Exception ex){ ex.printStackTrace(); }
    }
}