#include "stdafx.h"

#include "Tokenizer.h"
#include <unordered_set>
#include "Highlighting.h"
#include "IdentifierParser.h"
#include "TestIdentifier.h"
#include "TestImports.h"
#include "TextProcessor.h"
#include "TrieTest.h"


using namespace Yapynb;

int main()
{
	TrieTest();
	std::cout << "Trie test was successful\n";

	std::ifstream fin( "test.txt" );
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
	processor.ResetText( text );
	std::cout << processor.GetTaggedText();
	std::cout << "Enter the prefix:\n";
	std::string prefix;
	std::cin >> prefix;
	std::vector<std::string> completions = processor.GetCompletions( prefix );
	if( completions.size() > 0 ) {
		std::cout << completions.size() << " completions found:\n";
	} else {
		std::cout << "No completions found.\n";
	}
	for( std::string word : completions ) {
		std::cout << prefix << word << std::endl;
	}
	system( "pause" );
	return 0;
}
