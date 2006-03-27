
import java.util.Vector;
import java.util.Hashtable;
import edu.teco.particles.libParticle.*;
import iwork.eheap2.*;

public class EventLauncher implements Runnable{

    protected Vector particles;
    protected boolean running;
    protected ParticleSocket recSocket;
    protected ParticleFilter filter;
    protected Hashtable lastPacketList;
    protected EventHeap eventHeap;
    protected String eventHeapIp;
    protected String _proxyID;

    public EventLauncher(Vector configuredParticles, String eventHeapIp, String proxyID)
    {
        particles = configuredParticles;
        running = false;
        this.eventHeapIp = eventHeapIp;
        _proxyID = proxyID;
    }

    public void run()
    {
       running = true;

       int filterMode = P_FILTER.FILTER_CONCAT_AND | P_FILTER.FILTER_TYPE_ID;
       filter = new ParticleFilter("Id Filter");
       ParticleSrcId recFrom = new ParticleSrcId((String) particles.get(0));
       System.out.println(recFrom.toString());
       filter.add(filterMode,recFrom.toFilter());

       if(particles.size() > 1)
       {
           filterMode = P_FILTER.FILTER_CONCAT_OR | P_FILTER.FILTER_TYPE_ID;

           for (int i = 1; i < particles.size(); i++) {
               recFrom = new ParticleSrcId((String) particles.get(i));
               System.out.println(recFrom.toString());
               filter.add(filterMode, recFrom.toFilter());
           }
       }

       recSocket = new ParticleSocket(5555);
       lastPacketList = new Hashtable();
       eventHeap = new EventHeap(eventHeapIp);
       ParticlePacket currPacket;
       ParticleSrcId currId;
       boolean same;
       do
       {
           same = true;
           currPacket = recSocket.receiveFiltered(recSocket,filter);
           if(currPacket != null)
           {
               currId = currPacket.getSrcId();
               ParticlePacket lastPacket = (ParticlePacket) lastPacketList.get(currId.toString());

               if(lastPacket != null)
               {
                   ParticleTuple currPacketTuple = currPacket.firstAcl();
                   ParticleTuple lastPacketTuple = lastPacket.findFirstAcl(currPacketTuple.getAclType());

                   while (currPacketTuple != null)
                   {
                       short[] currPacketTupleData = currPacketTuple.toArray();
                       short[] lastPacketTupleData = lastPacketTuple.toArray();

                       for(int i=0;i<currPacketTupleData.length;i++)
                       {
                           if(currPacketTupleData[i] != lastPacketTupleData[i])
                           {
                               same = false;
                               break;
                           }
                       }
                       if(!same)
                           break;

                       currPacketTuple = currPacket.nextAcl(currPacketTuple);
                       lastPacketTuple = lastPacket.nextAcl(lastPacketTuple);
                   }
               }
               else
                   same = false;

               if(!same)
               {
                   try
                   {
                       Event event = new Event("Particle_Packet");
                       event.addField("ProxyID", _proxyID);
                       event.addField("ParticleSrcId",currPacket.getSrcId().toString());
                       event.setTimeToLive(1000);

                       ParticleTuple currTuple = currPacket.firstAcl();
                       currTuple = currPacket.nextAcl(currTuple);
                       int sensor;
                       while(currTuple != null)
                       {
                           sensor = 0;
                           for(int i=0;i<currTuple.length();i++){
                               sensor = sensor << 8;
                               sensor |= currTuple.getAclByte(i);
                           }
                           event.addField(currTuple.getAclType(),new Integer(sensor));
                           currTuple = currPacket.nextAcl(currTuple);
                       }

                       eventHeap.putEvent(event);
                       lastPacketList.remove(currPacket.getSrcId().toString());
                       lastPacketList.put(currPacket.getSrcId().toString(),currPacket);
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
