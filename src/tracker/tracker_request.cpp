#include <cpr/parameters.h>
#include <ctime>
#include <string>
#include <string.h>
#include <cstdlib>
#include <cstring>
#include "tracker_request.h"
#include "torrent_metainfo.h"
#include "tracker_response.h"
#include "util/uri_encode.h"
#include <openssl/sha.h>
#include <cpr/cpr.h>
using namespace std;

const string AZ_CLIENT_PREFIX = "-ZZ0001-";

string generatePeerId() {
	srand(time(0));
	string random = "";
	for (int i = 0; i < 12; i++) {
		random += to_string(rand() % 10);
	}
	return AZ_CLIENT_PREFIX + random;
}

string getHashedInfo(string bencodedInfo) {
	unsigned char hashedInfo[20];
	unsigned char unhashedInfo[bencodedInfo.size() + 1];
	copy(bencodedInfo.begin(), bencodedInfo.end(), unhashedInfo);	
	SHA1(unhashedInfo, strlen((char *)unhashedInfo), hashedInfo);
	return string(hashedInfo, hashedInfo + 20);
}

long getTotalTorrentBytes(TorrentInfo torrentInfo) {
	long totalBytes = 0;
	for (FileInfo fileInfo : torrentInfo.fileInfoList) {
		totalBytes += fileInfo.length;
	}
	return totalBytes;
}

TrackerRequest generateTrackerRequest(TorrentMetainfo torrentMetainfo) {
	TrackerRequest trackerRequest;
	trackerRequest.infoHash = getHashedInfo(torrentMetainfo.bencodedInfo);
	trackerRequest.peerId = generatePeerId();
	trackerRequest.bytesDownloaded = 0;
	trackerRequest.bytesUploaded = 0;
	trackerRequest.bytesLeft = getTotalTorrentBytes(torrentMetainfo.info);
	trackerRequest.portNumber = 6888;
	trackerRequest.compact = true;
	return trackerRequest;
}

TrackerResponse initiateTrackerRequest(TorrentMetainfo torrentMetainfo) {
	string infoHash = getHashedInfo(torrentMetainfo.bencodedInfo);
	string peerId = generatePeerId();
	cpr::Parameters params = cpr::Parameters{{"info_hash", infoHash},
		{"peer_id", peerId},
		{"port", "6888"},
		{"uploaded", "0"},
		{"downloaded", "0"},
		{"left", to_string(getTotalTorrentBytes(torrentMetainfo.info))},
		{"compact", "1"},
		{"event", "started"}
	};

	cpr::Response response = cpr::Get(cpr::Url{torrentMetainfo.announce}, params);	
	TrackerResponse trackerResponse;
	return trackerResponse;
}
