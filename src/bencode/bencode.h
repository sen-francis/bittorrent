#ifndef BENCODE
#define BENCODE

#include <string>
#include <unordered_map>
#include <variant>
#include <list>
#include <vector>

struct List;
struct Dictionary;

template <typename T> struct recursive_wrapper {
	// construct from an existing object
	recursive_wrapper(T t_) { t.emplace_back(std::move(t_)); }
	// cast back to wrapped type
	operator const T &() const { return t.front(); }
	// store the value
	std::vector<T> t;
};

using Value = std::variant<
std::string, 
long long, 
recursive_wrapper<List>, 
recursive_wrapper<Dictionary>>;
using Bencode = Value;

struct List {
	std::list<Value> values;
};

struct Dictionary {
	std::unordered_map<std::string, Value> values;
};

#endif
