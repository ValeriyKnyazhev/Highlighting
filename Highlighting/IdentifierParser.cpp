#include "stdafx.h"

#include "Tokenizer.h"
#include "IdentifierParser.h"

namespace Yapynb {

	std::unordered_set<std::string> IdentifierParser::getIdentifiers( 
		const std::vector<std::pair<CToken, size_t>>& tokens 
		) {
		std::unordered_set<std::string> identifiers;

		for( size_t i = 2; i < tokens.size(); ++i ) {
			if( 
				tokens[i].first.Type == CToken::TType::Identifier && 
				tokens[i - 1].first.Type == CToken::TType::Whitespace &&
				(tokens[i - 2].first.Text == "class" || tokens[i - 2].first.Text == "def") 
				) {
				identifiers.insert( tokens[i].first.Text );
			}
		}

		return identifiers;
	}


}