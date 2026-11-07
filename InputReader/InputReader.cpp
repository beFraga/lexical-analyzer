#include <iostream>
#include <fstream>
#include "InputReader.hpp"
using namespace std;

InputReader::InputReader(){}

vector<string> InputReader::readFile(const string & addressToRead) {
    vector<string> linesArray;
    string textRead;

    ifstream fileToRead(addressToRead);
    if (!fileToRead.is_open()) {
        cerr << "Erro: Nao foi possivel abrir o arquivo " << addressToRead << endl;
        return linesArray;
    }
    
    while (getline(fileToRead, textRead)) {
        linesArray.push_back(textRead);
    }

    fileToRead.close();    
    return linesArray;
}
