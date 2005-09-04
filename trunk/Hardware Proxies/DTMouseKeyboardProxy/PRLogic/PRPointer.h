// PRPointer.h

#ifndef _PRPOINTER_H_
#define _PRPOINTER_H_

#include "PRGeometry.h"

#define PR_NUM_BUTTONS 3

namespace prlogic {

class PRPointer
{

public:

    PRPointer();

    const PRPoint<int> &getLocation() { return m_Location; }
    int getX() { return m_Location.x; }
    int getY() { return m_Location.y; }
    void set(int x, int y);
    void set(const PRPoint<int> &p) { set(p.x, p.y); }
    void delta(int x, int y);
    void delta(const PRPoint<int> &p) { delta(p.x, p.y); }

    void constrain(const PRRect<int> &bounds);
    
    bool getButton(int b);
    void setButton(int b, bool state);
    
protected:

    PRPoint<int> m_Location;
    bool m_Button[PR_NUM_BUTTONS];
    
};

} // namespace prlogic

#endif