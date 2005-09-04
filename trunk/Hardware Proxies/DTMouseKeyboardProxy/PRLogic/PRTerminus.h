// PRTerminus.h

#ifndef _PRTERMINUS_H_
#define _PRTERMINUS_H_

#include <string>
#include "PRGeometry.h"

namespace prlogic {

class PRTerminus
{

public:

    PRTerminus(const string &screen, const PRRect<float> &bounds);

    const string &getScreen() const { return m_Screen; }
    const PRRect<float> &getBounds() const { return m_Bounds; }
    
protected:
    
     string m_Screen;
     PRRect<float> m_Bounds;
     
};

} // namespace prlogic

#endif