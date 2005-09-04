// PRScreen.cpp

#include "PRScreen.h"

namespace prlogic {

PRScreen::PRScreen()
{
}
    
PRScreen::PRScreen(const string &name, const PRPoint<int> &size)
    : m_Name(name), m_Size(size)
{
}


PRSide PRScreen::getSideAt(int x, int y)
{
    // preference left-right over top-bottom (at corners)
    if (x <= 0) return PR_LEFT;
    else if (x >= m_Size.x) return PR_RIGHT;
    else if (y <= 0) return PR_TOP;
    else if (y >= m_Size.y) return PR_BOTTOM;
    return PR_NONE;
}

void PRScreen::addConnection(const PRConnection &connection)
{
    m_Connections.push_back(connection);
}

/*
PRConnection *PRScreen::getConnectionAt(const PRPoint<int> &p)
{
    return getConnectionAt(localToRelative(p));
}

PRConnection *PRScreen::getConnectionAt(const PRPoint<float> &p)
{
    vector<PRConnection>::iterator i;
    for(i = m_Connections.begin(); i != m_Connections.end(); i++)
    {
        if (i->getStart().getBounds().contains(p)) return i;
    }
    return NULL;
}
*/

PRConnection *PRScreen::getConnectionAt(PRSide side, float x)
{
    if (side == PR_NONE) return NULL;
    vector<PRConnection>::iterator i;
    for(i = m_Connections.begin(); i != m_Connections.end(); i++)
    {
        if (i->getFromSide() == side && i->getFromRange().contains(x)) return &(*i);
    }
    return NULL;
}

} // namespace prlogic