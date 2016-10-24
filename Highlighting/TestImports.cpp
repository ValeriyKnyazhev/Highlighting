#include "stdafx.h"
#include "TestImports.h"


void TestImports::test()
{
	ImportParser parser;
	std::vector<std::pair<CToken, size_t>> tokens = {
		std::make_pair( CToken( CToken::TType::Identifier, "from" ), 0 ),
		std::make_pair( CToken( CToken::TType::Whitespace, " " ), 0 ),
		std::make_pair( CToken( CToken::TType::Identifier, "a" ), 0 ),
		std::make_pair( CToken( CToken::TType::Whitespace, " " ), 0 ),
		std::make_pair( CToken( CToken::TType::Other, "." ), 0 ),
		std::make_pair( CToken( CToken::TType::Whitespace, " " ), 0 ),
		std::make_pair( CToken( CToken::TType::Identifier, "b" ), 0 ),
		std::make_pair( CToken( CToken::TType::Whitespace, " " ), 0 ),
		std::make_pair( CToken( CToken::TType::Identifier, "import" ), 0 ),
		std::make_pair( CToken( CToken::TType::Whitespace, " " ), 0 ),
		std::make_pair( CToken( CToken::TType::Identifier, "e" ), 0 ),
		std::make_pair( CToken( CToken::TType::Whitespace, " " ), 0 ),
		std::make_pair( CToken( CToken::TType::Identifier, "as" ), 0 ),
		std::make_pair( CToken( CToken::TType::Whitespace, " " ), 0 ),
		std::make_pair( CToken( CToken::TType::Identifier, "f" ), 0 ),
		std::make_pair( CToken( CToken::TType::Other, "," ), 0 ),
		std::make_pair( CToken( CToken::TType::Whitespace, " " ), 0 ),
		std::make_pair( CToken( CToken::TType::Identifier, "c" ), 0 ),
		std::make_pair( CToken( CToken::TType::Whitespace, " " ), 0 ),
		std::make_pair( CToken( CToken::TType::Other, "," ), 0 ),
		std::make_pair( CToken( CToken::TType::Whitespace, " " ), 0 ),
		std::make_pair( CToken( CToken::TType::Identifier, "d" ), 0 )
	};
	std::unordered_set<std::string> result = parser.getImports( tokens );
	assert( result.size() == 3 && result.find( "f" ) != result.end() &&
		result.find( "c" ) != result.end() && result.find( "d" ) != result.end() );
}