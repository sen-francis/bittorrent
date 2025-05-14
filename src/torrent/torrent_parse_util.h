#ifndef TORRENT_PARSE_UTIL
#define TORRENT_PARSE_UTIL
	#include <string>
	#include <map>
	#include <any>
	#include "torrent_metainfo.h"

	TorrentInfo parseTorrentInfo(std::map<std::string, std::any>);
	TorrentMetainfo parseTorrentMetainfoFile(std::string fileName);
#endif
