#ifndef TORRENT_FILE
#define TORRENT_FILE
	#include <string>
	#include <list>
	#include <map>
	
	struct TorrentFile {
		std::map<std::string, any> info;
		std::string announce;
		std::list<std::list<std::string>> announceList;
		int creationDate;
		std::string comment;
		std::string createdBy;
		std::string encoding;
	}

#endif
