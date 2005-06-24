class Sender : public idk_th_Thread, protected Consts {
private:
	idk_string m_name;
	eh2_EventHeapPtr m_ehPtr;
	eh2_EventPtr m_eventPtr;
	int m_threadNum;
	int m_testCount;
	int m_maxSleepTime;
	int m_ttl;
	Receiver* m_receiver;
public:
	Sender(
		const eh2_EventHeapPtr& ehPtr,
		int threadNum,
		int testCount,
		int maxSleepTime,
		int ttl,
		Receiver* receiver)
	{
		m_ehPtr = ehPtr;
		m_eventPtr = eh2_Event::cs_create("TestEvent");
		m_threadNum = threadNum;
		m_testCount = testCount;
		m_maxSleepTime = maxSleepTime;
		m_ttl = ttl;
		m_receiver = receiver;
	}

	void run() {
		eh2_EventHeap* eh = m_ehPtr; // only for convenience
		eh2_Event* e = m_eventPtr; // only for convenience
		e->setPostValueInt(eh2_Consts::FN_TIMETOLIVE, m_ttl);
		for (int i = 0; i < m_testCount; i++) {
			e->setPostValueInt("Count", i);
			e->setPostValueInt("From", m_threadNum);
			e->setPostValueLong("SendTime", idk_ut_SystemUtil::getCurrentTimeMillis());
			try {
				eh->putEvent(e);
			}
			catch (idk_ut_Exception& ex) {
				fprintf(stderr, "[Sender%d] Exception. %s\n", m_threadNum, ex.getMessage());
			}
			idk_ut_SystemUtil::sleep(idk_ut_SystemUtil::random() * m_maxSleepTime);
		}

		m_receiver->setEOS();
	}
};

IDK_UT_SHAREDPTR_DECL(Sender);
