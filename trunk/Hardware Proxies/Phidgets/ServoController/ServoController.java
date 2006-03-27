import iwork.eheap2.Event;
import iwork.eheap2.EventHeap;
import Phidgets.PhidgetServo;

public class ServoController{

	public ServoController(String eventHeapName, String proxyID) {
		// connect a 4 Motor Servo Controller
		//PhidgetMotorControl phid = new PhidgetMotorControl();
		//The values for a Servo Motor range from 30..215
		PhidgetServo phid = new PhidgetServo();
		if (phid.Open(false) == false) 
		{
			System.out.println("Could not find a PhidgetServoControl");
			return;
		}
			
		//Before starting the controller, all motors should be reset to the minimal position
		phid.SetMotorPosition(0,50);
		phid.SetMotorPosition(1,50);
		phid.SetMotorPosition(2,50);
		phid.SetMotorPosition(3,50);
		
		try{
			EventHeap eheap = new EventHeap(eventHeapName);			
			Event template = new Event("ServoController");
			template.addField("ProxyID", proxyID);
			Event received;
			while( true ){
				received = eheap.waitForEvent(template);
				if  ( (received.getPostValue("ProxyID").equals(proxyID))
						|| (proxyID.equals(""))) {
					// Please don't get afraid! :)
					// As SetMotorPosition expects a double number and getPostValueString
					// returns strings a conversion is needed.
					// This is done in one step without additional variables.
					phid.SetMotorPosition(0, Double.valueOf(received.getPostValueString("PosMot1").trim()).doubleValue());
					phid.SetMotorPosition(1, Double.valueOf(received.getPostValueString("PosMot2").trim()).doubleValue());
					phid.SetMotorPosition(2, Double.valueOf(received.getPostValueString("PosMot3").trim()).doubleValue());
					phid.SetMotorPosition(3, Double.valueOf(received.getPostValueString("PosMot4").trim()).doubleValue());
													
				/* the following can be used for a motor controller
					String motor1Acceleration = received.getPostValueString("Motor1Acceleration");
					String motor1Speed = received.getPostValueString("Motor1Speed");
					String motor2Acceleration = received.getPostValueString("Motor2Acceleration");
					String motor2Speed = received.getPostValueString("Motor2Speed");
					String motor3Acceleration = received.getPostValueString("Motor3Acceleration");
					String motor3Speed = received.getPostValueString("Motor3Speed");
					String motor4Acceleration = received.getPostValueString("Motor4Acceleration");
					String motor4Speed = received.getPostValueString("Motor4Speed");
					
					System.out.println("Speed1: " + motor1Speed);
					System.out.println("Acceleration1: " + motor1Acceleration);
					System.out.println("Speed2: " + motor2Speed);
					System.out.println("Acceleration2: " + motor2Acceleration);
					System.out.println("Speed3: " + motor3Speed);
					System.out.println("Acceleration3: " + motor3Acceleration);
					System.out.println("Speed4: " + motor4Speed);
					System.out.println("Acceleration4: " + motor4Acceleration);
			*/
				}
			}
		} catch( Exception ex ){
			ex.printStackTrace();
		}

		
	}

	
	
	public static void main(String args[]){
		if(args.length == 1)
			new ServoController(args[0],"");
		else if (args.length > 2)
			new ServoController(args[0], args[1]);
		 else 
			System.out.println("Usage: ServoController <Event Heap Name> [ProxyID]");
	}

}
