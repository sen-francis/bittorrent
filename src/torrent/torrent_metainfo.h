#ifndef TORRENT_METAINFO
#define TORRENT_METAINFO
	#include <string>
	#include <list>
	#include <map>
	
	struct TorrentMetainfo {
		TorrentInfo info;
		std::string announce;
		std::list<std::list<std::string>> announceList;
		int creationDate;
		std::string comment;
		std::string createdBy;
		std::string encoding;
	}

#endif
