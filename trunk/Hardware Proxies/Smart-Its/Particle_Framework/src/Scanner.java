
import edu.teco.particles.libParticle.*;

public class Scanner implements Runnable{

    Framework main;

    static
    {
        System.loadLibrary("particleJava");
    }

    public Scanner(Framework f)
    {
        this.main = f;
    }

    public void run()
    {
        try
        {
            ParticleSocket socket = new ParticleSocket(5556);
            ParticlePacket hello = new ParticlePacket();
            short data[] = {255, 255, 255, 255, 255, 255, 255, 255};
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

    private void getData() throws java.lang.InterruptedException
    {
        ParticleSocket socket = new ParticleSocket(5555);
        try{
            socket.setAutoAck(0);
            ParticlePacket pck = null;

            for (int i = 0; i < 15; i++) {
                socket.setBlocking(0);
                pck = socket.receive(socket);
                if (pck != null) {
                    ParticleSrcId src = pck.getSrcId();
                    if (!main.listmodelParticles.contains(src.toString())) {
                        main.listmodelParticles.addElement(src.toString());
                    }
                    pck = socket.receive(socket);
                }
                Thread.sleep(100);
            }
        } catch(UnknownError e){
            if( !(e.getMessage().equals("c errno: 11")||e.getMessage().equals("c errno: 35")) ) {
                        System.out.println( e.getMessage() );
                        e.printStackTrace();
            }
            // this error was caused because no more packets are
            // avaiable.
        }
        socket.close();
        main.listmodelEvents.addElement("Scanning Finished");

    }
}
