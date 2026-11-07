#include "LexicalTree.h"
#include "InputReader.h"
#include <iostream>

#define INPUT_FILE "input.txt"

int main() {
	auto exprs = InputReader::readFile(INPUT_FILE);
	for (auto [id, exp] : exprs) {
		std::cout << "Tag: " << id << " | Regular expression: "<< exp << std::endl;
		LexicalTree lextree(exp);
		std::cout << std::endl;
	}
	return 0;
}
