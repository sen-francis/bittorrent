#include <sstream>
#include <iomanip>
#include "uri_encode.h"

using namespace std;

string encodeUriComponent(string component) {
	ostringstream encoded; 
	encoded.fill('0');
	encoded << hex;

	for (string::value_type c : component) {
		// Keep alphanumeric and other accepted characters intact
		if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
			encoded << c;
		}
		else {
			// Any other characters are percent-encoded
			encoded << uppercase;
			encoded << '%' << setw(2) << int((unsigned char) c);
			encoded << nouppercase;
		}
	}

	return encoded.str();
}
