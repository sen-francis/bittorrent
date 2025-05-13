#include <string>
#include <map>
#include <any>
#include <iostream>
#include "de_bencode.h"
using namespace std;

StringDeBencode::StringDeBencode(string str) {
	this->type = DeBencodeType::STRING;
	this->str = str;
}

std::string StringDeBencode::toString() {
	return this->str;
}

IntegerDeBencode::IntegerDeBencode(long long num) {
	this->type = DeBencodeType::INTEGER;
	this->num = num;
}

std::string IntegerDeBencode::toString() {
	reutrn to_string(this->num);
}

ListDeBencode::ListDeBencode() {
	this->type = DeBencodeType::LIST;
}

std::string ListDeBencode::toString() {
	return "";
}

DictionaryDeBencode::DictionaryDeBencode() {
	this->type = DeBencodeType::DICTIONARY; 
}

std::string DictionaryDeBencode::toString() {
	return "";
}


