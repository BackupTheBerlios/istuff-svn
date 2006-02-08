import edu.teco.particles.libParticle.*;
import java.util.*;

public class SensorConfig {

    Framework main;
    String particleId;
    ConfigureDialog conDialog;
    boolean successful = false;

    SensorConfig(Framework f,Object particle,ConfigureDialog cd)
    {
        main = f;
        particleId = (String) particle;
        conDialog = cd;
    }

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
