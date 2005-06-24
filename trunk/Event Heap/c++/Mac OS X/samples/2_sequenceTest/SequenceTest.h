class SequenceTest : public Consts {
private:
	eh2_EventHeapFactory* m_factory;
	eh2_EventHeapPtr m_ehPtr;
	CommandLineOptions m_opts;

public:
	SequenceTest(char** argv)
	{
		m_opts.process(argv);
		m_opts.displayContents();

		// initialize tracer
		if (m_opts.m_traceMask) {
			eh2_TracerPtr tracerPtr = eh2_Tracer::cs_create(
				idk_io_FileOutStream::cs_createBufferedByFileName(m_opts.m_traceFile),
				m_opts.m_traceMask
				);
			eh2_Tracer::cs_setTracer(tracerPtr);
		}

		// initialize event heap factory and the first event heap
		m_factory = eh2_EventHeapFactory::cs_getInstance();
		m_ehPtr = m_factory->createEventHeap(
			"SequenceTestMain", // source name
			m_opts.m_host, // host to connect
			m_opts.m_port,
			m_opts.m_sharedEventHeap
			);
			// note that if you want to share an EventHeap object among
			// multiple threads, you have to pass 1 to the 4th argument.

		m_ehPtr->clear();
	}

	void run()
	{
		IDK_UT_VECTOR(SenderPtr) sendThreads;
		IDK_UT_VECTOR(ReceiverPtr) receiveThreads;

		int i;
		char source[64];
		eh2_EventHeapPtr ehPtr = m_ehPtr;
		for (i = 0; i < m_opts.m_threadCount; i++) {

			// prepare a Receiver
			if (!m_opts.m_sharedEventHeap) {
				sprintf(source, "Receiver%d", i);
				ehPtr = m_factory->createEventHeap(
					source, m_opts.m_host, m_opts.m_port
					);
				ehPtr->setTimeout(m_opts.m_timeout);
			}
			ReceiverPtr receiverPtr = new Receiver(ehPtr, i, m_opts.m_retrievalType);
			receiveThreads.push_back(receiverPtr);

			// prepare a Sender
			if (!m_opts.m_sharedEventHeap) {
				sprintf(source, "Sender%d", i);
				ehPtr = m_factory->createEventHeap(
					source, m_opts.m_host, m_opts.m_port
					);
				ehPtr->setTimeout(m_opts.m_timeout);
			}
			sendThreads.push_back(new Sender(
				ehPtr, i, m_opts.m_count, m_opts.m_maxSleepTime, m_opts.m_ttl, receiverPtr
				));

		}

		// start worker threads
		for (i = 0; i < m_opts.m_threadCount; i++) {
			sendThreads[i]->start();
			receiveThreads[i]->start();
		}

		// wait for the threads ends
		for (i = 0; i < m_opts.m_threadCount; i++) {
			sendThreads[i]->join();
			receiveThreads[i]->join();
		}

		//
		// report the result
		//

		freopen(m_opts.m_outFile, "w", stdout);
		printf("<report>\n");
		for (i = 0; i < m_opts.m_threadCount; i++) {
			printf(" <thread num=\"%d\">\n", i);
			int j;
			for (j = 0; j < receiveThreads[i]->getInfoCount(); j++) {
				ReceiveInfo info = receiveThreads[i]->getInfo(j);
				printf("  <receive sequence=\"%d\" latency=\"%d\"/>\n", 
					info.m_sequence, info.m_latency
					);
			}
			printf(" </thread>\n");
		}
		printf("</report>\n");
	}
};

