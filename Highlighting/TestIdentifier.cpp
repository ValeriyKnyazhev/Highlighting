#include <vector>
#include <unordered_set>
#include "IdentifierParser.h"
#include "Tokenizer.h"

namespace Yapynb {

	void fillVectorTokensForTestIdentifiers1(std::vector<CToken>& tokens) {
		tokens.push_back(CToken(CToken::TType::Identifier, "class"));
		tokens.push_back(CToken(CToken::TType::Whitespace, "	"));
		tokens.push_back(CToken(CToken::TType::Identifier, "MyClass"));
		tokens.push_back(CToken(CToken::TType::Identifier, "def"));
		tokens.push_back(CToken(CToken::TType::Whitespace, " "));
		tokens.push_back(CToken(CToken::TType::Identifier, "getMyClass"));
		tokens.push_back(CToken(CToken::TType::End, "\n"));
	}

	void fillSetIdentifiersTest1(std::unordered_set<std::string>& identifiers) {
		identifiers.insert("MyClass");
		identifiers.insert("getMyClass");
	}

	bool testIdentifiers1() {
		std::vector<CToken> tokens;
		fillVectorTokensForTestIdentifiers1(tokens);

		std::unordered_set<std::string> validIdentifiers;
		fillSetIdentifiersTest1(validIdentifiers);

		IdentifierParser identifierParser;
		std::unordered_set<std::string> identifiers = identifierParser.getIdentifiers(tokens);

		if (identifiers == validIdentifiers) {
			return true;
		}
		else {
			return false;
		}

	}
}