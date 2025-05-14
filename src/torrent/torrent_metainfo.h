#ifndef TORRENT_METAINFO
#define TORRENT_METAINFO
	#include <string>
	#include <list>
	#include <map>
	#include "torrent_info.h"

	struct TorrentMetainfo {
		TorrentInfo info;
		std::string announce;
		std::list<std::list<std::string>> announceList;
		int creationDate;
		std::string comment;
		std::string createdBy;
		std::string encoding;
	};

#endif
