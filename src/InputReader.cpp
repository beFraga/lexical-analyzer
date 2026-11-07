#include <iostream>
#include <fstream>
#include <sstream>
#include "InputReader.h"
using namespace std;


vector<tuple<string, string>> InputReader::readFile(const string & addressToRead) {
    vector<tuple<string, string>> lines;
    string line;

    ifstream fileToRead(addressToRead);
    if (!fileToRead.is_open()) {
        cerr << "Error: was not possible to open file " << addressToRead << endl;
        return lines;
    }
    
	string delimeter = ": ";
    while (getline(fileToRead, line)) {
		if (line.empty()) continue;

		size_t delim = line.find(delimeter);
		string st, nd;

		if (delim == std::string::npos) {
			std::cerr << "Warning: skipping line\n";
			continue;
		}

		st = line.substr(0, delim);
		nd = line.substr(delim + delimeter.length());

		lines.emplace_back(st, nd);
    }

    fileToRead.close();    
    return lines;
}
