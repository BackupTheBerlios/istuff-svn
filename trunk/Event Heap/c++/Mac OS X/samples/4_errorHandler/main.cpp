#include <assert.h>
#include <eh2.h>

// This is an example of usage of eh2_ConnectErrorHandler.
// eh2_ConnectErrorHandler enables apps to observe and interfere
// the attempt to connect to the Event Heap server

#include "StatelessErrorHandlerTest.h"
#include "StatefulErrorHandlerTest.h"

static void displayUsage()
{
	puts("args: {1|2}");
	puts("  1 -- Test of stateless error handler");
	puts("  2 -- Test of stateful error handler");
}

int main(int argc, char** argv)
{
	eh2_init(NULL, NULL);

	if (argc < 2) {
		// too short arguments
		displayUsage();
	} else if (strcmp(argv[1], "1") == 0) {
		// test case 1 -- stateless error handler 
		StatelessErrorHandlerTest test;
		test.run();
	} else if (strcmp(argv[1], "2") == 0) {
		// test case 2 -- stateful error handler
		StatefulErrorHandlerTest test;
		test.run();
	} else {
		// invalid value
		displayUsage();
	}

	eh2_finalize();

	puts("Press ENTER to finish");
	getchar();

	return 0;
}

