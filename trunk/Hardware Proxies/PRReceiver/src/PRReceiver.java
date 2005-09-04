// PRReceiver.java

import ehwrapper.*;

class PRReceiver implements EHHandler
{
    EHEventHeap eheap;
    String screen;
    
    public PRReceiver(String server, String screen) {
        EventSim.enableEventStateCombining(false);
        eheap = new EHEventHeap(server);
        this.screen = screen;
        EHEvent template = EHEvent.create("PointRightEvent");
        template.addField("Screen",screen);
        eheap.registerForEvent(template, this);
        while (true) try { Thread.sleep(10000); } catch (Exception e) { }
    }

    public void handleEHEvent(EHEvent e) {
        String type = e.stringValue("PointRightEventType");
        if (type.equals("MouseEvent"))
        {
            int x = e.intValue("X");
            int y = e.intValue("Y");
            int leftButton = e.intValue("LeftButton");
            int rightButton = e.intValue("RightButton");
            int middleButton = e.intValue("MiddleButton");
            EventSim.postMouseEvent(x, y, leftButton, rightButton, middleButton);
        }
        else if (type.equals("ScrollEvent"))
        {
            int value = e.intValue("Value");
            EventSim.postScrollEvent(value);
        }
        else if (type.equals("KeyEvent"))
        {
            int charCode = e.intValue("CharCode");
            int keyCode = e.intValue("KeyCode");
            int state = e.intValue("State");
            EventSim.postKeyEvent(charCode, keyCode, state);
        }
        else if (type.equals("LeaveEvent"))
        {
            EventSim.postMouseEvent(32767, 32767, 0, 0, 0);
        }
    }
    
    public static void main(String[] args) {
        if (args.length < 2)
            System.out.println("Usage: <eheap-server> <screen-name>");
       else new PRReceiver(args[0], args[1]);
    }
}