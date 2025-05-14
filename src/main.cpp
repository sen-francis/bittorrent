#include "torrent_metainfo.h"
#include "torrent_parse_util.h"
#include <string>

using namespace std;

int main() {
	TorrentMetainfo torrentMetainfo = parseTorrentMetainfoFile("../test/TomJerry_Jolly_Fish.avi.torrent");

	return 0;
}
