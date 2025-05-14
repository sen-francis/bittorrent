#ifndef TORRENT_INFO
#define TORRENT_INFO
	#include <string>
	#include <list>
	
	enum class TorrentInfoType {SINGLE_FILE, MULTI_FILE};

	struct TorrentInfo {
		TorrentInfoType type;
		long pieceLength;
		std::string pieces;
		bool isPrivate;
	};

	struct SingleFileTorrentInfo : TorrentInfo {
		std::string fileName;
		long fileLength;
		std::string md5sum;
		
		SingleFileTorrentInfo();
	};

	struct SingleFileInfoForMultiFileTorrentInfo { 
		long length;
		std::string md5sum;
		std::list<std::string> path;
	};

	struct	MultiFileTorrentInfo : TorrentInfo {
		std::string directoryName;	
		std::list<SingleFileInfoForMultiFileTorrentInfo> fileInfoList;
		
		MultiFileTorrentInfo();
	};

#endif
