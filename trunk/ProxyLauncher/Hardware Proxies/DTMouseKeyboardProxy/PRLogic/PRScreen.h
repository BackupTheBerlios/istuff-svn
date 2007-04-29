// PRScreen.h

#ifndef _PRSCREEN_H_
#define _PRSCREEN_H_

#include <string>
#include <vector>
using namespace std;
#include "PRGeometry.h"
#include "PRConnection.h"

namespace prlogic {

class PRScreen
{

public:

    PRScreen();
    PRScreen(const string &name, const PRPoint<int> &size);

    const string &getName() const { return m_Name; }
    const PRPoint<int> &getSize() const { return m_Size; }
    PRRect<int> getBounds() const { return PRRect<int>::Make(0,0,m_Size.x,m_Size.y); }
/*
    PRPoint<float> localToRelative(const PRPoint<int> &p)
      { return PRPoint<float>::Make( (float)p.x / (float)m_Size.x, (float)p.y / (float)m_Size.y ); }
    PRPoint<int> relativeToLocal(const PRPoint<float> &p)
      { return PRPoint<int>::Make( (int)(p.x * (float)m_Size.x), (int)(p.y / (float)m_Size.y) ); }
*/

    PRSide getSideAt(int x, int y);
    
    void addConnection(const PRConnection &connection);
//    PRConnection *getConnectionAt(const PRPoint<int> &p);
//    PRConnection *getConnectionAt(const PRPoint<float> &p);
    PRConnection *getConnectionAt(PRSide side, float x);

protected:

    string m_Name;
    PRPoint<int> m_Size;
    vector<PRConnection> m_Connections;
};

} // namespace prlogic

#endif