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

#include "iStuffMobileContainer.h"
#include <eiklabel.h>


void CiStuffMobileContainer::ConstructL(const TRect& aRect)
{

	CreateWindowL();
	_LIT(iPathName,"\\System\\Apps\\iStuffMobile\\nokia.mbm");
	iBackground = iEikonEnv->CreateBitmapL(iPathName, 0 ); //read the mbm file which contain the bitmap

    iLabel = new (ELeave) CEikLabel;
    iLabel->SetContainerWindowL( *this );
    iLabel->SetTextL( _L("Status :\nNot Connected") );

    SetRect(aRect);

    ActivateL();
}

CiStuffMobileContainer::~CiStuffMobileContainer()
{
    delete iLabel;
}

void CiStuffMobileContainer::SendToBackground()
{
	TApaTask task(iEikonEnv->WsSession());
               
	// Initialise the object with the window group id of
	// our application (so that it represent our app)
	task.SetWgId(CEikonEnv::Static()->RootWin().Identifier());

	// Request window server to bring our application
	// to foreground
	task.SendToBackground();
}

void CiStuffMobileContainer::SizeChanged()
{
    iLabel->SetExtent( TPoint(10,40), iLabel->MinimumSize() );
}


TInt CiStuffMobileContainer::CountComponentControls() const
{
    return 1; // return nbr of controls inside this container
}

CCoeControl* CiStuffMobileContainer::ComponentControl(TInt aIndex) const
{
    switch ( aIndex )
    {
        case 0:
            return iLabel;
        default:
            return NULL;
    }
}

void CiStuffMobileContainer::Draw(const TRect& aRect) const
{
    CWindowGc& gc = SystemGc();
	TRect drawRect(0,0,176,140);
	gc.DrawBitmap(drawRect, iBackground);
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
}

void CiStuffMobileContainer::HandleControlEventL(CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
{

}