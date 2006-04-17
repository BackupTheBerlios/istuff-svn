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

#include <bt_sock.h>
#include "BtDiscoverer.h"

CBTDiscoverer* CBTDiscoverer::NewL(RFileLogger* aLog, CBTServiceListContainer* aBtSlContainer)
{
	CBTDiscoverer* self = CBTDiscoverer::NewLC(aLog,aBtSlContainer);
    CleanupStack::Pop(self);
    return self;
}

CBTDiscoverer* CBTDiscoverer::NewLC(RFileLogger* aLog, CBTServiceListContainer* aBtSlContainer)
{
	CBTDiscoverer* self = new (ELeave) CBTDiscoverer(aLog,aBtSlContainer);
    CleanupStack::PushL(self);
    return self;
}

void CBTDiscoverer::ConstructL()
{
	
	TUUID serviceClass(0x1101);
	iSdpSearchPattern = CSdpSearchPattern::NewL();
    iSdpSearchPattern->AddL(serviceClass);

    iMatchList = CSdpAttrIdMatchList::NewL();
    iMatchList->AddL(TAttrRange(0x4));
	iMatchList->AddL(TAttrRange(0x0100));

    iAgent = NULL;
}

CBTDiscoverer::CBTDiscoverer(RFileLogger* aLog, CBTServiceListContainer* aBtSlContainer)  
{		
	iLog = aLog;
	iBtSlContainer = aBtSlContainer;
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
}

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
				iServicePort = aValue.Uint();
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
			iBtSlContainer->AddItemToList(iServicePort,iServiceName);
			iServicePort = 0;
			iServiceName = NULL;
		}

		TRAPD(err, iAgent->NextRecordRequestL());
        if (err != KErrNone)
        {
            PrintSDPError(aError);
        }
    }
}

void CBTDiscoverer::PrintSDPError(TInt aError)
{
	if(aError != -25)
		iLog->WriteFormat(_L("Service Discovery Protocol Error = %d"),aError);
}