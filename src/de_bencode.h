#ifndef DE_BENCODE
#define DE_BENCODE
	#include <string>
	#include <map>
	#include <any>
	#include <list>
	

	enum class DeBencodeType {DICTIONARY, LIST, STRING, INTEGER};

	struct DeBencode {
		DeBencodeType type;
		virtual ~DeBencode() = default;
		virtual std::string toString();
	};
	
	struct StringDeBencode : DeBencode {
		std::string str;
		StringDeBencode(std::string str);
	};

	struct IntegerDeBencode : DeBencode {
		long long num;
		IntegerDeBencode(long long num);
	};

	struct ListDeBencode : DeBencode {
		std::list<DeBencode> list;
		ListDeBencode();
	};

	struct DictionaryDeBencode : DeBencode {
		std::map<std::string, DeBencode> dictionary;
		DictionaryDeBencode();
	};

#endif
