#ifndef BENCODE_UTIL
#define BENCODE_UTIL
	#include <string>
	#include <map>
	#include <list>
	#include <any>
	#include <vector>
	#include <variant>

	using Bencode = std::variant<
		std::string,
		long long,
		std::list<std::any>,
		std::map<std::string, std::any>
	>;

	std::string encode(std::any decoded);
	Bencode decode(std::vector<unsigned char> bencodedText, int &index);
	std::string decodeByteString(std::vector<unsigned char> bencodedText, int &index);
	long long decodeInteger(std::vector<unsigned char> bencodedText, int &index);
	std::list<Bencode> decodeList(std::vector<unsigned char> bencodedText, int &index);
	std::map<std::string, Bencode> decodeDictionary(std::vector<unsigned char> bencodedText, int &index);

#endif
