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
        ParticlePacket packet = new ParticlePacket();	//create a new packet to be sent to the "Particle"
        Vector sensorData = new Vector();		//holds the sensor no. selected by the user
        short data[] = new short[0];
        packet.aclAdd( "aps", data, 0 );	//add an empty "aps" tuple to the packet

        if(conDialog.chkAccXY.isSelected() == true)		//if X/Y axis acceleration sensor is selected
        {
            sensorData.add(new Short("0"));						//add the sensor no. to the vector. Sensor no. 0 is X/Y axis acceleration sensor
            sensorData.add(new Short((short)conDialog.cmbRates[0].getSelectedIndex()));	// add the index of selected transfer rate to the vector
        }
        
        /*
        	Sensor No.s: 
        				0 corresponds to the X/Y axis acceleration sensor in the "Particle" sensor board
        				1 corresponds to the Z axis acceleration sensor
        				2 corresponds to the audio sensor
        				3 corresponds to the light sensor
        				4 corresponds to the ambient light sensor
        				5 corresponds to the force sensor
        				6 corresponds to the temparature sensor
        				7 corresponds to the voltage sensor
        				
        	Transfer Rate: Transfer rate is the rate at which the "Particle" will transmit the data to the network
        				0 corresponds to the transfer rate of 13 ms
        				1 corresponds to the transfer rate of 26 ms
        				2 corresponds to the transfer rate of 52 ms
        				3 corresponds to the transfer rate of 104 ms
        				4 corresponds to the transfer rate of 208 ms
        				5 corresponds to the transfer rate of 416 ms
        				6 corresponds to the transfer rate of 832 ms
        				7 corresponds to the transfer rate of 1664 ms
        				8 corresponds to the transfer rate of 3328 ms
        				9 corresponds to the transfer rate of 6656 ms
        			 10 corresponds to the transfer rate of 13312 ms
        			 11 corresponds to the transfer rate of 26624 ms
        			 12 corresponds to the transfer rate of 53248 ms
        			 13 corresponds to the transfer rate of 106496 ms
        			 14 corresponds to the transfer rate of 212992 ms
        			 15 corresponds to the transfer rate of 425984 ms
        */
        
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
            data[i] = ((Short) sensorData.get(i)).shortValue();		//collect the selected sensor and rates

        packet.aclAdd( "crs", data, 0 );	//add the configuration data to the packet as a tuple

        for (int i = 0; i < 15; i++)
        {
            try
            {

                ParticleSrcId src = new ParticleSrcId(particleId.toString());
                ParticleSocket sndSocket = new ParticleSocket(5556);
                ParticleSocket recSocket = new ParticleSocket(5555);
                recSocket.setBlocking(0);
                sndSocket.sendAcked(recSocket, packet, src);	// if this returns without exception the particle is configured
                successful = true;


                sndSocket.close();
                recSocket.close();
                break;
            } 
            catch (Exception e)
            {
                e.printStackTrace();
                successful = false;
            } 
            catch (Error err) 
            {
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
            try
            {
                Thread.sleep(100);
            }catch(Exception e)
            {

            }
        }
    }

    public boolean isSuccessful()
    {
        return successful;
    }
}
