#include "TextProcessor.h"
#include <sstream> 
#include <iterator> 

namespace Yapynb {

extern const std::unordered_set<std::string> Keywords;
extern const std::unordered_set<std::string> Builtins;

IdentifierParser CTextProcessor::idParser = IdentifierParser();
ImportParser CTextProcessor::importParser = ImportParser();

void CTextProcessor::ResetText(const std::string & text) {
	CPythonTokenizer tokenizer(text);
	Tokens = tokenizer.Tokenize();
	std::unordered_set<std::string> userDefined = idParser.getIdentifiers(Tokens);
	std::unordered_set<std::string> imported = importParser.getImports(Tokens);
	highlighter.ResetTokens(Tokens, userDefined, imported);
	std::copy(userDefined.begin(), userDefined.end(), std::back_inserter(specialWords));
	std::copy(imported.begin(), imported.end(), std::back_inserter(specialWords));
	std::copy(Keywords.begin(), Keywords.end(), std::back_inserter(specialWords));
	std::copy(Builtins.begin(), Builtins.end(), std::back_inserter(specialWords));
}

std::string CTextProcessor::GetTaggedText() {
	std::ostringstream stream;
	highlighter.OutputTagged(stream);
    return stream.str();
}



}
