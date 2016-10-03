#include <iostream>
#include <unordered_set>
#include <vector>
#include "Highlighting.h"
#include "IdentifierParser.h"
#include "TestIdentifier.h"
using namespace Yapynb;

int main() {
	//Highlighting Highlighting("keywords.config");
	//Highlighting.HighlightText("test.txt");
	
	std::cout << ((testIdentifiers1() == true) ? "Test is successfull completed.\n" : "Test is failed.\n");

	return 0;
}