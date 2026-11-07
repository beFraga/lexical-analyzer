#pragma once
#include <string>
#include <vector>
#include <tuple>
using namespace std;

/* Como usar:
#include "InputReader.hpp"
using namespace std;
...
    const string fileToRead = "fileToRead.txt";
    vector<string> linesArray = InputReader::readFile(fileToRead);
...

--- Retorna um array das linhas do arquivo de texto
*/

class InputReader {
public:
    static vector<tuple<string, string>> readFile(const string & addressToRead);
};
