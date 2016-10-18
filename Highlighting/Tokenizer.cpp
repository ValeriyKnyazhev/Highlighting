#include "stdafx.h"
#include "Tokenizer.h"

#include <regex>


namespace Yapynb {
	size_t ITokenizer::GetScope( const std::string& whiteSpaceLine )
	{
		size_t scope = 0;
		size_t spaceSequenceSize = 0;
		for( size_t i = 0; i < whiteSpaceLine.size(); ++i ) {
			if( whiteSpaceLine[i] == ' ' ) {
				spaceSequenceSize++;
				if( spaceSequenceSize == 4 ) {
					scope += 4;
					spaceSequenceSize = 0;
				}
			} else if( whiteSpaceLine[i] == '\t' ) {
				scope += 4;
				spaceSequenceSize = 0;
			}
		}
		if( spaceSequenceSize > 0 ) {
			scope += spaceSequenceSize;
		}
		return scope;
	}

	std::vector<std::pair<CToken, size_t>> ITokenizer::Tokenize()
	{
		size_t scope = 0;
		bool isFirstLine = true;
		std::vector<std::pair<CToken, size_t>> result;
		do {
			CToken next = Next();
			if( isFirstLine ) {
				if( next.Type == CToken::TType::Whitespace ) {
					scope = GetScope( next.Text );
				}
				isFirstLine = false;
			}
			if (next.Type == CToken::TType::EndOfLine) {
				std::regex rgx("\\n+");
				std::smatch match;
				std::regex_search( next.Text, match, rgx );
				if( match[0].str().size() != next.Text.size() ) {
					CToken endOfLine = CToken( CToken::TType::EndOfLine, match[0].str() );
					result.push_back( std::make_pair( endOfLine, scope ) );
					next = CToken( CToken::TType::Whitespace, 
						next.Text.substr( match[0].str().size() ) );
				}
				scope = GetScope( next.Text );
			}
			result.push_back( std::make_pair( next, scope ) );
		} while( result.back().first.Type != CToken::TType::End );
		result.pop_back();
		return result;
	}

	namespace {

		const auto RegexFlags =
			std::regex_constants::ECMAScript
			| std::regex_constants::nosubs
			| std::regex_constants::optimize
			;

		const std::vector<std::pair<CToken::TType, std::regex>> TokenRegexps{
			{CToken::TType::Comment, std::regex( "#.*\\n", RegexFlags )},
			{CToken::TType::StringLiteral, std::regex( R"re(('([^']|\')*')|("([^"]\')*"))re", RegexFlags )},
			{CToken::TType::EndOfLine, std::regex( "\\n+[\\t ]+", RegexFlags )},
			{CToken::TType::Whitespace, std::regex( "[\\t ]+", RegexFlags )},
			{CToken::TType::Identifier, std::regex( R"re(\w\w*)re", RegexFlags )},
			{CToken::TType::Number, std::regex( R"re((\d+(\.?\d*)|\.\d+)j?)re", RegexFlags )},
		};

	}

	class CPythonTokenizer::CImpl {
	public:
		CImpl( const std::string& text )
			: begin( text.begin() )
			, end( text.end() )
		{
		}

		CToken Next()
		{
			CToken best;
			best.Type = CToken::TType::End;
			for( const auto& tokenRegexp : TokenRegexps ) {
				std::smatch matchedHere;
				if( std::regex_search( begin, end, matchedHere, tokenRegexp.second ) ) {
					std::ssub_match here = matchedHere[0];
					if( here.first == begin && here.length() > (int)best.Text.size() ) {
						best.Type = tokenRegexp.first;
						best.Text = here.str();
					}
				}
			}
			if( best.Type == CToken::TType::End && begin != end ) {
				best = CToken( CToken::TType::Other, std::string( begin, begin + 1 ) );
			}
			std::advance( begin, best.Text.size() );
			return best;
		}

	private:
		std::string::const_iterator begin;
		std::string::const_iterator end;
	};

	CPythonTokenizer::CPythonTokenizer( const std::string& text )
		: impl( new CImpl( text ) )
	{
	}

	CPythonTokenizer::~CPythonTokenizer()
	{
		// dtor should be here to provide std::unique_ptr with right deleter
	}

	CToken CPythonTokenizer::Next()
	{
		return impl->Next();
	}

}  // Yapynb
