// Event.h

#ifndef _EVENT_H_
#define _EVENT_H_

#include "Tuple.h"

namespace eheap {

extern string EH_EVENTTYPE;
extern string EH_TIMETOLIVE;
extern string EH_SOURCE;
extern string EH_TARGET;
extern string EH_SOURCEAPPLICATION;
extern string EH_TARGETAPPLICATION;
extern string EH_SOURCEDEVICE;
extern string EH_TARGETDEVICE;
extern string EH_SOURCEPERSON;
extern string EH_TARGETPERSON;
extern string EH_SOURCEGROUP;
extern string EH_TARGETGROUP;
extern string EH_SESSIONID;
extern string EH_SEQUENCENUM;
extern string EH_EVENTHEAPVERSION;
    
extern string EH_INVALID_EVENT;
extern int EH_DEFAULT_TTL;

class Event : public Tuple
{

public:
    
    Event(const string &eventType = EH_INVALID_EVENT, int timeToLive = EH_DEFAULT_TTL);

};

typedef vector<Event> EventArray;

} // namespace eheap

#endif