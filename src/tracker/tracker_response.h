#ifndef TRACKER_RESPONSE
#define TRACKER_RESPONSE
	#include <string>	
	#include <list>

	struct Peer {
		std::string peerId;
		std::string ipAddress;
		int port;
	};

	struct TrackerResponse {
		std::string failureReason;
		std::string warningMessage;
		int interval;
		int minInterval;
		std::string trackerId;
		int seeders;
		int leechers;
		std::list<Peer> peerList;
		std::string peerString;
	};
	
#endif
