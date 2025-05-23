#ifndef BENCODE
#define BENCODE

#include <string>
#include <unordered_map>
#include <list>
#include <boost/variant.hpp>

struct List;
struct Dictionary;

using Value = boost::variant<
std::string, 
long long, 
boost::recursive_wrapper<List>, 
boost::recursive_wrapper<Dictionary>>;
using Bencode = Value;

struct List {
	std::list<Value> values;
};

struct Dictionary {
	std::unordered_map<std::string, Value> values;
};

#endif
