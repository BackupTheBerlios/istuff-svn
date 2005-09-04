// EventHeap.h

#ifndef _EVENTHEAP_H_
#define _EVENTHEAP_H_

#include "Thread.h"
//#include "Mutex.h"
//#include "Semaphore.h"
using namespace thread;

#include "Socket.h"
using namespace net;

#include "Event.h"
#include "WireBundle.h"

namespace eheap {

extern uint16 EH_DEFAULT_PORT;
    
class ConnectionThread;

class EventHeap
{

public:
    
    EventHeap(const string &server, uint16 port = EH_DEFAULT_PORT);
    virtual ~EventHeap();

    void setSource(const string &source);
    void setApplication(const string &application);
    void setDevice(const string &device);
    void setPerson(const string &person);
    void setGroup(const string &group);

    string &getSource() { return m_Source; }
    string &getApplication() { return m_Application; }
    string &getDevice() { return m_Device; }
    string &getPerson() { return m_Person; }
    string &getGroup() { return m_Group; }

    bool isReady();
    
    void putEvent(Event &event);
    
    Event *getEvent(Event &templateEvent);
    Event *removeEvent(Event &templateEvent);
    void deleteEvent(Event &event);
    
    Event *waitForEvent(Event &templateEvent);
    Event *waitToRemoveEvent(Event &templateEvent);
    
    EventArray *snoopEvents(Event &templateEvent);
    EventArray *getAll();
    
    void clear();
    
    //EventRegistration registerForEvents(vector<Event> templateEvents, EventCallback callback);
    //EventRegistration registerForAll(EventCallback callback);

protected:

    string m_Server;
    uint16 m_Port;
    int m_SessionID;

    string m_Source, m_Postfix;
    string m_Application;
    string m_Device;
    string m_Person;
    string m_Group;

    bool m_HasPerson;
    bool m_HasGroup;
    

    Socket m_Socket;
    bool m_HandshakeCompleted;
    ConnectionThread *m_ConnectionThread;
    
    
    map<string,int> m_LocalSequenceNumMap;
    SourceInfoMap m_SourceInfoMap;

    
    void sendWireBundle(WireBundle &wb);


    friend class ConnectionThread;
};


class ConnectionThread : public Runnable
{
    
public:
    
    ConnectionThread(EventHeap *eventheap);
    virtual ~ConnectionThread();
    void run();
    
protected:

    Thread *m_Thread;
    bool m_Run;
    EventHeap *m_EventHeap;
    bool m_HandshakeSent;

};

} // namespace eheap

#endif
