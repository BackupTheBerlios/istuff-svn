//
//  Joystick.java
//  GameController
//
//  Created by Andy Szybalski on Thu Feb 20 2003.
//

package iwork.gamecontroller;

import de.hardcode.jxinput.*;
import de.hardcode.jxinput.directinput.*;
import de.hardcode.jxinput.event.*;
import de.hardcode.jxinput.test.*;

import iwork.IWRoomConfigValues;
import iwork.eheap2.*;
import iwork.eheap2.EventHeap;

//import javax.swing.*; // For swingutilities.invokeLater()
import java.util.*;

import java.text.DateFormat;



class Joystick implements JXInputAxisEventListener,
JXInputButtonEventListener, JXInputDirectionalEventListener {

    // these are public to allow access for GameController debug buttons
    public static final int TIME_TO_LIVE = 50; // keep events on Event Heap for 50 ms
    public static final boolean USE_TRIGGERS_FIELD = false;
    public static final boolean USE_DELTA_FIELDS = false;

    private Event event = null;

    protected ArrayList axes = new ArrayList();
    protected ArrayList buttons = new ArrayList();
    protected ArrayList directionals = new ArrayList();
    public int joystickNum;
    private Event basicEvent = null;
    private Event lastEvent = null;
    
    public String friendlyName;
    private GameController controller;
    private JXInputDevice device;
    private boolean eventChanged = false;
    private Timer timer = new Timer();

    // dummy constructor: constructs dummy joystick with no features,
    // as a channel for sending iPong events from GameController debug buttons

    // real constructor: use this one most of the time
    public Joystick(int joystickNum, GameController controller, JXInputDevice dev) {
        this.joystickNum = joystickNum;
        this.controller = controller;
        this.device = dev;
        friendlyName = initFriendlyName();
        addAllFeaturesToArrayLists();
        registerAsListenerForAllFeatures();
        event = getBasicEvent();
    }

    private String initFriendlyName() {
        String prevName = controller.props.getProperty(getName());
        //System.out.println("initFriendlyName(): " + prevName);
        if (prevName != null) {
            return prevName;
        } else {
            return getName();
        }
    }

    public String getName() {
        String s;
        try {
            s = device.getName();
        } catch (Exception ex) {
            ex.printStackTrace();
            s = "Unknown";
        }
        return s;
    }

    public String getFriendlyName() {
        return friendlyName;
    }

    public void setFriendlyName(String s) {
        friendlyName = removeSpaces(s);
        controller.props.setProperty(getName(), s);
    }

    public boolean hasFeatures() {
        if (axes.isEmpty() && buttons.isEmpty() && directionals.isEmpty()) {
            return false;
        } else {
            return true;
        }
    }

    // helper function:
    private void addAllFeaturesToArrayLists() {
        int j;

        // Add all valid axes, buttons, directionals to this.axes, etc.
        for (j = 0; j < device.getMaxNumberOfAxes(); j++)
            if (device.getAxis(j) != null) axes.add(device.getAxis(j));
        for (j = 0; j < device.getMaxNumberOfButtons(); j++)
            if (device.getButton(j) != null) buttons.add(device.getButton(j));
        for (j = 0; j < device.getMaxNumberOfDirectionals(); j++)
            if (device.getDirectional(j) != null) directionals.add(device.getDirectional(j));
    }

    // helper function:
    private void registerAsListenerForAllFeatures() {
        Iterator it;
        it = axes.iterator();
        while (it.hasNext()) {
            Axis a = (Axis)it.next();
            JXInputEventManager.addListener( this, a );
        }

        it = buttons.iterator();
        while (it.hasNext()) {
            Button b = (Button)it.next();
            JXInputEventManager.addListener( this, b );
        }

        it = directionals.iterator();
        while (it.hasNext()) {
            Directional d = (Directional)it.next();
            JXInputEventManager.addListener( this, d );
        }

    }

    public void changed(JXInputAxisEvent e) {
        try {
            addAxisFields(e.getAxis());
            if (USE_DELTA_FIELDS)
                addAxisDeltas(e);
            eventChanged = true;
        } catch (EventHeapException ex) {
            ex.printStackTrace();
        }        
    }

    public void changed(JXInputButtonEvent e) {
        try {
            addButtonFields(e.getButton());
            if (USE_DELTA_FIELDS)
                addButtonDeltas(e);
            eventChanged = true;
        } catch (EventHeapException ex) {
            ex.printStackTrace();
        }
        
    }

    public void changed(JXInputDirectionalEvent e) {
        try {
            addDirectionalFields(e.getDirectional());
            if (USE_DELTA_FIELDS)
                addDirectionalDeltas(e);
            eventChanged = true;
        } catch (EventHeapException ex) {
            ex.printStackTrace();
        }
    }

    // getBasicEvent()
    // ---------------
    // A convenience to avoid repeatedly adding standard fields to tuples
    private Event getBasicEvent() {
        event = buildBasicEvent();
        try {
            ArrayList triggers = null;
            if (USE_TRIGGERS_FIELD) triggers = new ArrayList();
            Iterator it;

            it = axes.iterator();
            while (it.hasNext()) {
                Axis a = (Axis) it.next();
                String axisName = removeSpaces(a.getName());
                if (USE_TRIGGERS_FIELD) triggers.add(axisName);
                addAllAxisFields(a);
            }
            it = buttons.iterator();
            while (it.hasNext()) {
                Button b = (Button) it.next();
                String buttonName = removeSpaces(b.getName());
                if (USE_TRIGGERS_FIELD) triggers.add(buttonName);
                addAllButtonFields(b);
            }
            it = directionals.iterator();
            while (it.hasNext()) {
                Directional d = (Directional) it.next();
                String dirName = removeSpaces(d.getName());
                if (USE_TRIGGERS_FIELD) triggers.add(dirName);
                addAllDirectionalFields(d);
            }

            // t.addField("ID", joystickID); // need to include Joystick ID?
            // add "button.field" type fields

            if (USE_TRIGGERS_FIELD) event.addField("Triggers", triggers.toArray());
        } catch (EventHeapException ex) {
            ex.printStackTrace();
        }
        return event;
    }
    
    private Event buildBasicEvent() {
        try {
            Event e = new Event("iStuffEvent");
            e.addField("TimeToLive", new Integer(TIME_TO_LIVE));
            e.addField("DeviceType", "Joystick");
            e.addField("Name", this.getFriendlyName());
            e.addField("Description", this.getName());
            e.addField("JoystickNum", new Integer(joystickNum));

            return e;
        } catch (EventHeapException ex) {
            ex.printStackTrace();
            return null;
        }
    }


    // Range of values:
    // for TRANSLATION or ROTATION: [-1.0, 1.0]
    // for SLIDER: [0, 1.0] because Slider has no defined center position

    public static final double MAX_VALUE = 1.0;
    public static final double MIN_VALUE_SLIDER = 0.0;
    public static final double MIN_VALUE_OTHER = -1.0;

    private void addAllAxisFields(Axis axis) throws EventHeapException {
        String axisName = removeSpaces(axis.getName());
        double res = axis.getResolution();
        int primitiveType = axis.getType();

        String axisType;
        int isRelativeInt;
        double min;
        String movementType = "Position";
        switch(primitiveType) {
            case Axis.TRANSLATION:
                axisType = "Translation";
                isRelativeInt = 0;
                movementType = "Velocity";
                min = MIN_VALUE_OTHER; break;
            case Axis.ROTATION:
                axisType = "Rotation";
                isRelativeInt = 0;
                movementType = "Position";
                min = MIN_VALUE_OTHER; break;
            case Axis.SLIDER: default:
                axisType = "Slider";
                isRelativeInt = 0;
                movementType = "Position";
                min = MIN_VALUE_SLIDER; break;
        }

        String[] dimensions = { "Axis" };

        event.addField(axisName + ".Device", "Axis");
        event.addField(axisName + ".Direction", "Input");
        event.addField(axisName + ".Dimensions", dimensions);
        
        // This is a temporary situation until we allow users to bind together multiple
        // axes into a single "joystick" object with multiple dimensions.
        // For now, we represent each axis as a separate device with one "Axis" dimension

        event.addField(axisName + ".Axis.Max", new Double(MAX_VALUE));
        event.addField(axisName + ".Axis.Min", new Double(min));
        event.addField(axisName + ".Axis.Resolution", new Double(res));
        event.addField(axisName + ".Axis.IsRelative", new Integer(isRelativeInt));
        event.addField(axisName + ".Axis.MovementType", movementType);
        event.addField(axisName + ".Axis.AxisType", axisType); 		     // optional field
        event.addField(axisName + ".Axis.IsChanged", new Integer(0));
        addAxisFields(axis);
    }

    private void addAxisFields(Axis axis) throws EventHeapException {
        String axisName = removeSpaces(axis.getName());
        double value = axis.getValue();
        event.addField(axisName + ".Axis.Value", new Double(value));
    }

    // addButtonFields():
    // Possible values of field "ButtonName.ButtonState.Context":
    // 		"Absolute" indicates a toggle button
    //		"Relative" indicates a push button
    // This information is redundantly coded in field
    // "ButtonName.ButtonState.ButtonType"
    
    private void addAllButtonFields(Button button) throws EventHeapException {
        int primitiveType = button.getType();
        String buttonName = removeSpaces(button.getName());
        String buttonType;
        int isRelative = 0;
        switch (primitiveType) {
            case (Button.PUSHBUTTON):
                buttonType = "PushButton";
                isRelative = 1; break;
            case (Button.TOGGLEBUTTON): default:
                buttonType = "ToggleButton";
                isRelative = 0; break;
        }
    
        String[] dimensions = {"ButtonState"};
    
        event.addField(buttonName + ".Device", "Button");
        event.addField(buttonName + ".Direction", "Input");
        event.addField(buttonName + ".Dimensions", dimensions);
    
        event.addField(buttonName + ".ButtonState.Max", new Integer(1));
        event.addField(buttonName + ".ButtonState.Min", new Integer(0));
        event.addField(buttonName + ".ButtonState.Resolution", new Integer(1));
        event.addField(buttonName + ".ButtonState.IsRelative", new Integer(isRelative));
        event.addField(buttonName + ".ButtonState.ButtonType", buttonType);
        addButtonFields(button);
    }

    private void addButtonFields(Button button) throws EventHeapException {
        String buttonName = removeSpaces(button.getName());
        boolean buttonState = button.getState();
        int buttonStateInt;
        if (buttonState) {
            buttonStateInt = 1;
        } else {
            buttonStateInt = 0;
        }
        event.addField(buttonName + ".ButtonState.Value", new Integer(buttonStateInt));
        event.addField(buttonName + ".ButtonState.IsChanged", new Integer(1));
    }	
    
    public static final double MAGNITUDE_MAX = 1.0;
    public static final double MAGNITUDE_MIN = 0.0;
    public static final int DIRECTION_MIN = 0;
    public static final int DIRECTION_MAX = 36000;
    public static final int DIRECTION_RES = 1;
    public static final double XY_MAX = 1.0;
    public static final double XY_MIN = -1.0;
    
    private void addAllDirectionalFields(Directional dir) throws EventHeapException {
        String dirName = removeSpaces(dir.getName());
        double resolution = dir.getResolution();
    
    
        // origin of XY coordinate system is in the bottom left.
    
        String[] dimensions = {"Magnitude", "Direction", "X", "Y"};
    
        event.addField(dirName + ".Device", "Directional");
        event.addField(dirName + ".Direction", "Input");
        event.addField(dirName + ".Dimensions", dimensions);
    
        event.addField(dirName + ".Magnitude.Min", new Double(MAGNITUDE_MIN));
        event.addField(dirName + ".Magnitude.Max", new Double(MAGNITUDE_MAX));
        event.addField(dirName + ".Magnitude.IsRelative", new Integer(1)); 	// absolute?
        event.addField(dirName + ".Magnitude.MovementType", new String("Velocity"));
        event.addField(dirName + ".Magnitude.Resolution", new Double(resolution));
    
        event.addField(dirName + ".Direction.Min", new Integer(DIRECTION_MIN));
        event.addField(dirName + ".Direction.Max", new Integer(DIRECTION_MAX));
        event.addField(dirName + ".Direction.IsRelative", new Integer(0));
        event.addField(dirName + ".Direction.MovementType", new String("Velocity"));
        event.addField(dirName + ".Direction.Resolution", new Integer(DIRECTION_RES));
    
        event.addField(dirName + ".X.Min", new Double(XY_MIN));
        event.addField(dirName + ".X.Max", new Double(XY_MAX));
        event.addField(dirName + ".X.IsRelative", new Integer(0));
        event.addField(dirName + ".X.MovementType", new String("Velocity"));
        event.addField(dirName + ".X.Resolution", new Double(resolution));

        // Resolution for X and Y are approximate,
        // since the actual resolution of the device will be in polar coords
    
        event.addField(dirName + ".Y.Min", new Double(XY_MIN));
        event.addField(dirName + ".Y.Max", new Double(XY_MAX));
        event.addField(dirName + ".Y.IsRelative", new Integer(0));
        event.addField(dirName + ".Y.MovementType", new String("Velocity"));
        event.addField(dirName + ".Y.Resolution", new Double(resolution));

        // Resolution for X and Y are approximate,
        // since the actual resolution of the device will be in polar coords
        addDirectionalFields(dir);
    }

    private void addDirectionalFields(Directional dir) throws EventHeapException {
        boolean isCentered = dir.isCentered();
        String dirName = removeSpaces(dir.getName());
        int direction = dir.getDirection();
        double value = dir.getValue();
        
        // convert from [0,36000] to [0, 2*PI]:
        double radians = (direction/100.0) * (Math.PI/180.0);
        double xComponent = value*Math.sin(radians);
        double yComponent = value*Math.cos(radians);
        
        int isCenteredInt;
        if (isCentered) {
            isCenteredInt = 1;
        } else {
            isCenteredInt = 0;
        }

        event.addField(dirName + ".IsChanged", new Integer(1));
        event.addField(dirName + ".Magnitude.Value", new Double(value));
        event.addField(dirName + ".Magnitude.IsCentered", new Integer(isCenteredInt));
        event.addField(dirName + ".Direction.Value", new Integer(direction));
        event.addField(dirName + ".X.Value", new Double(xComponent));
        event.addField(dirName + ".Y.Value", new Double(yComponent));

    }

    private void addAxisDeltas(JXInputAxisEvent e) throws EventHeapException {
        double delta = e.getDelta();
        Axis axis = e.getAxis();
        String axisName= removeSpaces(axis.getName());
        event.addField(axisName + ".Axis.Delta", new Double(delta));
        event.addField(axisName + ".Axis.IsChanged", new Integer(1));
    }
    
    private void addButtonDeltas(JXInputButtonEvent e) throws EventHeapException {
        Button b = e.getButton();
        String buttonName = removeSpaces(b.getName());
        boolean buttonState = b.getState();
        int buttonStateInt;
        if (buttonState) {
            buttonStateInt = 1;
        } else {
            buttonStateInt = 0;
        }
    
        // The field "ButtonName.ButtonState.Delta" is
        // represented by a boolean. True if this is a ButtonDown event,
        // False if it is a ButtonUp event. This may be a stretching of the
        // concept "Delta", but I believe this reflects the
        // binary nature of the device more accurately than a delta that is
        // an integer or a double.
    
        event.addField(buttonName + ".ButtonState.Delta", new Integer(buttonStateInt));
        event.addField(buttonName + ".ButtonState.IsChanged", new Integer(1));
    }
    
    
    private void addDirectionalDeltas(JXInputDirectionalEvent e) throws EventHeapException {
        Directional dir = e.getDirectional();
        String dirName = removeSpaces(dir.getName());
    
        int newDir = dir.getDirection();
        double newValue = dir.getValue();
        double newRadians = (newDir/100.0) * (Math.PI/180.0);
        double newX = newValue*Math.sin(newRadians);
        double newY = newValue*Math.cos(newRadians);
        
        int dirDelta = e.getDirectionDelta();
        double valueDelta = e.getValueDelta();
        int oldDir = newDir - dirDelta;
        double oldValue = newValue - valueDelta;
    
        // convert from [0,36000] to [0, 2*PI]:
        double oldRadians = (oldDir/100.0) * (Math.PI/180.0);
        double oldX = oldValue*Math.sin(oldRadians);
        double oldY = oldValue*Math.cos(oldRadians);
        double deltaX = newX - oldX;
        double deltaY = newY - oldY;

        event.addField(dirName + ".Direction.Delta", new Integer(dirDelta));
        event.addField(dirName + ".Magnitude.Delta", new Double(valueDelta));
        event.addField(dirName + ".X.Delta", new Double(deltaX));
        event.addField(dirName + ".Y.Delta", new Double(deltaY));
        event.addField(dirName + ".IsChanged", new Integer(1));
    }

    public void resetIsChangedFields() throws EventHeapException {
        Iterator it = axes.iterator();
        while (it.hasNext()) {
            Axis axis = (Axis)it.next();
            String axisName = removeSpaces(axis.getName());
            event.addField(axisName + ".Axis.IsChanged", new Integer(0));
        }
        it = buttons.iterator();
        while (it.hasNext()) {
            Button button = (Button)it.next();
            String buttonName = removeSpaces(button.getName());
            event.addField(buttonName + ".ButtonState.IsChanged", new Integer(0));
        }
        it = directionals.iterator();
        while (it.hasNext()) {
            Directional dir = (Directional)it.next();
            String dirName = removeSpaces(dir.getName());
            event.addField(dirName + ".IsChanged", new Integer(0));
        }
    }
    
    public int numAxes() {
        return axes.size();
    }
    
    public int numButtons() {
        return buttons.size();
    }
    
    public int numDirectionals() {
        return directionals.size();
    }
    
    // Replaces each block of spaces/parentheses/hyphens, except for those
    // at beginning/end of name, with an underscore.
    // example: "X Axis (North-South)"
    // becomes  "X_Axis_North_South"
    
    static String removeSpaces(String text) {
        StringTokenizer st = new StringTokenizer(text," ()-",false);
        String t = st.nextElement().toString();
        while (st.hasMoreElements()) {
            t = t + "_" + st.nextElement().toString();
        }
        return t;
    }

    public void sendEvent() {
        try {
            if (eventChanged) {
                event.addField("EHC_Timestamp", new Long(System.currentTimeMillis()));
                controller.sendEventNow(event);
                resetIsChangedFields();
                eventChanged = false;
            }
        } catch (EventHeapException ex) {
            ex.printStackTrace();
        }
    }

}
