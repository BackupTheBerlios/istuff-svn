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
 *			  Tico Ballagas
 *
 * Version:	  1.0
 */

import edu.teco.particles.libParticle.*;
import java.util.*;

//!  SensorConfig class configures the sensor module attached with the "Particle".
/*!  The main functionality of this class is to configure the sensor board which
	 is attached to a "Particle". Configuration of the sensor board means
	 which sensor information to receive and at what rate. This class is functional
	 when the OK button on the ConfigureDialog GUI is clicked.
*/

public class SensorConfig {

    Framework main;
    String particleId;
    ConfigureDialog conDialog;
    boolean successful = false;

    //!  SensorConfig class constructor.
	/*!  The constructor takes in objects of Framework, Object and ConfigureDialog
		 types and save them locally.

		 \param f as a Framework type object
		 \param particle as an Object type object
		 \param cd as a ConfigureDialog type object

	*/

    SensorConfig(Framework f,Object particle,ConfigureDialog cd)
    {
        main = f;
        particleId = (String) particle;
        conDialog = cd;
    }


    //!  Starts the configuration of a "Particle" sensor board
    /*!  This method starts the configuration of a single "Particle" sensor
    	 module. It first checks what sensors where selected by the user
    	 and then sends a configuration packet to the "Particle".
	*/

    public void startConfiguration()
    {
        ParticlePacket packet = new ParticlePacket();
        Vector sensorData = new Vector();
        short data[] = new short[0];
        packet.aclAdd( "aps", data, 0 );

        if(conDialog.chkAccXY.isSelected() == true)
        {
            sensorData.add(new Short("0"));
            sensorData.add(new Short((short)conDialog.cmbRates[0].getSelectedIndex()));
        }
        if(conDialog.chkAccZ.isSelected() == true)
        {
            sensorData.add(new Short("1"));
            sensorData.add(new Short((short)conDialog.cmbRates[1].getSelectedIndex()));
        }
        if(conDialog.chkAudio.isSelected() == true)
        {
            sensorData.add(new Short("2"));
            sensorData.add(new Short((short)conDialog.cmbRates[2].getSelectedIndex()));
        }
        if(conDialog.chkLight.isSelected() == true)
        {
            sensorData.add(new Short("3"));
            sensorData.add(new Short((short)conDialog.cmbRates[3].getSelectedIndex()));
        }
        if(conDialog.chkALight.isSelected() == true)
        {
            sensorData.add(new Short("4"));
            sensorData.add(new Short((short)conDialog.cmbRates[4].getSelectedIndex()));
        }
        if(conDialog.chkForce.isSelected() == true)
        {
            sensorData.add(new Short("5"));
            sensorData.add(new Short((short)conDialog.cmbRates[5].getSelectedIndex()));
        }
        if(conDialog.chkTemp.isSelected() == true)
        {
            sensorData.add(new Short("6"));
            sensorData.add(new Short((short)conDialog.cmbRates[6].getSelectedIndex()));
        }
        if(conDialog.chkVoltage.isSelected() == true)
        {
            sensorData.add(new Short("7"));
            sensorData.add(new Short((short)conDialog.cmbRates[7].getSelectedIndex()));
        }

        data = new short[sensorData.size()];
        for(int i=0;i<sensorData.size();i++)
            data[i] = ((Short) sensorData.get(i)).shortValue();

        packet.aclAdd( "crs", data, 0 );

        for (int i = 0; i < 15; i++) {
            try
            {

                ParticleSrcId src = new ParticleSrcId(particleId.toString());
                ParticleSocket sndSocket = new ParticleSocket(5556);
                ParticleSocket recSocket = new ParticleSocket(5555);
                recSocket.setBlocking(0);
                sndSocket.sendAcked(recSocket, packet, src);
                // if this returns without exception the particle is configured
                successful = true;


                sndSocket.close();
                recSocket.close();
                break;
            } catch (Exception e) {
                e.printStackTrace();
                successful = false;
            } catch (Error err) {
                if (!(err.getMessage().equals("c errno: 11") ||
                      err.getMessage().equals("c errno: 35"))) {
                    System.out.println(err.getMessage());
                    err.printStackTrace();
                    successful = false;

                }
                // this error was caused because no more packets are
                // avaiable.
                successful = true;
                break;
            }
            try{
                Thread.sleep(100);
            }catch(Exception e){

            }
        }
    }

    public boolean isSuccessful()
    {
        return successful;
    }
}
