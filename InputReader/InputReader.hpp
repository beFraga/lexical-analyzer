#ifndef INPUTREADER_HPP
#define INPUTREADER_HPP
#include <string>
#include <vector>
using namespace std;

/* Como usar:
#include "InputReader.hpp"
using namespace std;
...
    const string fileToRead = "fileToRead.txt";
    InputReader reader;
    vector<string> linesArray = reader.readFile(fileToRead);
...

--- Retorna um array das linhas do arquivo de texto
*/

class InputReader {
public:
    InputReader();

    vector<string> readFile(const string & addressToRead);
};

#endif
