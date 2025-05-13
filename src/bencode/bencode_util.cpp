#include <string>
#include <map>
#include <any>
#include <list>
#include <iostream>
#include "bencode_util.h"
#include "de_bencode.h"
using namespace std;

string encode(string plainText) {
	return plainText;
}

unique_ptr<DeBencode> decode(string bencodedText, int &index) {
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

unique_ptr<DictionaryDeBencode> decodeDictionary(string bencodedText, int &index) {
	if (bencodedText.at(index) == 'd') {
		index++;
	}
	else {
		cerr << "Did not find start char for bencoded dictionary.";
		abort();
	}
	unique_ptr<DictionaryDeBencode> decoded = unique_ptr<DictionaryDeBencode>(new DictionaryDeBencode());
	while (bencodedText.at(index) != 'e') {
		unique_ptr<StringDeBencode> propertyName = decodeByteString(bencodedText, index);
		unique_ptr<DeBencode> propertyValue = decode(bencodedText, index);
		decoded->dictionary[propertyName->str] = *propertyValue;
	}
	return decoded;
}

unique_ptr<StringDeBencode> decodeByteString(string bencodedText, int &index) {
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
	return unique_ptr<StringDeBencode>(new StringDeBencode(propertyName));
}

unique_ptr<ListDeBencode> decodeList(string bencodedText, int &index) {
	if (bencodedText.at(index) == 'l') {
		index++;
	}
	else {
		cerr << "Did not find start char for bencoded list.";
		abort();
	}
	unique_ptr<ListDeBencode> decoded = unique_ptr<ListDeBencode>(new ListDeBencode());
	while (bencodedText.at(index) != 'e') {
		decoded->list.push_back(*decode(bencodedText, index));
	}
	return decoded;
}

unique_ptr<IntegerDeBencode> decodeInteger(string bencodedText, int &index) {
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
	return unique_ptr<IntegerDeBencode>(new IntegerDeBencode(stoll(numberStr)));
}
