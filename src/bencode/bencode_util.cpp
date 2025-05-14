#include <string>
#include <map>
#include <any>
#include <list>
#include <iostream>
#include "bencode_util.h"
using namespace std;

string encode(string plainText) {
	return plainText;
}

any decode(string bencodedText, int &index) {
	if (bencodedText.empty()) {
		cerr << "Bencoded text was not initialized or empty.";
		abort();	
	}

	if (isdigit(bencodedText.at(index))) {
		return decodeByteString(bencodedText, index);
	}
	else if (bencodedText.at(index) == 'd') {
		return decodeDictionary(bencodedText, index);
	}
	else if (bencodedText.at(index) == 'l') {
		return decodeList(bencodedText, index);
	}
	else if (bencodedText.at(index) == 'i') {
		return decodeInteger(bencodedText, index);
	}

	cerr << "Bencoded text formatted incorrectly.";
	abort();	
}

map<string, any> decodeDictionary(string bencodedText, int &index) {
	if (bencodedText.at(index) == 'd') {
		index++;
	}
	else {
		cerr << "Did not find start char for bencoded dictionary.";
		abort();
	}
	map<string, any> dictionary;
	while (index < bencodedText.size() && bencodedText.at(index) != 'e') {
		string propertyName = decodeByteString(bencodedText, index);
		any propertyValue = decode(bencodedText, index);
		dictionary[propertyName] = propertyValue;
	}
	index++;
	return dictionary;
}

string decodeByteString(string bencodedText, int &index) {
	string bencodedTextLengthStr = "";
	while (isdigit(bencodedText.at(index))) {
		if (index >= bencodedText.size()) {
			cerr << "Could not decode byte string. Failed to parse length due to index out of bounds.";
			abort();
		}
		bencodedTextLengthStr += bencodedText.at(index);
		index++;
	}
	int bencodedTextLength = stoi(bencodedTextLengthStr);
	string propertyName = bencodedText.substr(index+1, bencodedTextLength);
	index += 1 + bencodedTextLength;
	return propertyName;
}

list<any> decodeList(string bencodedText, int &index) {
	if (bencodedText.at(index) == 'l') {
		index++;
	}
	else {
		cerr << "Did not find start char for bencoded list.";
		abort();
	}
	list<any> list;
	while (index < bencodedText.size() && bencodedText.at(index) != 'e') {
		list.push_back(decode(bencodedText, index));
	}
	index++;
	return list;
}

long long decodeInteger(string bencodedText, int &index) {
	if (bencodedText.at(index) =='i') {
		index++;
	}
	else {
		cerr << "Did not find start char for bencoded integer.";
		abort();
	}
	string numberStr = "";
	while (index <= bencodedText.size() && bencodedText.at(index) != 'e') {
		numberStr += bencodedText.at(index);
		index++;
	}
	index++;
	return stoll(numberStr);
}
