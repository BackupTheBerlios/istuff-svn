/*
* ============================================================================
*  Name     : CMPToolkitDocument from MPToolkitDocument.h
*  Part of  : MPToolkit
*  Created  : 01.11.2005 by Faraz Ahmed Memon
*  Description:
*     Declares document for application.
*  Version  :
*  Copyright: i10 RWTH Aachen
* ============================================================================
*/

#ifndef MPTOOLKITDOCUMENT_H
#define MPTOOLKITDOCUMENT_H


#include <akndoc.h>
   
class  CEikAppUi;

class CMPToolkitDocument : public CAknDocument
{
    public:
        
		static CMPToolkitDocument* NewL(CEikApplication& aApp);
        virtual ~CMPToolkitDocument();

    private:

        CMPToolkitDocument(CEikApplication& aApp);
        void ConstructL();
        CEikAppUi* CreateAppUiL();
    };

#endif