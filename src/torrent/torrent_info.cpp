#include "torrent_info.h"

SingleFileTorrentInfo::SingleFileTorrentInfo() {
	this->type = TorrentInfoType::SINGLE_FILE;
}

MultiFileTorrentInfo::MultiFileTorrentInfo() {
	this->type = TorrentInfoType::MULTI_FILE;
}
