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

#include "Btdiscoverer.h"



CBTDiscoverer* CBTDiscoverer::NewL(RFileLogger* aLog)
{
    CBTDiscoverer* self = CBTDiscoverer::NewLC(aLog);
    CleanupStack::Pop(self);
    return self;
}

CBTDiscoverer* CBTDiscoverer::NewLC(RFileLogger* aLog)
{
    CBTDiscoverer* self = new (ELeave) CBTDiscoverer(aLog);
    self->ConstructL();
    CleanupStack::PushL(self);
    return self;
}

void CBTDiscoverer::ConstructL()
{
    TUUID serviceClass(0x1101);
	iSdpSearchPattern = CSdpSearchPattern::NewL();
    iSdpSearchPattern->AddL(serviceClass);

    iMatchList = CSdpAttrIdMatchList::NewL();
    iMatchList->AddL(TAttrRange(0x4,0x0100)); // get only names

    iAgent = NULL;
}

CBTDiscoverer::CBTDiscoverer(RFileLogger* aLog)  
{
	//iHasPrintedRecordNumber = EFalse;
    //iHasPrintedHandle = EFalse;
	iLog = aLog;
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

/*TBool CBTDiscoverer::SelectDeviceL(TBTDeviceResponseParamsPckg& aResponse)
    {
    iHasPrintedRecordNumber = EFalse;
    TBool success = EFalse;
    
    RNotifier notifier;
    User::LeaveIfError(notifier.Connect());
  
    TBTDeviceSelectionParamsPckg selectionFilter;

    TRequestStatus status;
    notifier.StartNotifierAndGetResponse(
        status,
        KDeviceSelectionNotifierUid,
        selectionFilter,
        aResponse
    );

    User::WaitForRequest(status);

    if (status.Int() == KErrNone)
        {
        if (aResponse().IsValidDeviceName())
            {
            success = ETrue;
            }
        else
            {
            iReporter.Error(KStrFailedToConnect);
            }
        }
    else
        {
        iReporter.Error(KStrNoDeviceSelected);
        }

    notifier.CancelNotifier(KDeviceSelectionNotifierUid);
    notifier.Close();

    return success;
    }*/

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
       /*if (!iHasPrintedRecordNumber)
       {
            TBuf<64> buffer;
            buffer.Format(KStrRecordsFound, aTotalRecordsCount);
            iReporter.PrintLine(buffer);
            iHasPrintedRecordNumber = ETrue;
       }*/
       
	   TRAPD(err, iAgent->AttributeRequestL(aHandle, *iMatchList));
       if (err != KErrNone)
       {
            PrintSDPError(err);
       }
    }
}


void CBTDiscoverer::AttributeRequestResult(
    TSdpServRecordHandle aHandle, 
    TSdpAttributeID aAttrID, 
    CSdpAttrValue* aAttrValue
)
    {
    /*if (! iHasPrintedHandle)
        {
        TBuf<40> handle;
        handle.Append(KStrHandle);
        handle.AppendNumUC(static_cast<TUint>(aHandle), EHex);
        iHasPrintedHandle = ETrue;
        iReporter.PrintLine(handle);
        }*/
    //  Create a text value to identify the record & field
    /*TBuf<40> attrIDBuffer;
    attrIDBuffer.Append(KStrAttrId);
    attrIDBuffer.AppendNumUC(static_cast<TUint>(aAttrID), EHex);
    iReporter.PrintLine(attrIDBuffer);*/
    //  Create a text value of the AttributeValue
    //TBTAttributeValueLister lister(iReporter);
    
    //TRAPD(err,aAttrValue->AcceptVisitorL(lister));
	
	//----------------------------------------------------------print the value to the dialog

    /*if (err != KErrNone)
    {
        PrintSDPError(err);
	}*/

    // Ownership has been transferred
    delete aAttrValue;
    }

void CBTDiscoverer::AttributeRequestComplete(TSdpServRecordHandle /*aHandle*/, TInt aError)
{
    if (aError != KErrNone)
    {
        PrintSDPError(aError);
    }
    else
    {
//      iHasPrintedHandle = EFalse;
        TRAPD(err, iAgent->NextRecordRequestL());
        if (err != KErrNone)
        {
            PrintSDPError(aError);
        }
    }
}

void CBTDiscoverer::PrintSDPError(TInt aError)
{
	iLog->WriteFormat(_L("Service Discovery Protocol Error = %d"),aError);
}