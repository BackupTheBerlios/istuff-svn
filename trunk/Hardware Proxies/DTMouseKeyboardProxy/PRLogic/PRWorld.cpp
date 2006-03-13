#include "PRWorld.h"
#include <fstream>


#define STR_TO_INT(a) (atoi((a).c_str()))
#define STR_TO_FLOAT(a) (atof((a).c_str()))

namespace prlogic {

PRSide STR_TO_SIDE(const string &s)
{
    if (s == "left") return PR_LEFT;
    else if (s == "right") return PR_RIGHT;
    else if (s == "top") return PR_TOP;
    else if (s == "bottom") return PR_BOTTOM;
    else return PR_NONE;
}

PRPoint<int> LIST_TO_POINT_INT(PropertyList &l)
{
    if (l.size() < 2) { cout << "LIST_TO_POINT_INT: list too short" << endl; return PRPoint<int>::Make(0,0); }
    return PRPoint<int>::Make( STR_TO_INT(l[0].str()), STR_TO_INT(l[1].str()) );
}

PRRange<float> LIST_TO_RANGE_FLOAT(PropertyList &l)
{
    if (l.size() < 2) { cout << "LIST_TO_RANGE_FLOAT: list too short" << endl; return PRRange<float>::Make(0,0); }
    return PRRange<float>::Make( STR_TO_FLOAT(l[0].str()), STR_TO_FLOAT(l[1].str()) );
}
    
PropertyHash &PRWorld::ReadSettings(const char *fileName)
{
    PropertyHash &settings = *new PropertyHash();
    
    ifstream f(fileName);
    if (f) f >> settings;
    else cerr << "couldn't open config file: " << fileName << endl;

    return settings;
}

PRWorld::PRWorld(PropertyHash &settings)
{
    m_Sending = false;
	thread_listening = true;
    m_EventHeap = new EventHeap(settings["eheap"].str());


	srcMachineName = settings["srcMachineName"].str();
	//strcpy(&srcMachineName, settings["srcMachineName"].str());
	cout << "Machinename: " << srcMachineName;
    
    PropertyList::iterator i;

    PropertyList &screens = settings["screens"].list();
    for(i = screens.begin(); i != screens.end(); i++)
    {
        PropertyHash &screenHash = i->hash();
        
        string &name = screenHash["name"].str();
        PRPoint<int> size = LIST_TO_POINT_INT(screenHash["size"].list());
        
        PRScreen screen(name, size);

        PropertyList &connections = screenHash["connections"].list();
        PropertyList::iterator j;
        for(j = connections.begin(); j != connections.end(); j++)
        {
            PropertyHash &connectionHash = j->hash();
            PRSide fromSide = STR_TO_SIDE(connectionHash["from_side"].str());
            PRRange<float> fromRange = LIST_TO_RANGE_FLOAT(connectionHash["from_range"].list());
            string &toScreen = connectionHash["to_screen"].str();
            PRSide toSide = STR_TO_SIDE(connectionHash["to_side"].str());
            PRRange<float> toRange = LIST_TO_RANGE_FLOAT(connectionHash["to_range"].list());
            PRConnection connection(name, fromSide, fromRange, toScreen, toSide, toRange);
            screen.addConnection(connection);
        }
        
        m_Screens.insert(make_pair(name,screen));
    }

    m_StartScreen = &m_Screens[settings["initial_screen"].str()];
    m_CurrentScreen = &m_Screens["LOCAL"];
	
	//EY's modification:
	//Start a thread to wait for change output dev. event s.t. current screen will be reset such as :checkForScreenChange() at line 123
	//Wait for CHANGE_OUTPUT
	//[NSThread detachNewThreadSelector: @selector( checkForFocusChange: ) toTarget:self withObject:nil];
	/*
	int errcode;
	pthread_t threads[1];
	//int ids[1];
	
	
	if (errcode=pthread_create(&threads[1],
                    NULL,                    
                    PRWorld::checkForFocusChange,               
                    NULL)){
	}*/
}

PRWorld::~PRWorld()
{
	thread_listening  = false;
    delete m_EventHeap;
}

void PRWorld::updateMousePosition(int x, int y, bool relative)
{
    if (relative) m_Pointer.delta(x,y);
    else m_Pointer.set(x,y);
    m_Pointer.constrain(m_CurrentScreen->getBounds());
    checkForScreenChange();
    m_Sending = !(m_CurrentScreen->getName() == "LOCAL");
    if (m_Sending) sendMouseEvent();
}

void PRWorld::updateMouseButton(int button, bool isDown)
{
    m_Pointer.setButton(button, isDown);
    if (m_Sending) sendMouseEvent();
}

void PRWorld::updateScrollWheel(int value)
{
    if (m_Sending) sendScrollEvent(value);
}

void PRWorld::updateKeyState(int charCode, int keyCode, bool isDown)
{
    if (m_Sending) sendKeyEvent(charCode, keyCode, isDown);
}

void PRWorld::stopSending()
{
    if (m_Sending) {
        sendLeaveEvent();
        m_StartScreen = m_CurrentScreen;
        m_Sending = false;
    }
}

void PRWorld::checkForScreenChange()
{
	m_CurrentScreen = &m_Screens["default"]; //With just this line the pointer can leaves the screen put never come back
	//unless using the key combination crtl-cmd-q
	PRSide side = m_CurrentScreen->getSideAt(m_Pointer.getX(), m_Pointer.getY());
	if (side == PR_LEFT)
		printf("left hit\n");
	else if (side == PR_RIGHT)
		printf("right hit\n");
	else if (side == PR_TOP)
		printf("top hit\n");
	else if (side == PR_BOTTOM)
		printf(" bottom hit\n");

/*
    float z = 0;
    PRSide side = m_CurrentScreen->getSideAt(m_Pointer.getX(), m_Pointer.getY());
    if (side == PR_LEFT || side == PR_RIGHT) z = (float)m_Pointer.getY() / (float)m_CurrentScreen->getSize().y;
    if (side == PR_TOP || side == PR_BOTTOM) z = (float)m_Pointer.getX() / (float)m_CurrentScreen->getSize().x;
    PRConnection *connection = m_CurrentScreen->getConnectionAt(side, z);
    if (connection != NULL)
    {
        sendLeaveEvent();
        
        // if we're going back to local, save the current screen so we can go back to it
        if (connection->getToScreen() == "LOCAL") m_StartScreen = m_CurrentScreen;

        // if we're just starting, go to the designated start screen
        if (connection->getToScreen() == "START") m_CurrentScreen = m_StartScreen;
        else m_CurrentScreen = &m_Screens[connection->getToScreen()];

        //cout << "changing to screen: " << m_CurrentScreen->getName() << endl;

        float newz = connection->getFromRange().translate(z, connection->getToRange());
        if (connection->getToSide() == PR_LEFT)
            m_Pointer.set(0, (int)(newz * m_CurrentScreen->getSize().y));
        if (connection->getToSide() == PR_RIGHT)
            m_Pointer.set(m_CurrentScreen->getSize().x, (int)(newz * m_CurrentScreen->getSize().y));
        if (connection->getToSide() == PR_TOP)
            m_Pointer.set((int)(newz * m_CurrentScreen->getSize().x), 0);
        if (connection->getToSide() == PR_BOTTOM)
            m_Pointer.set((int)(newz * m_CurrentScreen->getSize().x), m_CurrentScreen->getSize().y);
    }*/
}

void PRWorld::sendMouseEvent()
{
    if (!m_Sending) return;
    //cout << "sending to " << m_CurrentScreen->getName() << ": ";
    //cout << "mouse = (" << m_Pointer.getX() << ", " << m_Pointer.getY() << ")";
    //cout << " L " << m_Pointer.getButton(0) << ", R " << m_Pointer.getButton(1) << ", M " << m_Pointer.getButton(2);
    //cout << endl;
    Event event("PointRightEvent", 500);
    event["PointRightEventType"].setPostValue("MouseEvent");
    event["Screen"].setPostValue(m_CurrentScreen->getName());
    event["X"].setPostValue(m_Pointer.getX());
    event["Y"].setPostValue(m_Pointer.getY());
    event["LeftButton"].setPostValue(m_Pointer.getButton(0)?1:0);
    event["RightButton"].setPostValue(m_Pointer.getButton(1)?1:0);
    event["MiddleButton"].setPostValue(m_Pointer.getButton(2)?1:0);
	event["srcMachineName"].setPostValue(srcMachineName);
	event["level"].setPostValue(0);
    m_EventHeap->putEvent(event);
}

void PRWorld::sendScrollEvent(int value)
{
    if (!m_Sending) return;
    //cout << "sending to " << m_CurrentScreen->getName() << ": ";
    //cout << "scroll = " << value;
    //cout << endl;
    Event event("PointRightEvent", 500);
    event["PointRightEventType"].setPostValue("ScrollEvent");
    event["Screen"].setPostValue(m_CurrentScreen->getName());
    event["Value"].setPostValue(value);
	event["srcMachineName"].setPostValue(srcMachineName);
	event["level"].setPostValue(0);
    m_EventHeap->putEvent(event);
}

void PRWorld::sendKeyEvent(int charCode, int keyCode, bool isDown)
{
    if (!m_Sending) return;
    //cout << "sending to " << m_CurrentScreen->getName() << ": ";
    //cout << "char = " << charCode << ", key = " << keyCode << ", state = " << isDown;
    //cout << endl;
	//This one has the target set to "default", PatchPanel is to rewrite this field
    Event event("PointRightEvent", 500);
    event["PointRightEventType"].setPostValue("KeyEvent");
    event["Screen"].setPostValue(m_CurrentScreen->getName());
    event["CharCode"].setPostValue(charCode);
    event["KeyCode"].setPostValue(keyCode);
    event["State"].setPostValue(isDown?1:0);
	event["srcMachineName"].setPostValue(srcMachineName);
	event["level"].setPostValue(0);
    m_EventHeap->putEvent(event);
	
	
	//This one has no target
	Event eventK("KEYBOARD", 500);
	//printf("%d `%s %c \n",charCode, charCode, charCode);
    eventK["code"].setPostValue(keyCode);
	char key[2];
	key[0] = charCode;
	key[1] = '\0';
    eventK["key"].setPostValue(key);
	eventK["isDown"].setPostValue(isDown?1:0);
	eventK["level"].setPostValue(0);
	eventK["srcMachineName"].setPostValue(srcMachineName);
	eventK["level"].setPostValue(0);
	m_EventHeap->putEvent(eventK);
}

void PRWorld::sendLeaveEvent()
{
    if (!m_Sending) return;
    //cout << "sending to " << m_CurrentScreen->getName() << ": leaving" << endl;
    Event event("PointRightEvent", 500);
    event["PointRightEventType"].setPostValue("LeaveEvent");
    event["Screen"].setPostValue(m_CurrentScreen->getName());
	event["srcMachineName"].setPostValue(srcMachineName);
	event["level"].setPostValue(0);
    m_EventHeap->putEvent(event);
		
	Event eventMouseLeave("PointRightEvent", 500);
    eventMouseLeave["PointRightEventType"].setPostValue("MouseEvent");
    eventMouseLeave["Screen"].setPostValue(m_CurrentScreen->getName());
    eventMouseLeave["X"].setPostValue(0);
    eventMouseLeave["Y"].setPostValue(0);
    eventMouseLeave["LeftButton"].setPostValue(0);
    eventMouseLeave["RightButton"].setPostValue(0);
    eventMouseLeave["MiddleButton"].setPostValue(0);
	eventMouseLeave["srcMachineName"].setPostValue(srcMachineName);
	eventMouseLeave["level"].setPostValue(0);
    m_EventHeap->putEvent(eventMouseLeave);
}

} // namespace prlogic