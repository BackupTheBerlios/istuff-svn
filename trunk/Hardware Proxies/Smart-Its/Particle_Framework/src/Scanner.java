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

//!  Scanner class scans for the "Particles" in the network.
/*!  The main functionality of this class is to broadcase a hello
	 packet onto the network and list all the "Particles" that
	 respond to It. The scanning of network is done in a separate
	 thread.
*/

public class Scanner implements Runnable{

    Framework main;

    static
    {
        System.loadLibrary("particleJava");	//load a static library
    }

    public Scanner(Framework f)
    {
        this.main = f;
    }

    //!  Starts scanning for the "Particles" in the network.
	/*!  This method starts scanning the network for "Particles"
		 by broadcasting a hello packet into the network. All
		 the "Particles" are by default configured to respond
		 to a hello packet.
	*/

    public void run()
    {
        try
        {
            ParticleSocket socket = new ParticleSocket(5556);
            ParticlePacket hello = new ParticlePacket();		//construct a new Particle packet
            short data[] = {255, 255, 255, 255, 255, 255, 255, 255}; //set up the destination address as a broadcast address
            short empt[] = {};
            hello.aclAdd("acm", empt, 0);
            hello.aclAdd("che", data, 0);
            socket.send(hello);
            socket.close();

            getData();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }


	//!  Listens to response of hello packet from the "Particles".
	/*!  This method receives all the packets that are incomming
		 as a response of the hello packet. The Partcle Id is extracted
		 from these packets and added to the "Particle List" on the
		 Framework GUI.
	*/

    private void getData() throws java.lang.InterruptedException
    {
        ParticleSocket socket = new ParticleSocket(5555);	//open a socker for receiving packets from "Particles"
            socket.setAutoAck(0);	//dont send an acknowledgment
            ParticlePacket pck = null;

            for (int i = 0; i < 15; i++) {	//loop 15 times with an interval of 100ms between each increament
                socket.setBlocking(0);		//dont block the thread
                try{
                    pck = socket.receive(socket);	//receive a packet
                    if (pck != null) {
                        ParticleSrcId src = pck.getSrcId();	//get the Source Id of the particle
                        if (!main.listmodelParticles.contains(src.toString())) {
                            main.listmodelParticles.addElement(src.toString());	//if the id doesnot exists in the list already, add it to the list
                        }
                        pck = socket.receive(socket);	//receive the next packet
                    }
                } catch(UnknownError e){
                    if (!(e.getMessage().equals("c errno: 11") ||
                          e.getMessage().equals("c errno: 35"))) {
                        System.out.println(e.getMessage());
                        e.printStackTrace();
                    }
                    // this error was caused because no more packets are
                    // avaiable.
                }
                Thread.sleep(100);
            }

        socket.close();
        main.listmodelEvents.addElement("Scanning Finished");

    }
}
