#include "stdafx.h"
#include "TestImports.h"


void TestImports::test()
{
	ImportParser parser;
	std::vector<CToken> tokens = {
		CToken( CToken::TType::Identifier, "from" ),
		CToken( CToken::TType::Whitespace, " " ),
		CToken( CToken::TType::Identifier, "a" ),
		CToken( CToken::TType::Whitespace, " " ),
		CToken( CToken::TType::Other, "." ),
		CToken( CToken::TType::Whitespace, " " ),
		CToken( CToken::TType::Identifier, "b" ),
		CToken( CToken::TType::Whitespace, " " ),
		CToken( CToken::TType::Identifier, "import" ),
		CToken( CToken::TType::Whitespace, " " ),
		CToken( CToken::TType::Identifier, "e" ),
		CToken( CToken::TType::Whitespace, " " ),
		CToken( CToken::TType::Identifier, "as" ),
		CToken( CToken::TType::Whitespace, " " ),
		CToken( CToken::TType::Identifier, "f" ),
		CToken( CToken::TType::Other, "," ),
		CToken( CToken::TType::Whitespace, " " ),
		CToken( CToken::TType::Identifier, "c" ),
		CToken( CToken::TType::Whitespace, " " ),
		CToken( CToken::TType::Other, "," ),
		CToken( CToken::TType::Whitespace, " " ),
		CToken( CToken::TType::Identifier, "d" )
	};
	std::unordered_set<std::string> result = parser.getImports( tokens );
	assert( result.size() == 3 && result.find( "f" ) != result.end() &&
		result.find( "c" ) != result.end() && result.find( "d" ) != result.end() );
}