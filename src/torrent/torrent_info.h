#ifndef TORRENT_INFO
#define TORRENT_INFO
	#include <string>
	#include <list>
	#include <map>
	
	enum class TorrentInfoType {SINGLE_FILE, MULTI_FILE};

	struct TorrentInfo {
		TorrentInfoType type;
		std::string name;
	};

	struct SingleFileTorrentInfo : TorrentInfo {
		long length;
		std::string md5sum;
	};

	struct SingleFileInfoForMultiFileTorrentInfo { 
		long length;
		std::string md5sum;
		std::list<std::string> path;
	};

	struct	MultiFileTorrentInfo : TorrentInfo {
		std::list<SingleFileInfoForMultiFileTorrentInfo> fileInfo;
	};



#endif
