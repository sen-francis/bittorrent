#include <string>
#include <map>
#include <any>
#include <list>
#include <iostream>
#include <vector>
#include "bencode_util.h"
#include "bencode.h"
using namespace std;

string encode (any decoded) {
	string bencoded = "";
	if (decoded.type() == typeid(map<string, any>)) {
		bencoded += "d";
		map<string, any> dictionary = any_cast<map<string, any>>(decoded);
		for (auto const& [key, val] : dictionary) {
			bencoded += encode(key) + encode(val);
		}
		bencoded += "e";
	}
	else if (decoded.type() == typeid(list<any>)) {
		bencoded += "l";
		list<any> l = any_cast<list<any>>(decoded);
		for (any val : l) {
			bencoded += encode(val);
		}
		bencoded += "e";
	}
	else if (decoded.type() == typeid(string)) {
		string value = any_cast<string>(decoded);
		bencoded += to_string(value.size()) + ":" + value;
		
	}
	else if (decoded.type() == typeid(long long)) {
		long long value = any_cast<long long>(decoded);
		bencoded += "i" + to_string(value) + "e";
		
	}

	return bencoded;
}


Bencode decode(vector<unsigned char> bencodedText, int &index) {
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

Dictionary decodeDictionary(vector<unsigned char> bencodedText, int &index) {
	if (bencodedText.at(index) == 'd') {
		index++;
	}
	else {
		cerr << "Did not find start char for bencoded dictionary.";
		abort();
	}
	Dictionary dictionary;
	while (index < bencodedText.size() && bencodedText.at(index) != 'e') {
		string propertyName = decodeByteString(bencodedText, index);
		if (propertyName == "pieces") {
			cout << "hi";
		}
		Bencode propertyValue = decode(bencodedText, index);
		dictionary.values[propertyName] = propertyValue;
	}
	index++;
	return dictionary;
}

string decodeByteString(vector<unsigned char> bencodedText, int &index) {
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
	index++;
	string propertyName;
	while (propertyName.size() < bencodedTextLength) {
		propertyName += bencodedText.at(index);
		index++;
	}
	
	return propertyName;
}

List decodeList(vector<unsigned char> bencodedText, int &index) {
	if (bencodedText.at(index) == 'l') {
		index++;
	}
	else {
		cerr << "Did not find start char for bencoded list.";
		abort();
	}
	List list;
	while (index < bencodedText.size() && bencodedText.at(index) != 'e') {
		list.values.push_back(decode(bencodedText, index));
	}
	index++;
	return list;
}

long long decodeInteger(vector<unsigned char> bencodedText, int &index) {
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
