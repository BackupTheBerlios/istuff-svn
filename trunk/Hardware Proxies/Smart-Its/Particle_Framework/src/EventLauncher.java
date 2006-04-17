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

import java.util.Vector;
import java.util.Hashtable;
import edu.teco.particles.libParticle.*;
import iwork.eheap2.*;

//!  EventLauncher class receives sensor data from "Particles" and posts it onto the "Event Heap".
/*!  The two main functionalities of this class are:
  		-# Receive packets with sensor data from "Particles".
  		-# Post the sensor data packet onto the "Event Heap" only if its different from the last packet.
*/

public class EventLauncher implements Runnable{

    protected Vector particles;
    protected boolean running;
    protected ParticleSocket recSocket;
    protected ParticleFilter filter;
    protected Hashtable lastPacketList;
    protected EventHeap eventHeap;
    protected String eventHeapIp;
    protected String proxyID;

 	//! EventLauncher class constructor
	/*! The constructor initializes the local variables with the parameters
			provided.

			\param configuredParticles as a Vector. This vector contains ID of all the
						 "Particles" that have been configured to receive sensor data.
			\param eventHeapIp as a String. Specifies the IP address of the "Event Heap".
			\param proxyID as a String. Specifies the proxy ID to be used while
			   		 posting Events and to be checked while receiving events.
	*/
    public EventLauncher(Vector configuredParticles, String eventHeapIp, String proxyID)
    {
        particles = configuredParticles;
        running = false;
        this.eventHeapIp = eventHeapIp;
        this.proxyID = proxyID;
    }
    
  //! Receives sensor data from the "Particles" and posts them as events onto the "Event Heap"
	/*! This method receives the sensor data packets from the "Particles" that are 
			contained	in the "particles" vector. On reception of each packet, it is 
			checked for changes from the last packet received by the same "Particle".
			If the packet is different, it is posted as Event onto the "Event Heap".
	*/

    public void run()
    {
       running = true;

       int filterMode = P_FILTER.FILTER_CONCAT_AND | P_FILTER.FILTER_TYPE_ID;
       filter = new ParticleFilter("Id Filter");
       ParticleSrcId recFrom = new ParticleSrcId((String) particles.get(0));
       filter.add(filterMode,recFrom.toFilter());	//receive packets from this particle

       if(particles.size() > 1)	//if the particle list contains more than one particle
       {
           filterMode = P_FILTER.FILTER_CONCAT_OR | P_FILTER.FILTER_TYPE_ID;

           for (int i = 1; i < particles.size(); i++) {
               recFrom = new ParticleSrcId((String) particles.get(i));
               System.out.println(recFrom.toString());
               filter.add(filterMode, recFrom.toFilter()); 	//add all the particles to the reception list
           }
       }

       recSocket = new ParticleSocket(5555);	//open a socket for reception of packets from particles
       lastPacketList = new Hashtable();
       eventHeap = new EventHeap(eventHeapIp);
       ParticlePacket currPacket;
       ParticleSrcId currId;
       boolean same;
       do
       {
           same = true;
           currPacket = recSocket.receiveFiltered(recSocket,filter);	//get a new packet
           if(currPacket != null)
           {
               currId = currPacket.getSrcId();	//get the Source Id of the packet received
               ParticlePacket lastPacket = (ParticlePacket) lastPacketList.get(currId.toString());	//get the previous packet transmitted by this Source from the hashtable

               if(lastPacket != null) //if the previous packet transfered from this particle exists
               {
                   ParticleTuple currPacketTuple = currPacket.firstAcl();	//get the 1st tuple from the current packet
                   ParticleTuple lastPacketTuple = lastPacket.findFirstAcl(currPacketTuple.getAclType());	//get the 1st tuple from the previous packet

                   while (currPacketTuple != null)
                   {
                       short[] currPacketTupleData = currPacketTuple.toArray();	//get data of the current packet tuple
                       short[] lastPacketTupleData = lastPacketTuple.toArray();	//get data of the previous packet tuple

                       for(int i=0;i<currPacketTupleData.length;i++)
                       {
                           if(currPacketTupleData[i] != lastPacketTupleData[i])	//if the data is not equal
                           {
                               same = false;
                               break;
                           }
                       }
                       if(!same)
                           break;

                       currPacketTuple = currPacket.nextAcl(currPacketTuple); //get the next tuple from the current packet
                       lastPacketTuple = lastPacket.nextAcl(lastPacketTuple); //get the next tuple from the previous packet
                   }
               }
               else
                   same = false;

               if(!same)	//if packets are not same
               {
                   try
                   {
                       Event event = new Event("Particle_Packet");	//create an event which represents a particle packet
                       event.addField("ProxyID", proxyID);
                       event.addField("ParticleSrcId",currPacket.getSrcId().toString());	//add the source Id to the event
                       event.setTimeToLive(1000);

                       ParticleTuple currTuple = currPacket.firstAcl();
                       currTuple = currPacket.nextAcl(currTuple);	//get the 2nd tuple which is sensor data
                       int sensor;
                       while(currTuple != null)
                       {
                           sensor = 0;
                           for(int i=0;i<currTuple.length();i++){	//the sensor data has three bytes which are filled into a single integer
                               sensor = sensor << 8;
                               sensor |= currTuple.getAclByte(i);
                           }
                           event.addField(currTuple.getAclType(),new Integer(sensor));	// add a field to the event with the tuple name e.g. sgx and the sensor data integer
                           currTuple = currPacket.nextAcl(currTuple);	//get the next sensor data which is the next tuple
                       }

                       eventHeap.putEvent(event);	//get the event onto the event heap
                       lastPacketList.remove(currPacket.getSrcId().toString());	//remove the previous packet transmitted by the current source from the hashtable
                       lastPacketList.put(currPacket.getSrcId().toString(),currPacket);	//add the current packet transmitted by the source to the hashtable
                   }
                   catch(Exception e)
                   {
                       e.printStackTrace();
                   }
               }
           }

       }while(running);
    }

    public void stop()
    {
        synchronized (this)
        {
            running = false;
        }
    }
}
