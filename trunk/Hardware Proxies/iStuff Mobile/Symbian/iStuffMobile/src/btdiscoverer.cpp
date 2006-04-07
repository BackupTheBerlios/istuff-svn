/*
 * Copyright (c) 2006
 * Media informatics Department
 * RWTH Aachen Germany
 * http://media.informatik.rwth-aachen.de
 *
 * Redistribution and use of the source code and binary, with or without
 * modification, are permitted under OPI Artistic License 
 * (http://www.opensource.org/licenses/artistic-license.php) provided that 
 * the source code retains the above copyright notice and the following 
 * disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors:	  Faraz Ahmed Memon
 *			  Tico Ballagas
 *
 * Version:	  1.0
 */

#include <eiklabel.h>
#include <bt_sock.h>
#include <iStuffMobile.rsg>

#include "Btdiscoverer.h"

#define KListPosition TPoint(0,0)



CBTDiscoverer* CBTDiscoverer::NewL(RFileLogger* aLog, CCodeListener* aCodeListener)
{
	CBTDiscoverer* self = CBTDiscoverer::NewLC(aLog,aCodeListener);
    CleanupStack::Pop(self);
    return self;
}

CBTDiscoverer* CBTDiscoverer::NewLC(RFileLogger* aLog, CCodeListener* aCodeListener)
{
	CBTDiscoverer* self = new (ELeave) CBTDiscoverer(aLog,aCodeListener);
    CleanupStack::PushL(self);
    return self;
}

void CBTDiscoverer::ConstructL(const TRect& aRect)
{
	
	CreateWindowL();
 

	TUUID serviceClass(0x1101);
	iSdpSearchPattern = CSdpSearchPattern::NewL();
    iSdpSearchPattern->AddL(serviceClass);

    iMatchList = CSdpAttrIdMatchList::NewL();
    iMatchList->AddL(TAttrRange(0x4,0x0100)); // get only names
    iAgent = NULL;

	iPortList = new (ELeave) CAknSingleNumberStyleListBox();
	iPortList->SetContainerWindowL(*this);
	iPortList->SetListBoxObserver(this);
//	iPortList->MakeVisible(EFalse);

	TResourceReader reader;
	CCoeEnv::Static()->CreateResourceReaderLC(reader,R_ISTUFFMOBILE_SERVICE_LIST);
	iPortList->ConstructFromResourceL(reader);
	CleanupStack::PopAndDestroy();

	SetupScrollBarsL();

	/*iServiceName = new TUint16[3];
	iServiceName[0] = 'h';
	iServiceName[1] = 'e';
	iServiceName[2] = '\0';
	AddItemToList();*/

	SetRect(aRect);
	ActivateL();
}

CBTDiscoverer::CBTDiscoverer(RFileLogger* aLog, CCodeListener* aCodeListener)  
{		
	iLog = aLog;
	iCodeListener = aCodeListener;
	iServicePort = 0;
	iServiceName = NULL;
}

CBTDiscoverer::~CBTDiscoverer()
{
    delete iAgent;
    iAgent = NULL;

    delete iMatchList;
    iMatchList = NULL;

    delete iSdpSearchPattern;
    iSdpSearchPattern = NULL;

	delete iPortList;
	iPortList = NULL;
}

TInt CBTDiscoverer::CountComponentControls() const
{
    return 1;
}

void CBTDiscoverer::Draw(const TRect& aRect) const
{    
    CWindowGc& gc = SystemGc();
	gc.Clear(aRect);
	
    /*gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor(KRgbWhite);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);*/
}

void CBTDiscoverer::SizeChanged()
{
	if(iPortList)
	{
		iPortList->SetExtent(KListPosition, iPortList->MinimumSize());
	}
}

CCoeControl* CBTDiscoverer::ComponentControl(TInt aIndex) const
{
    switch ( aIndex )
    {
		case 0:
			return iPortList;
		default:
			return NULL;
    }
}

void CBTDiscoverer::SetupScrollBarsL()
{
	iPortList->CreateScrollBarFrameL(ETrue);
	iPortList->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff,CEikScrollBarFrame::EAuto);
}

TKeyResponse CBTDiscoverer::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
{
	if(iPortList)
	{
		return iPortList->OfferKeyEventL(aKeyEvent, aType);
	}
	else
	{
		return EKeyWasNotConsumed;
	}
}

void CBTDiscoverer::HandleListBoxEventL(CEikListBox* /*aListBox*/, TListBoxEvent aListBoxEvent)
{}

void CBTDiscoverer::ListServicesL(const TBTDevAddr& aAddress)
{
    delete iAgent;

    iAgent = NULL;
    iAgent = CSdpAgent::NewL(*this, aAddress);

    iAgent->SetRecordFilterL(*iSdpSearchPattern);
    iAgent->NextRecordRequestL();
}

void CBTDiscoverer::NextRecordRequestComplete(TInt aError, TSdpServRecordHandle aHandle, TInt aTotalRecordsCount)
{
    if (aError != KErrNone)
    {
        PrintSDPError(aError);
	}
    else if (aTotalRecordsCount)
    {
       TRAPD(err, iAgent->AttributeRequestL(aHandle, *iMatchList));
       if (err != KErrNone)
       {
            PrintSDPError(err);
       }
    }
}


void CBTDiscoverer::AttributeRequestResult(TSdpServRecordHandle aHandle, TSdpAttributeID aAttrID, CSdpAttrValue* aAttrValue)
{
    iAttrId = aAttrID;
	TRAPD(err,aAttrValue->AcceptVisitorL(*this));
	
    if (err != KErrNone)
    {
        PrintSDPError(err);
	}
	
    delete aAttrValue;
}

void CBTDiscoverer::VisitAttributeValueL(CSdpAttrValue& aValue, TSdpElementType aType)
{
	switch(aType)
	{
		case ETypeUint:

			if(iAttrId == 0x4)
			{
				iServicePort = aValue.Uint();
				iLog->WriteFormat(_L("service port = %d"),iServicePort);
			}
			break;

		case ETypeString:
			
			if(iAttrId == 0x100)
			{
				TInt len = aValue.Des().Length();
				iServiceName = new TUint16[len+1];
				for (int i = 0; i < len; i++)
				{
					iServiceName[i] = aValue.Des()[i];
				}
				iServiceName[len] = '\0';
				iLog->WriteFormat(_L("service name = %s"),iServiceName);
			}
			break;

		default:
			break;
	}
}

void CBTDiscoverer::StartListL(CSdpAttrValueList& /*aList*/)
{}

void CBTDiscoverer::EndListL()
{}

void CBTDiscoverer::AttributeRequestComplete(TSdpServRecordHandle /*aHandle*/, TInt aError)
{
    if (aError != KErrNone)
    {
        PrintSDPError(aError);
    }
    else
    {
        if(iServicePort != 0 && iServiceName != NULL)
		{
			AddItemToList();
			iServicePort = 0;
			iServiceName = NULL;
//			iPortList->MakeVisible(ETrue);
		}

		TRAPD(err, iAgent->NextRecordRequestL());
        if (err != KErrNone)
        {
            PrintSDPError(aError);
        }
    }
}

void CBTDiscoverer::AddItemToList()
{
	CTextListBoxModel* model = iPortList->Model();
	model->SetOwnershipType(ELbmOwnsItemArray);

	CDesCArray* itemList = STATIC_CAST(CDesCArray*,model->ItemTextArray());
	
	_LIT(KItem,"%d\t%s\t\t");
	TBuf<256> item;
	item.Format(KItem(),iServicePort,iServiceName);
	itemList->AppendL(item);
	
	DrawNow();
}

void CBTDiscoverer::PrintSDPError(TInt aError)
{
	iLog->WriteFormat(_L("Service Discovery Protocol Error = %d"),aError);
}