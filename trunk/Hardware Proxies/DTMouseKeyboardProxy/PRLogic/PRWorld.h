// PRWorld.h

#ifndef _PRWORLD_H_
#define _PRWORLD_H_

#include "PRKeyCodes.h"
#include "PRPointer.h"
#include "PRScreen.h"

#include "jph.h"
using namespace jph;

#include "EventHeap.h"
using namespace eheap;

namespace prlogic {
    
class PRWorld
{

public:

    static PropertyHash &ReadSettings(const char *fileName);
    
    PRWorld(PropertyHash &settings);
    ~PRWorld();

    bool isReady() { return m_EventHeap->isReady(); }
    bool isSending() { return m_Sending; }

    #define PR_ABSOLUTE false
    #define PR_RELATIVE true
    void updateMousePosition(int x, int y, bool relative = false);
    void updateMouseButton(int button, bool isDown);
    void updateScrollWheel(int value);
    void updateKeyState(int charCode, int keyCode, bool isDown);
    void stopSending();
    
    const PRPoint<int> &getMouseLocation() { return m_Pointer.getLocation(); }
    
protected:

    EventHeap *m_EventHeap;

    map<string,PRScreen> m_Screens;
    PRScreen *m_CurrentScreen;
    PRScreen *m_StartScreen;
    
    PRPointer m_Pointer;
    bool m_Sending;
	bool thread_listening;

    void checkForScreenChange();
	
    void sendMouseEvent();
    void sendScrollEvent(int value);
    void sendKeyEvent(int charCode, int keyCode, bool isDown);
    void sendLeaveEvent();
    
};

} // namespace prlogic

#endif