class CommandLineOptions : protected Consts {
public:
	const char* m_host;
	int m_port;
	RetrievalType m_retrievalType;
	int m_threadCount;
	int m_count;
	int m_maxSleepTime;
	int m_ttl;
	int m_timeout;
	const char* m_traceFile;
	const char* m_outFile;
	int m_traceMask;
	int m_sharedEventHeap;

public:
	CommandLineOptions()
		: m_host("localhost"),
		  m_port(-1),
		  m_retrievalType(RT_WAITFOREVENT),
		  m_threadCount(1),
		  m_count(100),
		  m_maxSleepTime(1000),
		  m_ttl(120000),
		  m_timeout(5000),
		  m_traceFile("trace.txt"),
		  m_outFile("out.xml"),
		  m_traceMask(0),
		  m_sharedEventHeap(0)
	{}

	void process(char** argv) {
		const char* opt;
		argv++;

		while (opt = *argv++) {
			if (strcmp(opt, "--host") == 0) {
				m_host = *argv++;
			}
			else if (strcmp(opt, "--port") == 0) {
				m_port = atoi(*argv++);
			}
			else if (strcmp(opt, "--retrievalType") == 0) {
				const char* value = *argv++;
				RetrievalType rt = stringToRetrievalType(value);
				if (rt != RT_UNKNOWN) {
					m_retrievalType = rt;
				} else {
					fprintf(stderr, "unknown retrieval type: %s\n", value);
				}
			}
			else if (strcmp(opt, "--threads") == 0) {
				m_threadCount = atoi(*argv++);
			}
			else if (strcmp(opt, "--count") == 0) {
				m_count = atoi(*argv++);
			}
			else if (strcmp(opt, "--maxSleepTime") == 0) {
				m_maxSleepTime = atoi(*argv++);
			}
			else if (strcmp(opt, "--ttl") == 0) {
				m_ttl = atoi(*argv++);
			}
			else if (strcmp(opt, "--timeout") == 0) {
				m_timeout = atoi(*argv++);
			}
			else if (strcmp(opt, "--traceFile") == 0) {
				m_traceFile = *argv++;
			}
			else if (strcmp(opt, "--outFile") == 0) {
				m_outFile = *argv++;
			}
			else if (strcmp(opt, "--sharedEventHeap") == 0) {
				m_sharedEventHeap = atoi(*argv++);
			}
			else if (strcmp(opt, "--traceMask") == 0) {
				const char* value = *argv++;

				int reset = 0;
				if (*value == '-') {
					value++;
					reset = 1;
				}

				int mask;

				if (strncmp(value, "ALL", 3) == 0) {
					mask = eh2_Consts::TMM_ALL;
				}
				else if (strncmp(value, "API", 3) == 0) {
					mask = eh2_Consts::TMM_API;
				}
				else if (strncmp(value, "SYS", 3) == 0) {
					mask = eh2_Consts::TMM_SYSTEMCALL;
				}
				else if (strncmp(value, "ERR", 3) == 0) {
					mask = eh2_Consts::TMM_ERROR;
				}
				else if (strncmp(value, "OTH", 3) == 0) {
					mask = eh2_Consts::TMM_OTHER;
				}

				if (reset) {
					m_traceMask &= ~mask;
				} else {
					m_traceMask |= mask;
				}
			}
			else if (strcmp(opt, "--help") == 0 || strcmp(opt, "-h") == 0) {
				displayHelpAndExit();				
			}
			else {
				fprintf(stderr, "unknown option: %s.  use -h to show help.\n", opt);
			}
		}
	}

	void displayContents() {
		fprintf(stderr,
			"host = %s\n"
			"port = %d\n"
			"retrievalType = %s\n"
			"threads = %d\n"
			"count = %d\n"
			"maxSleepTime = %d\n"
			"ttl = %d\n"
			"timeout = %d\n"
			"traceFile = %s\n"
			"outFile = %s\n"
			"sharedEventHeap = %d\n"
			"traceMask = %s%s%s%s\n"
			"\n",
			
			m_host, m_port, retrievalTypeToString(m_retrievalType),
			m_threadCount, m_count, m_maxSleepTime, m_ttl, m_timeout,
			m_traceFile, m_outFile, m_sharedEventHeap,
			(m_traceMask & eh2_Consts::TMM_API) ? "API " : "",
			(m_traceMask & eh2_Consts::TMM_SYSTEMCALL) ? "SYS " : "",
			(m_traceMask & eh2_Consts::TMM_ERROR) ? "ERR " : "",
			(m_traceMask & eh2_Consts::TMM_OTHER) ? "OTHER " : ""
			);
	}

	void displayHelpAndExit() {
		fprintf(stderr, "%s",
			"Options:\n"
			"  --host <EventHeap host>\n"
			"  --port <EventHeap port>\n"
			"  --retrievalType {getEvent|waitForEvent|removeEvent|waitToRemoveEvent}\n"
			"  --threads <thread count>\n"
			"  --count <event post count>\n"
			"  --maxSleepTime <max interval (ms)>\n"
			"  --ttl <time-to-live of event (ms)>\n"
			"  --timeout <timeout (ms)>\n"
			"  --traceFile <filename>\n"
			"  --outFile <filename>\n"
			"  --sharedEventHeap {0|1}\n"
			"  --traceMask {ALL|API|SYS|ERR|OTH|-ALL|-API|-SYS|-ERR|-OTH}\n"
			"              (can be specified multiple times to combine flags)\n"
			"  --help or -h to show this message\n"
			"\n");
		exit(0);
	}
};
