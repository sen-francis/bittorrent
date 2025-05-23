#ifndef BENCODE_UTIL
#define BENCODE_UTIL
#include <string>
#include <any>
#include <vector>
#include "bencode.h"

std::string encode(std::any decoded);
Bencode decode(std::vector<unsigned char> bencodedText, int &index);
std::string decodeByteString(std::vector<unsigned char> bencodedText, int &index);
long long decodeInteger(std::vector<unsigned char> bencodedText, int &index);
List decodeList(std::vector<unsigned char> bencodedText, int &index);
Dictionary decodeDictionary(std::vector<unsigned char> bencodedText, int &index);

#endif
