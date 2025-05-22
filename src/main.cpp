#include "torrent_metainfo.h"
#include "torrent_parse_util.h"
#include "tracker/tracker_request.h"

#include <string>

using namespace std;

int main() {
	TorrentMetainfo torrentMetainfo = parseTorrentMetainfoFile("../test/ubuntu-16.04-desktop-amd64.iso.torrent");
	initiateTrackerRequest(torrentMetainfo);

	return 0;
}
