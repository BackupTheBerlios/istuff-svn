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

#ifndef BT_DISCOVERER_H
#define BT_DISCOVERER_H

#include <btsdp.h>
#include <btmanclient.h>
#include <btextnotifiers.h>
#include <aknglobalprogressdialog.h>
#include <flogger.h>
#include "BtServiceListContainer.h"

//!  CBTDiscoverer class is responsible for scanning a remote device for bluetooth serial port services
/*!  Following are some main functions of this class:
		 -# Scan serial port services on a bluetooth device.
		 -# Construct a UI to display them to the user for selection.
*/
class CBTDiscoverer : public MSdpAgentNotifier, public MSdpAttributeValueVisitor
    {
		public:

			/** @name CBTDiscoverer class first level constructors
			*   These methods create an object of CBTDiscoverer class and
					initialize a couple of class variables.
			
					\param aLog as RFileLogger object pointer.
					\param aBtSlContainer as CBTServiceListContainer object pointer.
	
					\return CBTDiscoverer object pointer.
			*/
			//@{
			static CBTDiscoverer* NewL(RFileLogger* aLog, CBTServiceListContainer* aBtSlContainer);
			static CBTDiscoverer* NewLC(RFileLogger* aLog, CBTServiceListContainer* aBtSlContainer);
			//@}
			
			//!  Second level constructor for CBTDiscoverer class
			/*!  This method initializes some class variables and 
					 defines a searching criteria for services on a
					 device.
			*/
			void ConstructL();
			
			virtual ~CBTDiscoverer();

			//!  Initiates the service discovery process
			/*!  This method initiates the service discovery process
					 for the device whos address is passed as parameters.
					 
					 \param aAddress as TBTDevAddr object. Represents the
					 				bluetooth address of a device.
			*/
			void ListServicesL(const TBTDevAddr& aAddress);

		private:

			//!  CBTDiscoverer class constructor
			/*!  CBTDiscoverer only initializes some class variables
					 with parameters passed.
					 
					 \param aLog as RFileLogger object pointer.
					 \param aBtSlContainer as CBTServiceListContainer object pointer.
			*/
			CBTDiscoverer(RFileLogger* aLog, CBTServiceListContainer* aBtSlContainer);
			
			//!  Prints an error code to the log
			/*!  This method prints the error code passed to it
					 to the log file.
					 
					 \param aError as TInt. Represents an error code.
			*/
			void PrintSDPError(TInt aError);

			//!  Callback method from system
			/*!  This method is a call back from system and is 
					 invoked when the Bluetooth service discovery 
					 agent finds a service matching the service 
					 criteria specified in ConstructL(). This method
					 then further requests attributes for the 
					 discovered service.
					 
					 \param aError as TInt. Represents an error code.
					 \param aHandle as TSdpServRecordHandle type.
					 				Represents the Handle to the service record.
					 \param aTotalRecordsCount as TInt. 0 if no record
					 				is found.
			*/
			void NextRecordRequestComplete(TInt aError, 
                                   TSdpServRecordHandle aHandle, 
                                   TInt aTotalRecordsCount);
                                   
			//!  Callback method from system
			/*!  This method is a call back from system and is 
					 invoked when the Bluetooth service discovery 
					 agent finds an attribute for a particular 
					 service requested by NextRecordRequestComplete()
					 method. This method then further requests to 
					 visit the value of the received attribute.
					 
					 \param aHandle as TSdpServRecordHandle type.
					 				Represents the Handle to the service record.
					 \param aAttrID as TSdpAttributeID. Represents the
					 				attribute id.
					 \param aAttrValue as CSdpAttrValue object pointer.
					 				Represents attribute value.
			*/
			void AttributeRequestResult(TSdpServRecordHandle aHandle, 
                                TSdpAttributeID aAttrID, 
                                CSdpAttrValue* aAttrValue);
      
      //!  Callback method from system
			/*!  This method is a call back from system and is 
					 invoked when the attribute list of a service
					 ends. When this method is invoked it is guaranteed
					 the port number and the port name of the serial
					 port service on the device is available. This
					 number and name is then written to the list contained
					 by CBTServiceListContainer.
					 
					 \param aHandle as TSdpServRecordHandle type.
					 				Represents the Handle to the service record.
					 \param aError as TInt. Represents an error code.
			*/
			void AttributeRequestComplete(TSdpServRecordHandle aHandle, TInt aError);
			
			void StartListL(CSdpAttrValueList& aList);
			
			//!  Callback method from system
			/*!  This method is a call back from system and is 
					 invoked when the value of an attribute is
					 visited. This method is responsible for saving
					 the port number and port name of a service.
					 
					 \param aValue as CSdpAttrValue object. Represents
					 				the value of the attribute.
					 \param aType as TSdpElementType. Represents the
					 				type of the attribute value.
			*/
			void VisitAttributeValueL(CSdpAttrValue& aValue, TSdpElementType aType);
			
			void EndListL();
		
			CSdpAgent* iAgent;
			CSdpSearchPattern* iSdpSearchPattern;
			CSdpAttrIdMatchList* iMatchList;

			TUint iServicePort;
			TUint iAttrId;
			TUint16* iServiceName;

			RFileLogger* iLog;

			CBTServiceListContainer* iBtSlContainer;
	};

#endif