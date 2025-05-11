#ifndef BENCODE_UTIL
#define BENCODE_UTIL
	#include <string>
	#include <memory>
	#include "de_bencode.h"
	
	std::string encode(std::string plainText);
	std::unique_ptr<DeBencode> decode(std::string bencodedText, int &index);
	std::unique_ptr<StringDeBencode> decodeByteString(std::string bencodedText, int &index);
	std::unique_ptr<IntegerDeBencode> decodeInteger(std::string bencodedText, int &index);
	std::unique_ptr<ListDeBencode> decodeList(std::string bencodedText, int &index);
	std::unique_ptr<DictionaryDeBencode> decodeDictionary(std::string bencodedText, int &index);

#endif
