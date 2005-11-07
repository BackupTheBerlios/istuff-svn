#include <iostream.h>
//#include <unistd.h>
#include<assert.h>

// event heap includes
#include <idk_io.h>
#include <idk_th.h>
#include <eh2.h>

// teleo includes
#include <TeleoMioAin.h>
#include <TeleoMioDin.h>
#include <TeleoMioPwm.h>
#include <TeleoMioDout.h>
#include <TeleoEasy.h>


// constants
static const int BUFFER_SIZE = 255;
static const int MAX_TELEO_AIN = 4;
static const int MAX_TELEO_DIN = 4;
static const int MAX_TELEO_PWMOUT = 2;
static const int MAX_TELEO_DOUT = 4;
static const char EHEAP_DEVICE_AIN_STR[]    = "TELEO_AIN";
static const char EHEAP_DEVICE_DIN_STR[]    = "TELEO_DIN";
static const char EHEAP_DEVICE_PWMOUT_STR[] = "TELEO_PWMOUT";
static const char EHEAP_DEVICE_DOUT_STR[]   = "TELEO_DOUT";
static const char EHEAP_DEVICE_ID_STR[]     = "ID";
static const char EHEAP_DEVICE_VALUE_STR[]  = "VALUE";
static const char EHEAP_CLIENT_NAME_STR[]   = "NAME";

// global variables
static TMioAin  *pAinArray[MAX_TELEO_AIN];
static TMioDin  *pDinArray[MAX_TELEO_DIN];
static TMioPwm  *pPwmoutArray[MAX_TELEO_PWMOUT];
static TMioDout *pDoutArray[MAX_TELEO_DOUT];
static eh2_EventHeap *pEventHeap;
static char clientName[BUFFER_SIZE];
static float staticValA;
static bool staticValD;

// local function declarations
bool InitEventHeap(const char *serverName);
bool InitTeleo(const char *usbDevice, const bool *isAinActive, const bool *isDinActive, const bool *isPwmoutActive, const bool *isDoutActive);
void PrintUsage(const char *execName);
bool ParseArgs(char *argv[], int argc, char *serverName, char *clientName, char *usbDevice, bool *isAinActive, bool *isDinActive, bool *isPwmoutActive, bool *isDoutActive);
TeleoError AinValueUpdate(TMioAin* pAin, float value);
TeleoError DinValueUpdate(TMioDin* pDin, bool value);
TeleoError PwmoutValueUpdate(TMioPwm* pPwmout, float duty);
TeleoError DoutValueUpdate(TMioDout* pDout, bool value);

// local class declarations
class EventListener : public idk_th_Thread 
{
private:
	eh2_EventRegistrationPtr pEventRegistration_;

protected:
	void setRegistration(const eh2_EventRegistrationPtr& pEventRegistration);

public:
   EventListener(eh2_EventHeap* eh);
   void run();
   void quit();
};

int main(int argc, char *argv[]) 
{
   if (argc % 2 != 1 || argc == 1)
   {
      PrintUsage(argv[0]);
      return 0;
   }
   
   // Get command-line options
   char serverName[BUFFER_SIZE] = "localhost";
   char usbDevice[BUFFER_SIZE] = "";
   bool isAinActive[MAX_TELEO_AIN];
   staticValD=1;
   staticValA=0;
   
   //initialize clientName to hostname
   gethostname(clientName, BUFFER_SIZE);
   
   for (int i = 0; i < MAX_TELEO_AIN; i++)
   {
      isAinActive[i] = false;
      pAinArray[i] = NULL;
   }
   bool isDinActive[MAX_TELEO_DIN];
   for (int i = 0; i < MAX_TELEO_DIN; i++)
   {
      isDinActive[i] = false;
      pDinArray[i] = NULL;
   }
   bool isPwmoutActive[MAX_TELEO_PWMOUT];
   for (int i = 0; i < MAX_TELEO_PWMOUT; i++)
   {
      isPwmoutActive[i] = false;
      pPwmoutArray[i] = NULL;
   }
   bool isDoutActive[MAX_TELEO_DOUT];
   for (int i = 0; i < MAX_TELEO_DOUT; i++)
   {
      isDoutActive[i] = false;
      pDoutArray[i] = NULL;
   }
   bool success = ParseArgs(&argv[1], argc - 1, serverName, clientName, usbDevice, isAinActive, isDinActive, isPwmoutActive, isDoutActive);
   if (!success)
   {
      PrintUsage(argv[0]);
      return 0;
   }
   cout << "Event heap server: " << serverName << endl;
   if (strcmp(usbDevice, "") != 0)
   {
      cout << "USB device: " << usbDevice << endl;
   }
   cout << "Teleo analog inputs:";
   for (int i = 0; i < MAX_TELEO_AIN; i++)
   {
      if (isAinActive[i]) cout << " " << i;
   }
   cout << endl;
   cout << "Teleo digital inputs:";
   for (int i = 0; i < MAX_TELEO_DIN; i++)
   {
      if (isDinActive[i]) cout << " " << i;
   }
   cout << endl;
   cout << "Teleo pulse width modulated outputs:";
   for (int i = 0; i < MAX_TELEO_PWMOUT; i++)
   {
      if (isPwmoutActive[i]) cout << " " << i;
   }
   cout << endl;
   cout << "Teleo digital outputs:";
   for (int i = 0; i < MAX_TELEO_DOUT; i++)
   {
      if (isDoutActive[i]) cout << " " << i;
   }
   cout << endl;
   
   // Set up teleo related stuff
   cout << "Initializing teleo.... " << flush;
   if (!InitTeleo(usbDevice, isAinActive, isDinActive, isPwmoutActive, isDoutActive))
   {
      return 1;
   }
   cout << "ok.\n";

   // Set-up event heap related stuff
   cout << "Initializing event heap.... " << flush;
   
   // Initialize the event heap client library.
   eh2_init(NULL, NULL);
   
   // Create a tracer.  Keep it in a smart pointer.
   //eh2_TracerPtr pTracer = eh2_Tracer::cs_create(idk_io_FileOutStream::cs_createBufferedByFileName("trace.txt"), eh2_Consts::TMM_ALL);
   //eh2_Tracer::cs_setTracer(pTracer);

   // Create an event heap.  Make sure it's thread-safe.
   eh2_EventHeapPtr pEHeap = NULL;
   try
   {
      eh2_EventHeapFactory* pFactory = eh2_EventHeapFactory::cs_getInstance();
      pEHeap = pFactory->createEventHeap(NULL, serverName, -1, 1);
      // store in a global variable...
      pEventHeap = pEHeap;
   }
   catch (idk_ut_Exception& ex) 
   {
      cerr << ex.getMessage() << endl;
      return 1;
   }
   cout << "ok.\n";

   EventListener* pEventListener = new EventListener(pEHeap);
   pEventListener->start();
   
   cout << "entering main loop\n";
   // Enter main run loop
   TeleoEasy_Continue();

   // Clean-up   
   pEventListener->quit();
   pEventListener->join();
   eh2_finalize();

   return 0;
}


bool InitTeleo(const char *usbDevice, const bool *isAinActive, const bool *isDinActive, const bool *isPwmoutActive, const bool *isDoutActive)
{
   // Device Manager
   TeleoDeviceManager *pDeviceManager;
   if (TeleoEasy_Init(usbDevice, TI_USB, &pDeviceManager ) != TELEO_OK)
   {
	  TeleoError errCode = TeleoEasy_Init(usbDevice, TI_USB, &pDeviceManager );
       cerr << "Failed TeleoEasy_Init " << usbDevice << " with errorcode " << errCode << endl;
      return false;
   }
   
   // Analog input devices
   for (int i = 0; i < MAX_TELEO_AIN; i++)
   {
      if (isAinActive[i])
      {
         TMioAin_Create(pDeviceManager, NULL, 0, NULL, &pAinArray[i]);
         if (!pAinArray[i])
         {
		    cerr << "Failed TMioAin_Create" << endl;
            return false;
         }
         TMioAin_maxSet(pAinArray[i], 1023);
         TMioAin_minSet(pAinArray[i], 0);
         TMioAin_sampleRateSet(pAinArray[i], 50/*ms*/);
         TMioAin_resolutionSet(pAinArray[i], 10);
         TMioAin_valueCallbackSet(pAinArray[i], AinValueUpdate);
      }
   }

   // Digital input devices
   for (int i = 0; i < MAX_TELEO_DIN; i++)
   { 
      if (isDinActive[i])
      {  
         TMioDin_Create(pDeviceManager, NULL, 0, NULL, &pDinArray[i]);
		 cout << "TMioDin is created"<<endl;
         if (!pDinArray[i])
         {
		    cerr << "Failed TMioDin_Create \n";
			return false;
         }
         TMioDin_sampleRateSet(pDinArray[i], 50);
		 TMioDin_valueCallbackSet(pDinArray[i], DinValueUpdate);
           			 }
   }
   
   // Pulse width modulated output devices
   for (int i = 0; i < MAX_TELEO_PWMOUT; i++)
   {
      if (isPwmoutActive[i])
      {
         TMioPwm_Create(pDeviceManager, NULL, 0, NULL, &pPwmoutArray[i]);
         if (!pPwmoutArray[i])
         {
		    cerr << "Failed TMioPwm_Create" << endl;
            return false;
         }
         TMioPwm_dutyCallbackSet(pPwmoutArray[i], PwmoutValueUpdate);
      }
   }

   // Digital output devices
   for (int i = 0; i < MAX_TELEO_DOUT; i++)
   {
      if (isDoutActive[i])
      {
         TMioDout_Create(pDeviceManager, NULL, 0, NULL, &pDoutArray[i]);
         if (!pDoutArray[i])
         {
		    cerr << "Failed TMioDout_Create" << endl;
            return false;
         }
         TMioDout_valueCallbackSet(pDoutArray[i], DoutValueUpdate);
      }
   }
   
   // Start the device system up
   TeleoEasy_Start();   
   return true;
}

void PrintUsage(const char *execName)
{
   cout << "Usage: " << execName << " [-server server_name] [-device usb_device] [-ain #] [-din #] [-pwmout #] [-dout #]\n"
        << "  -server : name of event heap server (default: localhost)\n"
        << "  -name   : name of this event client for the subscription templates to distinguish between multiple Teleo clients connected to the same event heap (default: hostname)\n"
        << "  -device : usb device that Teleo device is connected to (default: search all USB devices)\n"
        << "  -ain    : ID of analog input, from 0 to " << MAX_TELEO_AIN - 1 << " (can be specified multiple times)\n"
        << "  -din    : ID of digital input, from 0 to " << MAX_TELEO_DIN - 1 << " (can be specified multiple times)\n"
        << "  -pwmout : ID of pulse width modulated output, from 0 to " << MAX_TELEO_PWMOUT - 1 << " (can be specified multiple times)\n"
        << "  -dout   : ID of digital output, from 0 to " << MAX_TELEO_DOUT - 1 << " (can be specified multiple times)\n";
}

bool ParseArgs(char *argv[], int argc, char *serverName, char *clientName, char *usbDevice, bool *isAinActive, bool *isDinActive, bool *isPwmoutActive, bool *isDoutActive)
{
   assert(argc % 2 == 0);
   
   int i = 0;
   while (i < argc)
   {
      if (strcmp(argv[i], "-server") == 0)
      {
         strcpy(serverName, argv[i+1]);
      }
      else if (strcmp(argv[i], "-name") == 0)
      {
         strcpy(clientName, argv[i+1]);
      }
      else if (strcmp(argv[i], "-device") == 0)
      {
         strcpy(usbDevice, argv[i+1]);
      }
      else if (strcmp(argv[i], "-ain") == 0)
      {
         int id = atoi(argv[i+1]);
         if (0 <= id && id < MAX_TELEO_AIN)
         {
            isAinActive[id] = true;
         }
         else
         {
            cout << "Warning: '" << argv[i+1] << "' is not a valid analog input id.\n";
            return false;
         }
      }
      else if (strcmp(argv[i], "-din") == 0)
      {
         int id = atoi(argv[i+1]);
         if (0 <= id && id < MAX_TELEO_DIN)
         {
            isDinActive[id] = true;
         }
         else
         {
            cout << "Warning: '" << argv[i+1] << "' is not a valid digital input id.\n";
            return false;
         }
      }
      else if (strcmp(argv[i], "-pwmout") == 0)
      {
         int id = atoi(argv[i+1]);
         if (0 <= id && id < MAX_TELEO_PWMOUT)
         {
            isPwmoutActive[id] = true;
         }
         else
         {
            cout << "Warning: '" << argv[i+1] << "' is not a valid pulse width modulated output id.\n";
            return false;
         }
      }
      else if (strcmp(argv[i], "-dout") == 0)
      {
         int id = atoi(argv[i+1]);
         if (0 <= id && id < MAX_TELEO_DOUT)
         {
            isDoutActive[id] = true;
         }
         else
         {
            cout << "Warning: '" << argv[i+1] << "' is not a valid digital output id.\n";
            return false;
         }
      }
      else
      {
         cout << "Warning: unknown option '" << argv[i] << "'\n";
         return false;
      }
      i += 2;
   }
   
   return true;
}

TeleoError AinValueUpdate(TMioAin* pAin, float value)
{
    if(value != staticValA){
   int i;
   for (i = 0; i < MAX_TELEO_AIN; i++)
   {
      if (pAinArray[i] == pAin)
      {
         break;
      }
   }
   assert(i < MAX_TELEO_AIN);
   cout << "Sending analog input [" << i << "]: " << value << endl << flush;
    staticValA=value;
   // create and place event on event heap
   eh2_EventPtr pEvent = eh2_Event::cs_create(EHEAP_DEVICE_AIN_STR);
   pEvent->setPostValueInt(EHEAP_DEVICE_ID_STR, i);
   pEvent->setPostValueFloat(EHEAP_DEVICE_VALUE_STR, value / 1023.0);
   pEvent->setPostValueString(EHEAP_CLIENT_NAME_STR,clientName);
   pEventHeap->putEvent(pEvent);
}
   return TELEO_OK;
}

TeleoError DinValueUpdate(TMioDin* pDin, bool value)
{   
  if(value != staticValD){
     int i;
   for (i = 0; i < MAX_TELEO_DIN; i++)
   {
      if (pDinArray[i] == pDin)
      {
         break;
      }
   }
   assert(i < MAX_TELEO_DIN);
   //if the value has not been changed don"t send anything
 
   cout << "Sending digital input [" << i << "]: " << (value ? 1 : 0) << endl << flush;
   staticValD=value;
   // create and place event on event heap
   eh2_EventPtr pEvent = eh2_Event::cs_create(EHEAP_DEVICE_DIN_STR);
   pEvent->setPostValueInt(EHEAP_DEVICE_ID_STR, i);
   pEvent->setPostValueInt(EHEAP_DEVICE_VALUE_STR, (value ? 1 : 0));
   pEvent->setPostValueString(EHEAP_CLIENT_NAME_STR,clientName);
   pEventHeap->putEvent(pEvent);
}
   return TELEO_OK;
}

TeleoError PwmoutValueUpdate(TMioPwm* pPwmout, float duty)
{
   int i;
   for (i = 0; i < MAX_TELEO_PWMOUT; i++)
   {
      if (pPwmoutArray[i] == pPwmout)
      {
         break;
      }
   }
   assert(i < MAX_TELEO_PWMOUT);
   cout << "Received pwm output [" << i << "]: " << duty << endl << flush;

   return TELEO_OK;
}

TeleoError DoutValueUpdate(TMioDout* pDout, bool value)
{
   int i;
   for (i = 0; i < MAX_TELEO_DOUT; i++)
   {
      if (pDoutArray[i] == pDout)
      {
         break;
      }
   }
   assert(i < MAX_TELEO_DOUT);
   cout << "Received digital output [" << i << "]: " << (value ? 1 : 0) << endl << flush;
   
   return TELEO_OK;
}


// local class implementation

EventListener::EventListener(eh2_EventHeap* eh)
{
   // Register teleo output events to listen for
   eh2_EventCollectionPtr pTemplates = eh2_EventCollection::cs_create();
   
   eh2_EventPtr pwmTemplate = eh2_Event::cs_create(EHEAP_DEVICE_PWMOUT_STR);
   pwmTemplate->setPostValueString(EHEAP_CLIENT_NAME_STR,clientName);
   pTemplates->add(pwmTemplate);
   
   eh2_EventPtr doutTemplate = eh2_Event::cs_create(EHEAP_DEVICE_DOUT_STR);
   doutTemplate->setPostValueString(EHEAP_CLIENT_NAME_STR,clientName);
   pTemplates->add(doutTemplate);
   
   eh2_EventRegistrationPtr pEventRegistration = eh->registerForEvents(pTemplates);
   
   setRegistration(pEventRegistration);
}

void EventListener::setRegistration(const eh2_EventRegistrationPtr& pEventRegistration)
{
	pEventRegistration_ = pEventRegistration;
}

void EventListener::run()
{
		fprintf(stderr, "[iteleo] started\n");
		try {
			while (1) {
				eh2_EventPtr eventPtr = pEventRegistration_->waitForResult(NULL);
				fprintf(stderr, "[iteleo] type='%s' seq='%d'\n",
					eventPtr->getEventType(),
					eventPtr->getPostValueInt(eh2_Consts::FN_SEQUENCENUM)
					);
		
				if(strcmp(eventPtr->getEventType(), EHEAP_DEVICE_PWMOUT_STR) == 0){
					int port = eventPtr->getPostValueInt(EHEAP_DEVICE_ID_STR);
					float value = eventPtr->getPostValueFloat(EHEAP_DEVICE_VALUE_STR);
					TMioPwm_dutySet(pPwmoutArray[port], value);						
				}
				else if(strcmp(eventPtr->getEventType(), EHEAP_DEVICE_DOUT_STR) == 0){
					int port = eventPtr->getPostValueInt(EHEAP_DEVICE_ID_STR);
					bool value = eventPtr->getPostValueBoolean(EHEAP_DEVICE_VALUE_STR);
					TMioDout_valueSet (pDoutArray[port], value);	
				}
			}
		}
		catch (idk_th_InterruptedException&) {
			// interrupted by deregister
		}
}

void EventListener::quit()
{
	pEventRegistration_->deregister();
}