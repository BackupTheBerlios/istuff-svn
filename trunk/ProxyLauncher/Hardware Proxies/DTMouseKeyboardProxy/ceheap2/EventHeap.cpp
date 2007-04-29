// EventHeap.cpp

#include "EventHeap.h"

#include "Util.h"

#include <iostream>
using namespace std;

#define DEBUG 1

namespace eheap {

int EH_EVENT_HEAP_VERSION_NUM = 2;

uint16 EH_DEFAULT_PORT = 4535;
string EH_WIRE_PROTOCOL_VERSION = "EHWPv1";

string EH_DEFAULT_SOURCE = "DefaultSource";
string EH_DEFAULT_APPLICATION = "DefaultApplication";
string EH_DEFAULT_DEVICE = "DefaultDevice";

string EH_PUT_EVENT = "putEvent";

EventHeap::EventHeap(const string &server, uint16 port)
{
    m_Server = server;
    m_Port = port;
    
    m_SessionID = randomInt();
    m_Postfix = "_" + intToHex(m_SessionID);
    
    setSource(EH_DEFAULT_SOURCE);
    setApplication(EH_DEFAULT_APPLICATION);
    setDevice(EH_DEFAULT_DEVICE);
    setPerson("");
    setGroup("");

    m_HandshakeCompleted = false;
    m_ConnectionThread = new ConnectionThread(this);
}

EventHeap::~EventHeap()
{
    delete m_ConnectionThread;
}

void EventHeap::setSource(const string &source) { m_Source = source + m_Postfix; }
void EventHeap::setApplication(const string &application) { m_Application = application; }
void EventHeap::setDevice(const string &device) { m_Device = device; }
void EventHeap::setPerson(const string &person) { m_Person = person; m_HasPerson = (m_Person.length() > 0); }
void EventHeap::setGroup(const string &group) { m_Group = group; m_HasGroup = (m_Person.length() > 0); }

bool EventHeap::isReady()
{
    return (m_Socket.isConnected() && m_HandshakeCompleted);
}

void EventHeap::sendWireBundle(WireBundle &wb)
{
    if (!isReady()) return;

    //if (DEBUG) cout << "sending bundle" << endl;
    
    ByteString bytes;
    wb.writeToBytes(bytes);
    m_Socket.write(bytes);
   /* 
    if (DEBUG) cout << "waiting for response..." << endl;

    if (m_Socket.poll(5*SOCKTIME_SECOND)>0)
    {
        if (DEBUG) cout << "got response: " << endl;
        WireBundle response(m_Socket);
        if (DEBUG) cout << response << endl;
    } else {
        if (DEBUG) cout << "no response!" << endl;
    }
 */
}

void EventHeap::putEvent(Event &event)
{
    if (!isReady()) return;

    event[EH_SOURCE].setPostValue(m_Source);
    event[EH_SOURCEAPPLICATION].setPostValue(m_Application);
    event[EH_SOURCEDEVICE].setPostValue(m_Device);

    event[EH_SESSIONID].setPostValue(m_SessionID);
    event[EH_EVENTHEAPVERSION].setPostValue(EH_EVENT_HEAP_VERSION_NUM);

    int seqNum = ++m_LocalSequenceNumMap[event[EH_EVENTTYPE].getPostValue().getString()];
    event[EH_SEQUENCENUM].setPostValue(seqNum);

    WireBundle wb;
    wb.setDestinationTag(EH_PUT_EVENT);
    wb.setReturnTag("ACK");
    TupleArray tuples(1, event);
    wb.setTuples(tuples);
    sendWireBundle(wb);
}

Event *EventHeap::getEvent(Event &templateEvent)
{
    return NULL;
}

Event *EventHeap::removeEvent(Event &templateEvent)
{
    return NULL;
}

void EventHeap::deleteEvent(Event &event)
{

}

Event *EventHeap::waitForEvent(Event &templateEvent)
{
    return NULL;
}

Event *EventHeap::waitToRemoveEvent(Event &templateEvent)
{
    return NULL;
}

EventArray *EventHeap::snoopEvents(Event &templateEvent)
{
    return NULL;
}

EventArray *EventHeap::getAll()
{
    return NULL;
}

void EventHeap::clear()
{

}



ConnectionThread::ConnectionThread(EventHeap *eventheap)
{
    m_EventHeap = eventheap;
    m_HandshakeSent = false;
    m_EventHeap->m_Socket.create(SOCKTYPE_TCP);
    m_Run = true;
    m_Thread = new Thread(this);
}

ConnectionThread::~ConnectionThread()
{
    m_Run = false;
    m_Thread->join();
    delete m_Thread;
    m_EventHeap->m_Socket.close();
}

void ConnectionThread::run()
{
    while (m_Run)
    {
        if (m_EventHeap->m_Socket.isConnected())
        {
            if (m_EventHeap->m_HandshakeCompleted)
            {
                
                if (m_EventHeap->m_Socket.poll(SOCKTIME_SECOND)>0)
                {
                    //if (DEBUG) cout << "got wirebundle: " << endl;
                    WireBundle wb(m_EventHeap->m_Socket);
                    //if (DEBUG) cout << wb;
                    if(!m_EventHeap->m_Socket.isConnected())
                        if (DEBUG) cout << "lost connection  to " << m_EventHeap->m_Server << ":" << m_EventHeap->m_Port << endl;
                }
                
                //wait(2000);
            }
            else
            {
                if (m_HandshakeSent)
                {
                    if (m_EventHeap->m_Socket.poll(SOCKTIME_SECOND)>0)
                    {
                        if (DEBUG) cout << "got handshake response: ";
                        string &response = m_EventHeap->m_Socket.readUTF8();
                        if (DEBUG) cout << response << endl;
                        if (response == EH_WIRE_PROTOCOL_VERSION)
                        {
                            if (DEBUG) cout << "handshake succeeded" << endl;
                            m_EventHeap->m_HandshakeCompleted = true;
                        }
                        else
                        {
                            if (DEBUG) cout << "handshake failed" << endl;
                            m_HandshakeSent = false;
                        }
                    }
                }
                else
                {
                    if (DEBUG) cout << "sending handshake: " << EH_WIRE_PROTOCOL_VERSION << endl;
                    m_EventHeap->m_Socket.writeUTF8(EH_WIRE_PROTOCOL_VERSION);
                    m_HandshakeSent = true;
                }
            }
        }
        else
        {    
            m_HandshakeSent = false;
            m_EventHeap->m_HandshakeCompleted = false;
            m_EventHeap->m_Socket.connect(getAddress(m_EventHeap->m_Server), m_EventHeap->m_Port);
            if(m_EventHeap->m_Socket.isConnected())
            {
                if (DEBUG) cout << "connected to " << m_EventHeap->m_Server << ":" << m_EventHeap->m_Port << endl;
            }
            else
            {
                if (DEBUG) cout << "couldn't connect to " << m_EventHeap->m_Server << ":" << m_EventHeap->m_Port << endl;
                wait(2000);
            }
        }
    }
}



} // namespace eheap
