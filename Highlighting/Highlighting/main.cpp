#include <iostream>
#include <string>
#include <vector>
#include "Tokenizer.h"
#include <unordered_set>
#include "Highlighting.h"
#include "IdentifierParser.h"
#include "TestIdentifier.h"

using namespace Yapynb;

int main() {
	std::string text{
		std::istreambuf_iterator<char>(std::cin),
		std::istreambuf_iterator<char>()
	};

	CHighlighting high(text);
	high.OutputTagged(std::cout);
	
	std::cout << ((testIdentifiers1() == true) ? "Test is successfull completed.\n" : "Test is failed.\n");

	return 0;
}
