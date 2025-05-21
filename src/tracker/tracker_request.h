#ifndef TRACKER_REQUEST
#define TRACKER_REQUEST
	#include <string>	
	#include "tracker_response.h"
	
	enum class TrackerRequestEvent {STARTED, STOPPED, COMPLETE};

	struct TrackerRequest {
		std::string infoHash;
		std::string peerId;
		int portNumber;
		long long bytesUploaded;
		long long bytesDownloaded;
		long long bytesLeft;
		bool compact;
		bool noPeerId;	
		std::string ipAddress;
		int numWant;
		std::string key;
		std::string trackerId;
	};
	
	std::string generatePeerId();

	TrackerResponse initiateTrackerRequest(TrackerRequest trackerRequest);
	
#endif
