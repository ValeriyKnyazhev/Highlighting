#include "stdafx.h"
#include "IdentifierParser.h"
#include "Tokenizer.h"

namespace Yapynb {

	void fillVectorTokensForTestIdentifiers1( std::vector<std::pair<CToken, size_t>>& tokens )
	{
		tokens.push_back( std::make_pair( CToken( CToken::TType::Identifier, "class" ), 0 ) );
		tokens.push_back( std::make_pair( CToken( CToken::TType::Whitespace, "	" ), 0 ) );
		tokens.push_back( std::make_pair( CToken( CToken::TType::Identifier, "MyClass" ), 0 ) );
		tokens.push_back( std::make_pair( CToken( CToken::TType::Identifier, "def" ), 0 ) );
		tokens.push_back( std::make_pair( CToken( CToken::TType::Whitespace, " " ), 0 ) );
		tokens.push_back( std::make_pair( CToken( CToken::TType::Identifier, "getMyClass" ), 0 ) );
		tokens.push_back( std::make_pair( CToken( CToken::TType::End, "\n" ), 0 ) );
	}

	void fillSetIdentifiersTest1( std::unordered_set<std::string>& identifiers )
	{
		identifiers.insert( "MyClass" );
		identifiers.insert( "getMyClass" );
	}

	bool testIdentifiers1()
	{
		std::vector<std::pair<CToken, size_t>> tokens;
		fillVectorTokensForTestIdentifiers1( tokens );

		std::unordered_set<std::string> validIdentifiers;
		fillSetIdentifiersTest1( validIdentifiers );

		IdentifierParser identifierParser;
		std::unordered_set<std::string> identifiers = identifierParser.getIdentifiers( tokens );

		if( identifiers == validIdentifiers ) {
			return true;
		} else {
			return false;
		}

	}
}