/* Copyright (c) 2002, Nokia. All rights reserved */

#include <eiklabel.h>
#include <bt_sock.h>

#include "BTDiscoverer.h"
#include "BTAttributeValueLister.h"
#include "BTDiscovery.pan"



_LIT(KStrFailedToConnect,        "Failed to connect");
_LIT(KStrNoDeviceSelected,       "No device selected");
_LIT(KStrFinished,               "-- Finished --");
_LIT(KStrRecordStart,            "-- Record Start --");
_LIT(KStrRecordEnd,              "-- Record End --");
_LIT(KStrRecordsFound,           "%d records found");
_LIT(KStrHandle,                 "Handle: 0x");
_LIT(KStrAttrId,                 "Attr Id: 0x");

_LIT(KErrAlreadyBound,           "SDP Error: AlreadyBound");
_LIT(KErrPeerError,              "SDP Error: PeerError");
_LIT(KErrClientNotConnected,     "SDP Error: ClientNotConnected");
_LIT(KErrUnsupportedVer,         "SDP Error: UnsupportedVersion");
_LIT(KErrBadRecordHandle,        "SDP Error: BadRecordHandle");
_LIT(KErrBadContinuationState,   "SDP Error: BadContinuationState");
_LIT(KErrServerRejectedRequest,  "SDP Error: ServerRejectedRequest");
_LIT(KErrBadRequestBufferLength, "SDP Error: BadRequestBufferLength");
_LIT(KErrBadResultBufferLength,  "SDP Error: BadResultBufferLength");
_LIT(KErrBadUUIDLentgh,          "SDP Error: BadUUIDLength");
_LIT(KErrBadResultData,          "SDP Error: BadResultData");
_LIT(KErrDatabaseFull,           "SDP Error: DatabaseFull");
_LIT(KErrSDPError,               "SDP Error: %d");



CBTDiscoverer* CBTDiscoverer::NewL(MReporter& aReporter)
    {
    CBTDiscoverer* self = CBTDiscoverer::NewLC(aReporter);
    CleanupStack::Pop(self);
    return self;
    }

CBTDiscoverer* CBTDiscoverer::NewLC(MReporter& aReporter)
    {
    CBTDiscoverer* self = new (ELeave) CBTDiscoverer(aReporter);
    self->ConstructL();
    CleanupStack::PushL(self);
    return self;
    }

void CBTDiscoverer::ConstructL()
    {
    iSdpSearchPattern = CSdpSearchPattern::NewL();
    iSdpSearchPattern->AddL(KL2CAP);

    iMatchList = CSdpAttrIdMatchList::NewL();
    iMatchList->AddL(TAttrRange(0x0000, 0xFFFF)); // get them all

    iAgent = NULL;
    }

CBTDiscoverer::CBTDiscoverer(MReporter& aReporter)
:   iReporter(aReporter),  
    iHasPrintedRecordNumber(EFalse), 
    iHasPrintedHandle(EFalse)
    {
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

TBool CBTDiscoverer::SelectDeviceL(TBTDeviceResponseParamsPckg& aResponse)
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
    if (aError == KErrEof)
        {
        iReporter.PrintLine(KStrFinished);
        }
    else if (aError != KErrNone)
        {
        PrintSDPError(aError);
        iReporter.PrintLine(KStrRecordEnd);
        }
    else if (aTotalRecordsCount)
        {
        if (! iHasPrintedRecordNumber)
            {
            TBuf<64> buffer;
            buffer.Format(KStrRecordsFound, aTotalRecordsCount);
            iReporter.PrintLine(buffer);
            iHasPrintedRecordNumber = ETrue;
            }
        iReporter.PrintLine(KStrRecordStart);

        TRAPD(err, iAgent->AttributeRequestL(aHandle, *iMatchList));
        if (err != KErrNone)
            {
            Panic(EBTDiscoveryAttributeRequest);
            }
        }
    else
        {
        iReporter.PrintLine(KNullDesC);
        iReporter.PrintLine(KStrFinished);
        }
    }


void CBTDiscoverer::AttributeRequestResult(
    TSdpServRecordHandle aHandle, 
    TSdpAttributeID aAttrID, 
    CSdpAttrValue* aAttrValue
)
    {
    if (! iHasPrintedHandle)
        {
        TBuf<40> handle;
        handle.Append(KStrHandle);
        handle.AppendNumUC(static_cast<TUint>(aHandle), EHex);
        iHasPrintedHandle = ETrue;
        iReporter.PrintLine(handle);
        }
    //  Create a text value to identify the record & field
    TBuf<40> attrIDBuffer;
    attrIDBuffer.Append(KStrAttrId);
    attrIDBuffer.AppendNumUC(static_cast<TUint>(aAttrID), EHex);
    iReporter.PrintLine(attrIDBuffer);
    //  Create a text value of the AttributeValue
    TBTAttributeValueLister lister(iReporter);
    
    TRAPD(err,aAttrValue->AcceptVisitorL(lister));
    if (err != KErrNone)
        {
        Panic(EBTDiscoveryAttributeAcceptVisitor);
        }

    // Ownership has been transferred
    delete aAttrValue;
    }

void CBTDiscoverer::AttributeRequestComplete(TSdpServRecordHandle /*aHandle*/, TInt aError)
    {
    if (aError == KErrEof)
        {
        iReporter.PrintLine(KStrFinished);
        }
    else if (aError != KErrNone)
        {
        PrintSDPError(aError);
        iReporter.PrintLine(KStrFinished);
        }
    else
        {
        // Finished all attributes of this record - so request the next record
        iHasPrintedHandle = EFalse;
        TRAPD(err, iAgent->NextRecordRequestL());
        if (err != KErrNone)
            {
            Panic(EBTDiscoveryNextRecordRequest);
            }
        }
    }

void CBTDiscoverer::PrintSDPError(TInt aError)
    {
    switch (aError)
        {
        case KErrSdpAlreadyBound:
            iReporter.PrintLine(KErrAlreadyBound);
            break;
        case KErrSdpPeerError:
            iReporter.PrintLine(KErrPeerError);
            break;
        case KErrSdpClientNotConnected:
            iReporter.PrintLine(KErrClientNotConnected);
            break;
        case KErrSdpUnsupportedVersion:
            iReporter.PrintLine(KErrUnsupportedVer);
            break;
        case KErrSdpBadRecordHandle:
            iReporter.PrintLine(KErrBadRecordHandle);
            break;
        case KErrSdpBadContinuationState:
            iReporter.PrintLine(KErrBadContinuationState);
            break;
        case KErrSdpServerRejectedRequest:
            iReporter.PrintLine(KErrServerRejectedRequest);
            break;
        case KErrSdpBadRequestBufferLength:
            iReporter.PrintLine(KErrBadRequestBufferLength);
            break;
        case KErrSdpBadResultBufferLength:
            iReporter.PrintLine(KErrBadResultBufferLength);
            break;
        case KErrSdpBadUUIDLength:
            iReporter.PrintLine(KErrBadUUIDLentgh);
            break;
        case KErrSdpBadResultData:
            iReporter.PrintLine(KErrBadResultData);
            break;
        case KErrSdpDatabaseFull:
            iReporter.PrintLine(KErrDatabaseFull);
            break;
        default:
            {
            TBuf<32> buffer;
            buffer.Format(KErrSDPError, aError);
            iReporter.PrintLine(buffer);
            }
            break;
        }
    }