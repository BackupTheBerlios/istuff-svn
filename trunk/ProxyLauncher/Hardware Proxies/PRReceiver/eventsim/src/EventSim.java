// EventSim.java

class EventSim
{
    static {
        System.loadLibrary("EventSim");
    }

    public static native void enableEventStateCombining(boolean enable);
    public static native void postMouseEvent(int x, int y, int leftButton, int rightButton, int middleButton);
    public static native void postScrollEvent(int value);
    public static native void postKeyEvent(int charCode, int keyCode, int state);

}