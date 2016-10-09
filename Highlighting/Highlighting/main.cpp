#include <iostream>
#include <string>
#include <vector>
#include "Tokenizer.h"
#include <unordered_set>
#include "Highlighting.h"
#include "IdentifierParser.h"
#include "TestIdentifier.h"
#include "TestImports.h"
#include "TrieTest.h"

using namespace Yapynb;

int main() {
	TrieTest();
	std::cout << "Trie test was successful\n";

	std::cout << (
		(testIdentifiers1() == true)
		? "Identifiers parser passed the test.\n"
		: "Identifiers parser failed the test.\n"
	);

	TestImports::test();

	std::cout << "Now enter the input for highlighter:\n";

	std::string text{
		std::istreambuf_iterator<char>(std::cin),
		std::istreambuf_iterator<char>()
	};
	CHighlighting high(text);
	high.OutputTagged(std::cout);
	
	return 0;
}
