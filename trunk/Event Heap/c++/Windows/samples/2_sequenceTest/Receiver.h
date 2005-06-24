class ReceiveInfo {
public:
	int m_latency;
	int m_sequence;

	ReceiveInfo(int latency, int sequence)
		: m_latency(latency), m_sequence(sequence)
	{
	}
};

class Receiver : public idk_th_Thread, protected Consts {
private:
	eh2_EventHeapPtr m_ehPtr;
	eh2_EventPtr m_eventPtr;
	int m_threadNum;
	RetrievalType m_retrievalType;
	int m_isEOS; // end of sequence
	
	IDK_UT_VECTOR(ReceiveInfo) m_receiveInfos;

public:
	Receiver(
		const eh2_EventHeapPtr& ehPtr,
		int threadNum,
		RetrievalType retrievalType)
	{
		m_ehPtr = ehPtr;
		m_eventPtr = eh2_Event::cs_create("TestEvent");
		m_eventPtr->allocateField("Count", eh2_FieldType::cs_int())->
			setTemplateValueType(eh2_Consts::FVT_FORMAL);
		m_eventPtr->setTemplateValueInt("From", threadNum);
		m_eventPtr->setTemplateValueType(eh2_Consts::FN_TARGET, eh2_Consts::FVT_FORMAL);
		m_threadNum = threadNum;
		m_retrievalType = retrievalType;
		m_isEOS = 0;
	}

	void run() {
		int count = 0;
		eh2_EventHeap* eh = m_ehPtr; // only for convenience
		eh2_Event* e = m_eventPtr; // only for convenience
		eh->setTimeout(5000);
		while (1) {
			try {
				eh2_EventPtr resultPtr;
				switch (m_retrievalType) {
				case RT_GETEVENT:
					resultPtr = eh->getEvent(e);
					break;
				case RT_REMOVEEVENT:
					resultPtr = eh->removeEvent(e);
					break;
				case RT_WAITFOREVENT:
					resultPtr = eh->waitForEvent(e);
					break;
				case RT_WAITTOREMOVEEVENT:
					resultPtr = eh->waitToRemoveEvent(e);
					break;
				default:
					assert(0);
				}

				if (resultPtr != NULL) {
					int sequence = resultPtr->getPostValueInt("Count");
					int latency = idk_ut_SystemUtil::getCurrentTimeMillis() - 
							resultPtr->getPostValueLong("SendTime");
					if (sequence != count) {
						fprintf(stderr, "[Receiver%d] Wrong sequence. %d was expected but got %d.\n",
							m_threadNum, count, sequence);
					}
					count = sequence + 1;

					m_receiveInfos.push_back(ReceiveInfo(latency, sequence));
				} else {
					fprintf(stderr, "[Receiver%d] No event. Retrying...\n", m_threadNum);
					idk_ut_SystemUtil::sleep(100);
					if (m_isEOS) break;
				}
			}
			catch (idk_th_MonitorTimedoutException&) {
				fprintf(stderr, "[Receiver%d] Server call timed out.\n", m_threadNum);
				if (m_isEOS) break;
			}
			catch (idk_ut_Exception& ex) { // other exception
				fprintf(stderr, "[Receiver%d] Exception. %s\n", m_threadNum, ex.getMessage());
				idk_ut_SystemUtil::sleep(100);
			}
		}
	}

	void setEOS() { m_isEOS = 1; }

	int getInfoCount() const { return m_receiveInfos.size(); }
	const ReceiveInfo getInfo(int i) { return m_receiveInfos[i]; }

};

IDK_UT_SHAREDPTR_DECL(Receiver);
