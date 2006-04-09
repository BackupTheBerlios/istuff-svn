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

#include <iStuffMobile.rsg>
#include <eiklabel.h>
#include "BtServiceListContainer.h"
#include "CodeListener.h"


CBTServiceListContainer* CBTServiceListContainer::NewL(RFileLogger* aLog, CCodeListener* aCodeListener)
{
	CBTServiceListContainer* self = CBTServiceListContainer::NewLC(aLog,aCodeListener);
    CleanupStack::Pop(self);
    return self;
}

CBTServiceListContainer* CBTServiceListContainer::NewLC(RFileLogger* aLog, CCodeListener* aCodeListener)
{
	CBTServiceListContainer* self = new (ELeave) CBTServiceListContainer(aLog,aCodeListener);
    CleanupStack::PushL(self);
    return self;
}

void CBTServiceListContainer::ConstructL(const TRect& aRect)
{
	
	CreateWindowL();
 
	iPortList = new (ELeave) CAknSingleNumberStyleListBox();
	iPortList->SetContainerWindowL(*this);
	iPortList->SetListBoxObserver(this);

	TResourceReader reader;
	CCoeEnv::Static()->CreateResourceReaderLC(reader,R_ISTUFFMOBILE_SERVICE_LIST);
	iPortList->ConstructFromResourceL(reader);
	CleanupStack::PopAndDestroy();

	SetupScrollBarsL();

	iLabel = new (ELeave) CEikLabel;
    iLabel->SetContainerWindowL( *this );
    iLabel->SetTextL( _L("Select a service") );

	SetRect(aRect);
	ActivateL();
}

CBTServiceListContainer::CBTServiceListContainer(RFileLogger* aLog, CCodeListener* aCodeListener)  
{		
	iLog = aLog;
	iCodeListener = aCodeListener;
}

CBTServiceListContainer::~CBTServiceListContainer()
{
    delete iPortList;
	iPortList = NULL;

	delete iLabel;
	iLabel = NULL;
}

TInt CBTServiceListContainer::CountComponentControls() const
{
    return 2;
}

void CBTServiceListContainer::Draw(const TRect& aRect) const
{    
    CWindowGc& gc = SystemGc();
	gc.Clear(aRect);
}

void CBTServiceListContainer::SizeChanged()
{
	if(iPortList)
		iPortList->SetExtent(TPoint(0,15), iPortList->MinimumSize());
	
	if(iLabel)
		iLabel->SetExtent(TPoint(30,5), iLabel->MinimumSize());
}

CCoeControl* CBTServiceListContainer::ComponentControl(TInt aIndex) const
{
    switch ( aIndex )
    {
		case 0:
			return iPortList;

		case 1:
			return iLabel;

		default:
			return NULL;
    }
}

void CBTServiceListContainer::SetupScrollBarsL()
{
	iPortList->CreateScrollBarFrameL(ETrue);
	iPortList->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff,CEikScrollBarFrame::EAuto);
}

TKeyResponse CBTServiceListContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
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

void CBTServiceListContainer::HandleListBoxEventL(CEikListBox* /*aListBox*/, TListBoxEvent aListBoxEvent)
{
	if ((aListBoxEvent == MEikListBoxObserver::EEventEnterKeyPressed) ||
		(aListBoxEvent == MEikListBoxObserver::EEventItemClicked))
	{
		CDesCArray* itemList = STATIC_CAST(CDesCArray*, iPortList->Model()->ItemTextArray());
		TPtrC16 currentItem((*itemList)[iPortList->CurrentItemIndex()]);

		TLex aLex = TLex(currentItem);
		TUint val;
		if (aLex.Val(val) == KErrNone)
		{
			iCodeListener->ConnectToService(val);
		}
	}

}

void CBTServiceListContainer::AddItemToList(TUint aServicePort, TUint16* aServiceName)
{
	CTextListBoxModel* model = iPortList->Model();
	model->SetOwnershipType(ELbmOwnsItemArray);

	CDesCArray* itemList = STATIC_CAST(CDesCArray*,model->ItemTextArray());
	
	_LIT(KItem,"%d\t%s\t\t");
	TBuf<256> item;
	item.Format(KItem(),aServicePort,aServiceName);
	itemList->AppendL(item);
	
	iPortList->HandleItemAdditionL();
}