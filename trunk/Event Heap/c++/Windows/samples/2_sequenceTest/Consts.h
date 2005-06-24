class Consts {
public:
	enum RetrievalType {
		RT_UNKNOWN,
		RT_GETEVENT,
		RT_REMOVEEVENT,
		RT_WAITFOREVENT,
		RT_WAITTOREMOVEEVENT
	};

	const char* retrievalTypeToString(RetrievalType rt) {
		switch (rt) {
		case RT_GETEVENT:
			return "getEvent";
		case RT_REMOVEEVENT:
			return "removeEvent";
		case RT_WAITFOREVENT:
			return "waitForEvent";
		case RT_WAITTOREMOVEEVENT:
			return "waitToRemoveEvent";
		default:
			assert(0);
			return NULL;
		}
	}

	RetrievalType stringToRetrievalType(const char* str) {
		if (strcmp(str, "getEvent") == 0) {
			return RT_GETEVENT;
		}
		else if (strcmp(str, "waitForEvent") == 0) {
			return RT_WAITFOREVENT;
		}
		else if (strcmp(str, "removeEvent") == 0) {
			return RT_REMOVEEVENT;
		}
		else if (strcmp(str, "waitToRemoveEvent") == 0) {
			return RT_WAITTOREMOVEEVENT;
		}
		else {
			return RT_UNKNOWN;
		}
	}
};
