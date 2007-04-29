// Event.cpp

#include "Event.h"

namespace eheap {

string EH_EVENTTYPE = "EventType";
string EH_TIMETOLIVE = "TimeToLive";
string EH_SOURCE = "Source";
string EH_TARGET = "Target";
string EH_SOURCEAPPLICATION = "SourceApplication";
string EH_TARGETAPPLICATION = "TargetApplication";
string EH_SOURCEDEVICE = "SourceDevice";
string EH_TARGETDEVICE = "TargetDevice";
string EH_SOURCEPERSON = "SourcePerson";
string EH_TARGETPERSON = "TargetPerson";
string EH_SOURCEGROUP = "SourceGroup";
string EH_TARGETGROUP = "TargetGroup";
string EH_SESSIONID = "SessionID";
string EH_SEQUENCENUM = "SequenceNum";
string EH_EVENTHEAPVERSION = "EventHeapVersion";

string EH_INVALID_EVENT = "INVALID_EVENT";
int EH_DEFAULT_TTL = 120*1000;
    
Event::Event(const string &eventType, int timeToLive)
{
    (*this)[EH_EVENTTYPE].set(eventType, eventType);
    (*this)[EH_TIMETOLIVE].set(timeToLive, EH_FORMAL);
    (*this)[EH_SOURCE].set(EH_AUTOSET, EH_STRING);
    (*this)[EH_TARGET].set(EH_STRING, EH_AUTOSET_OVERRIDEABLE);
    (*this)[EH_SOURCEAPPLICATION].set(EH_AUTOSET, EH_STRING);
    (*this)[EH_TARGETAPPLICATION].set(EH_STRING, EH_AUTOSET_OVERRIDEABLE);
    (*this)[EH_SOURCEDEVICE].set(EH_AUTOSET, EH_STRING);
    (*this)[EH_TARGETDEVICE].set(EH_STRING, EH_AUTOSET_OVERRIDEABLE);
    (*this)[EH_SOURCEPERSON].set(EH_AUTOSET, EH_VIRTUAL);
    (*this)[EH_TARGETPERSON].set(EH_STRING, EH_AUTOSET_OVERRIDEABLE);
    (*this)[EH_SOURCEGROUP].set(EH_AUTOSET, EH_VIRTUAL);
    (*this)[EH_TARGETGROUP].set(EH_STRING, EH_AUTOSET_OVERRIDEABLE);
    (*this)[EH_SESSIONID].set(EH_AUTOSET, EH_VIRTUAL);
    (*this)[EH_SEQUENCENUM].set(EH_AUTOSET, EH_VIRTUAL);
    (*this)[EH_EVENTHEAPVERSION].set(EH_AUTOSET, EH_VIRTUAL);
}

} // namespace eheap