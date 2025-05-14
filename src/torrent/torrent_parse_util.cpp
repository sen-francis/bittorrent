#include <fstream>
#include <iostream>
#include <map>
#include <any>
#include <list>
#include "bencode_util.h"
#include "torrent_info.h"
#include "torrent_metainfo.h"

using namespace std;

bool isSingleFileTorrentInfoValid(map<string, any> infoDictionary) {
	if (infoDictionary.count("piece length") == 0) {
		return false;
	}
	if (infoDictionary.count("pieces") == 0) {
		return false;
	}
	if (infoDictionary.count("name") == 0) {
		return false;
	}
	if (infoDictionary.count("length") == 0) {
		return false;
	}

	return true;
}

bool isMultiFileTorrentInfoValid(map<string, any> infoDictionary) {
	if (infoDictionary.count("piece length") == 0) {
		return false;
	}
	if (infoDictionary.count("pieces") == 0) {
		return false;
	}
	if (infoDictionary.count("name") == 0) {
		return false;
	}
	if (infoDictionary.count("files") == 0) {
		return false;
	}
	else {
		list<map<string, any>> files = any_cast<list<map<string, any>>>(infoDictionary.at("files"));
		if(files.size() == 0) {
			return false;
		}
		for(map<string, any> file : files) {
			if (file.count("length") == 0 || file.count("path") == 0) {
				return false;
			}
		}
	}

	return false;
}

SingleFileTorrentInfo parseSingleFileTorrentInfo(map<string, any> infoDictionary) {
	if (!isSingleFileTorrentInfoValid(infoDictionary)) {
		cerr << "Torrent file info dictionary formatted incorrectly.";
		abort();
	}
	SingleFileTorrentInfo *singleFileTorrentInfo = new SingleFileTorrentInfo();
	singleFileTorrentInfo->pieceLength = any_cast<long long>(infoDictionary.at("piece length"));
	singleFileTorrentInfo->pieces = any_cast<string>(infoDictionary.at("pieces"));
	singleFileTorrentInfo->fileName = any_cast<string>(infoDictionary.at("name"));
	singleFileTorrentInfo->fileLength = any_cast<long long>(infoDictionary.at("length"));
	if (infoDictionary.count("private") > 0) {
		int isPrivate = any_cast<int>(infoDictionary.at("private"));

		singleFileTorrentInfo->isPrivate = isPrivate == 1 ? true : false;
	}

	if (infoDictionary.count("md5sum") > 0) {
		singleFileTorrentInfo->md5sum = any_cast<string>(infoDictionary.at("md5sum"));
	}

	return *singleFileTorrentInfo;
}

MultiFileTorrentInfo parseMultiFileTorrentInfo(map<string, any> infoDictionary) {
	if (!isMultiFileTorrentInfoValid(infoDictionary)) {
		cerr << "Torrent file info dictionary formatted incorrectly.";
		abort();
	}

	MultiFileTorrentInfo *multiFileTorrentInfo = new MultiFileTorrentInfo();
	multiFileTorrentInfo->pieceLength = any_cast<long long>(infoDictionary.at("piece length"));
	multiFileTorrentInfo->pieces = any_cast<string>(infoDictionary.at("pieces"));
	multiFileTorrentInfo->directoryName = any_cast<string>(infoDictionary.at("name"));
	
	list<SingleFileInfoForMultiFileTorrentInfo> fileList;
	list<map<string, any>> files = any_cast<list<map<string, any>>>(infoDictionary.at("files"));
	for (map<string, any> file: files) {
		SingleFileInfoForMultiFileTorrentInfo *singleFileInfoForMultFileTorrentInfo	= new SingleFileInfoForMultiFileTorrentInfo();
		singleFileInfoForMultFileTorrentInfo->length = any_cast<long long>(file.at("length"));
		singleFileInfoForMultFileTorrentInfo->path = any_cast<list<string>>(file.at("path"));
		if (file.count("md5sum") > 0) {
			singleFileInfoForMultFileTorrentInfo->md5sum = any_cast<string>(file.at("md5sum"));
		}
		fileList.push_back(*singleFileInfoForMultFileTorrentInfo);
	}
	multiFileTorrentInfo->fileInfoList = fileList;

	if (infoDictionary.count("private") > 0) {
		int isPrivate = any_cast<int>(infoDictionary.at("private"));

		multiFileTorrentInfo->isPrivate = isPrivate == 1 ? true : false;
	}
	
	return *multiFileTorrentInfo;
}

TorrentInfo parseTorrentInfo(map<string, any> infoDictionary) {
	bool isMultiFile = infoDictionary.count("files") > 0;
	if (isMultiFile) {
		return parseMultiFileTorrentInfo(infoDictionary);
	}
	else {
		return parseSingleFileTorrentInfo(infoDictionary);
	}
}

bool isTorrentMetainfoFileValid(map<string, any> dictionary) {
	if (dictionary.count("info") == 0) {
		return false;
	}
	if (dictionary.count("announce") == 0) {
		return false;
	}
	return true;
}

TorrentMetainfo parseTorrentMetainfoFile(std::string fileName) {
	ifstream file(fileName);
	string bencodedText;
	string str;
	while (getline(file, str)) {
		bencodedText += str;
	}
	file.close();
	
	int index = 0;
	map<string, any> dictionary = decodeDictionary(bencodedText, index);

	if (!isTorrentMetainfoFileValid(dictionary)) {
		cerr << "Torrent metainfo file missing required fields.";
		abort();
	}

	TorrentMetainfo *torrentMetainfo = new TorrentMetainfo();
	map<string, any> infoDictionary = any_cast<map<string, any>>(dictionary.at("info"));
	torrentMetainfo->info = parseTorrentInfo(infoDictionary);
	// todo sen: info probably needs to be a pointer so we can cast to child classes and access their unique properties
	torrentMetainfo->announce = any_cast<string>(dictionary.at("announce"));
	
	if (dictionary.count("announce-list") > 0) {
		torrentMetainfo->announceList = any_cast<list<list<string>>>(dictionary.at("announce-list"));
	}
	if (dictionary.count("creation date") > 0) {
		torrentMetainfo->creationDate = any_cast<long long>(dictionary.at("creation date"));
	}
	if (dictionary.count("comment") > 0) {
		torrentMetainfo->comment = any_cast<string>(dictionary.at("comment"));
	}
	if (dictionary.count("created by") > 0) {
		torrentMetainfo->createdBy = any_cast<string>(dictionary.at("created by"));
	}
	if (dictionary.count("encoding")) {
		torrentMetainfo->encoding = any_cast<string>(dictionary.at("encoding"));
	}

	return *torrentMetainfo;
}


