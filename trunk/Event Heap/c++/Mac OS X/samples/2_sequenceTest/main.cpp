#include <eh2.h>
#include <idk_ut.h>
#include <idk_io.h>
#include <idk_th.h>
#include <assert.h>

#include "Consts.h"
#include "CommandLineOptions.h"
#include "Receiver.h"
#include "Sender.h"
#include "SequenceTest.h"

int main(int argc, char** argv)
{
	eh2_init(NULL, NULL);

	{
		SequenceTest t(argv);
		t.run();

		// make sure no EventHeap objects are left undestructed.
	}

	eh2_finalize();

	return 0;
}

