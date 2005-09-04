#include "PRPointer.h"

namespace prlogic {
    
PRPointer::PRPointer()
{
    m_Location.set(0,0);
    for(int i=0; i<PR_NUM_BUTTONS; i++) m_Button[i] = false;
}

void PRPointer::set(int x, int y)
{
    m_Location.set(x,y);
}

void PRPointer::delta(int x, int y)
{
    m_Location.delta(x,y);
}

bool PRPointer::getButton(int b)
{
    if(b>=0 && b<PR_NUM_BUTTONS) return m_Button[b];
    return false;
}

void PRPointer::setButton(int b, bool state)
{
    if(b>=0 && b<PR_NUM_BUTTONS) m_Button[b] = state;
}

void PRPointer::constrain(const PRRect<int> &bounds)
{
    if (m_Location.x < bounds.minX()) m_Location.x = bounds.minX();
    if (m_Location.x > bounds.maxX()) m_Location.x = bounds.maxX();
    if (m_Location.y < bounds.minY()) m_Location.y = bounds.minY();
    if (m_Location.y > bounds.maxY()) m_Location.y = bounds.maxY();
}

} // namespace prlogic