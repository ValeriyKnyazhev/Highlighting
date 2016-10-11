#include <iostream>
#include <string>
#include <vector>
#include "Tokenizer.h"
#include <unordered_set>
#include "Highlighting.h"
#include "IdentifierParser.h"
#include "TestIdentifier.h"
#include "TestImports.h"
#include "TextProcessor.h"
#include "TrieTest.h"
#include <sstream>
#include <fstream>

using namespace Yapynb;

int main() {
	TrieTest();
	std::cout << "Trie test was successful\n";

	std::ifstream fin("test.txt");
	std::stringstream buffer;
	buffer << fin.rdbuf();
	std::string text = buffer.str();

	std::cout << (
		(testIdentifiers1() == true)
		? "Identifiers parser passed the test.\n"
		: "Identifiers parser failed the test.\n"
	);

	TestImports::test();

	CTextProcessor processor;
	processor.ResetText(text);
	std::cout << processor.GetTaggedText();
	system("pause");
	return 0;
}
