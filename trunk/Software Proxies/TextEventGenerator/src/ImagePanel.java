import javax.swing.*;
import java.awt.*;
import javax.imageio.*;
import java.io.*;

public class ImagePanel extends JPanel
{
        //path of image
        private String path;

        //image object
        private Image img;

        public ImagePanel(String path) throws IOException
        {
                //save path
                this.path = path;

                //load image
                img = ImageIO.read(new File(path));

        }

        //override paint method of panel
        public void paint(Graphics g)
        {
                //draw the image
                if( img != null)
                        g.drawImage(img,0,0, this);
        }

}
