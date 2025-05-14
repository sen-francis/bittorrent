#ifndef BENCODE_UTIL
#define BENCODE_UTIL
	#include <string>
	#include <map>
	#include <list>
	#include <any>
	
	std::string encode(std::string plainText);
	std::any decode(std::string bencodedText, int &index);
	std::string decodeByteString(std::string bencodedText, int &index);
	long long decodeInteger(std::string bencodedText, int &index);
	std::list<std::any> decodeList(std::string bencodedText, int &index);
	std::map<std::string, std::any> decodeDictionary(std::string bencodedText, int &index);

#endif
