// PRConnection.h

#ifndef _PRCONNECTION_H_
#define _PRCONNECTION_H_

#include <string>
using namespace std;
#include "PRGeometry.h"

namespace prlogic {
 
class PRConnection
{

public:

    PRConnection(const string &fromScreen, PRSide fromSide, const PRRange<float> &fromRange,
                 const string &toScreen, PRSide toSide, const PRRange<float> &toRange);

    const string &getFromScreen() const { return m_FromScreen; }
    PRSide getFromSide() const { return m_FromSide; }
    const PRRange<float> &getFromRange() const { return m_FromRange; }
    const string &getToScreen() const { return m_ToScreen; }
    PRSide getToSide() const { return m_ToSide; }
    const PRRange<float> &getToRange() const { return m_ToRange; }
    
protected:

    string m_FromScreen, m_ToScreen;
    PRSide m_FromSide, m_ToSide;
    PRRange<float> m_FromRange, m_ToRange;
    
};

} // namespace prlogic

#endif