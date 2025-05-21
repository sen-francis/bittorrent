#ifndef TORRENT_INFO
#define TORRENT_INFO
	#include <string>
	#include <list>

	struct FileInfo { 
		long length;
		std::string md5sum;
		std::list<std::string> path;
	};

	struct TorrentInfo {
		long pieceLength;
		std::string pieces;
		bool isPrivate;
		std::string directoryName;
		std::list<FileInfo> fileInfoList;
	};

	
#endif
