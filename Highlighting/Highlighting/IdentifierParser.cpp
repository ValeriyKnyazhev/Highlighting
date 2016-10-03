#include "Tokenizer.h"
#include <unordered_set>
#include <string>
#include <vector>
#include "IdentifierParser.h"

namespace Yapynb {

	std::unordered_set<std::string> IdentifierParser::getIdentifiers(const std::vector<CToken>& tokens) {
		std::unordered_set<std::string> identifiers;

		for (size_t i = 2; i < tokens.size(); ++i) {
			if (tokens[i].Type == CToken::TType::Identifier && tokens[i - 1].Type == CToken::TType::Whitespace &&
				(tokens[i - 2].Text == "class" || tokens[i - 2].Text == "def")) {
				identifiers.insert(tokens[i].Text);
			}
		}

		return identifiers;
	}


}