/*
 * Copyright (c) 2006
 * Media informatics Department
 * RWTH Aachen Germany
 * http://media.informatik.rwth-aachen.de
 *
 * Redistribution and use of the source code and binary, with or without
 * modification, are permitted under OPI Artistic License
 * (http://www.opensource.org/licenses/artistic-license.php) provided that
 * the source code retains the above copyright notice and the following
 * disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors:	  Faraz Ahmed Memon
 *
 * Version:	  1.0
 */

import javax.swing.*;
import java.awt.*;
import javax.imageio.*;
import java.io.*;

//! ImagePanel class draws a panel containing an image.
/*!	This class draws an image into a Panel which can inturn
	be used anywhere on a GUI
*/

public class ImagePanel extends JPanel
{
        //path of image
        private String path;

        //image object
        private Image img;

        //! ImagePanel class constructor
		/*! The ImagePanel constructor takes the path for the image as an argument
			and reads the image into an Image object.

			\param path as an String. Specifies the path for the image file.
		*/

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