// PRConnection.cpp

#include "PRConnection.h"

namespace prlogic {

PRConnection::PRConnection(const string &fromScreen, PRSide fromSide, const PRRange<float> &fromRange,
                const string &toScreen, PRSide toSide, const PRRange<float> &toRange)
    : m_FromScreen(fromScreen), m_ToScreen(toScreen),
    m_FromSide(fromSide), m_ToSide(toSide),
    m_FromRange(fromRange), m_ToRange(toRange)
{
}

} // namespace prlogic