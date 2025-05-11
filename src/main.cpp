#include <iostream>
#include <string>
#include <fstream>
#include "bencode_util.h"

using namespace std;

int main() {
	ifstream file("alice.torrent");
	string bencodedText;
	string str;
	while(getline(file, str)) {
		bencodedText += str;
		//cout << bencodedText << ' ';
	}
	file.close();
	//cout << bencodedText << "blah";
	int index = 0;
	unique_ptr<DeBencode> tmp = decode(bencodedText, index);
//	if (tmp->type == DeBencodeType::STRING) {
//		StringDeBencode* tmp2= dynamic_cast<StringDeBencode*>(tmp.get());
//		cout << tmp2->str;
//	}
	if (tmp->type == DeBencodeType::DICTIONARY) {
		DictionaryDeBencode* dict = dynamic_cast<DictionaryDeBencode*>(tmp.get());
		for(auto const& [key, val] : dict->dictionary) {
			//cout << key << ' '  << val << endl;
			cout << val.toString();
		}
	}
	return 0;
}
