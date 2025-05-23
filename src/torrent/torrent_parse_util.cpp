#include <fstream>
#include <iostream>
#include <map>
#include <any>
#include <list>
#include <variant>
#include <vector>
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

TorrentInfo parseSingleFileTorrentInfo(map<string, any> infoDictionary) {
	if (!isSingleFileTorrentInfoValid(infoDictionary)) {
		cerr << "Torrent file info dictionary formatted incorrectly.";
		abort();
	}
	TorrentInfo torrentInfo;
	torrentInfo.pieceLength = any_cast<long long>(infoDictionary.at("piece length"));
	torrentInfo.pieces = any_cast<string>(infoDictionary.at("pieces"));
	FileInfo fileInfo;
	list<string> path;
	path.push_back(any_cast<string>(infoDictionary.at("name")));
	fileInfo.path = path;	

	if (infoDictionary.count("md5sum") > 0) {
		fileInfo.md5sum = any_cast<string>(infoDictionary.at("md5sum"));
	}

	list<FileInfo> fileInfoList;
	fileInfoList.push_back(fileInfo);
	torrentInfo.fileInfoList = fileInfoList;

	if (infoDictionary.count("private") > 0) {
		int isPrivate = any_cast<int>(infoDictionary.at("private"));

		torrentInfo.isPrivate = isPrivate == 1 ? true : false;
	}

	return torrentInfo;
}

TorrentInfo parseMultiFileTorrentInfo(map<string, any> infoDictionary) {
	if (!isMultiFileTorrentInfoValid(infoDictionary)) {
		cerr << "Torrent file info dictionary formatted incorrectly.";
		abort();
	}

	TorrentInfo torrentInfo;
	torrentInfo.pieceLength = any_cast<long long>(infoDictionary.at("piece length"));
	torrentInfo.pieces = any_cast<string>(infoDictionary.at("pieces"));
	torrentInfo.directoryName = any_cast<string>(infoDictionary.at("name"));

	list<FileInfo> fileInfoList;
	list<map<string, any>> files = any_cast<list<map<string, any>>>(infoDictionary.at("files"));
	for (map<string, any> file: files) {
		FileInfo fileInfo;
		fileInfo.length = any_cast<long long>(file.at("length"));
		fileInfo.path = any_cast<list<string>>(file.at("path"));
		if (file.count("md5sum") > 0) {
			fileInfo.md5sum = any_cast<string>(file.at("md5sum"));
		}
		fileInfoList.push_back(fileInfo);
	}
	torrentInfo.fileInfoList = fileInfoList;

	if (infoDictionary.count("private") > 0) {
		int isPrivate = any_cast<int>(infoDictionary.at("private"));

		torrentInfo.isPrivate = isPrivate == 1 ? true : false;
	}

	return torrentInfo;
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

bool isTorrentMetainfoFileValid(unordered_map<string, Bencode> dictionary) {
	if (dictionary.count("info") == 0 || !holds_alternative<Dictionary>(dictionary.at("info"))) {
		return false;
	}
	if (dictionary.count("announce") == 0 || !holds_alternative<string>(dictionary.at("announce"))) {
		return false;
	}
	return true;
}

TorrentMetainfo parseTorrentMetainfoFile(std::string fileName) {
	ifstream file(fileName, ios_base::binary);
	vector<unsigned char> bencodedText(istreambuf_iterator<char>(file), {});
	/*string bencodedText;
	string str;
	while (getline(file, str)) {
		bencodedText += str;
	}
	*/

	file.close();

	int index = 0;
	unordered_map<string, Bencode> dictionary = decodeDictionary(bencodedText, index).values;

	if (!isTorrentMetainfoFileValid(dictionary)) {
		cerr << "Torrent metainfo file missing required fields.";
		abort();
	}

	TorrentMetainfo torrentMetainfo;
	Dictionary infoDictionary = boost::get<Dictionary>(dictionary.at("info"));
	torrentMetainfo.info = parseTorrentInfo(infoDictionary);
	torrentMetainfo.bencodedInfo = encode(infoDictionary);
	torrentMetainfo.announce = any_cast<string>(dictionary.at("announce"));

	if (dictionary.count("announce-list") > 0) {
		torrentMetainfo.announceList = any_cast<list<list<string>>>(dictionary.at("announce-list"));
	}
	if (dictionary.count("creation date") > 0) {
		torrentMetainfo.creationDate = any_cast<long long>(dictionary.at("creation date"));
	}
	if (dictionary.count("comment") > 0) {
		torrentMetainfo.comment = any_cast<string>(dictionary.at("comment"));
	}
	if (dictionary.count("created by") > 0) {
		torrentMetainfo.createdBy = any_cast<string>(dictionary.at("created by"));
	}
	if (dictionary.count("encoding")) {
		torrentMetainfo.encoding = any_cast<string>(dictionary.at("encoding"));
	}

	return torrentMetainfo;
}


