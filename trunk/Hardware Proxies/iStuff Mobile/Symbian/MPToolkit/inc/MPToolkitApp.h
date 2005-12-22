/*
* ============================================================================
*  Name     : CMPToolkitApp from MPToolkitApp.h
*  Part of  : MPToolkit
*  Created  : 01.11.2005 by Faraz Ahmed Memon
*  Description:
*     Declares main application class.
*  Version  :
*  Copyright: i10 RWTH Aachen
* ============================================================================
*/

#ifndef MPTOOLKITAPP_H
#define MPTOOLKITAPP_H


#include <aknapp.h>

const TUid KUidMPToolkit = { 0x07D8FC33 };

class CMPToolkitApp : public CAknApplication
{
    private:

        CApaDocument* CreateDocumentL();
        TUid AppDllUid() const;
};

#endif