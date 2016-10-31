#include "stdafx.h"
#include "ImportParser.h"

namespace Yapynb
{
	void ImportParser::processFrom( 
		const std::vector<std::pair<CToken, size_t>>& tokens, 
		size_t cur, std::unordered_set<std::string>& imports 
		) {
		if (
			tokens[cur].first.Type != CToken::TType::Identifier ||
			tokens[cur].first.Text != "from"
			) {
			return;
		}
		cur++;
		if( 
			cur >= tokens.size() || 
			tokens[cur].first.Type != CToken::TType::Whitespace 
			) {
			return;
		} 
		cur++;
		size_t add = 0;
		while( 
			cur < tokens.size() && 
			tokens[cur].first.Type == CToken::TType::Identifier &&
			(add = addIndexWithPoint( cur, tokens )) > 0 
			) {
			cur += add;
		}
		if( 
			cur >= tokens.size() || 
			tokens[cur].first.Type != CToken::TType::Identifier 
			) {
			return;
		}
		cur++;
		if( 
			cur >= tokens.size() || 
			tokens[cur].first.Type != CToken::TType::Whitespace ) {
			return;
		}
		cur++;
		if (
			tokens[cur].first.Type != CToken::TType::Identifier ||
			tokens[cur].first.Text != "import"
			) {
			return;
		}
		cur++;
		if( 
			cur >= tokens.size() || 
			tokens[cur].first.Type != CToken::TType::Whitespace 
			) {
			return;
		}
		cur++;
		while( cur < tokens.size() ) {
			if( tokens[cur].first.Type == CToken::TType::Whitespace ) {
				cur++;
			}
			getAttribute( imports, cur, tokens );
			if( 
				cur < tokens.size() && 
				tokens[cur].first.Type == CToken::TType::Whitespace 
				) {
				cur++;
			}
			if( 
				cur >= tokens.size() || 
				tokens[cur].first.Type != CToken::TType::Other ||
				tokens[cur].first.Text != "," 
				) {
				return;
			} 
			cur++;
		}
	}

	size_t ImportParser::addIndexWithPoint(
		size_t cur, 
		const std::vector<std::pair<CToken, size_t>>& tokens 
		) {
		size_t result = 1;
		if( cur + result == tokens.size() ) {
			return 0;
		}
		if( tokens[cur + result].first.Type == CToken::TType::Whitespace ) {
			result++;
			if( cur + result == tokens.size() ) {
				return 0;
			}
		}
		if( 
			tokens[cur + result].first.Type == CToken::TType::Other && 
			tokens[cur + result].first.Text == "." 
			) {
			result++;
			if( 
				cur + result < tokens.size() && 
				tokens[cur + result].first.Type == CToken::TType::Whitespace 
				) {
				result++;
			}
			return result;
		}
		return 0;
	}

	void ImportParser::getAttribute( 
		std::unordered_set<std::string>& imports, size_t& i,
		const std::vector<std::pair<CToken, size_t>>& tokens 
		) {
		if( 
			i + 4 < tokens.size() && 
			tokens[i + 1].first.Type == CToken::TType::Whitespace &&
			tokens[i + 2].first.Type == CToken::TType::Identifier && 
			tokens[i + 2].first.Text == "as" &&
			tokens[i + 3].first.Type == CToken::TType::Whitespace &&
			tokens[i + 4].first.Type == CToken::TType::Identifier 
			) {
			imports.insert( tokens[i + 4].first.Text );
			i += 5;
		} else if( tokens[i].first.Type == CToken::TType::Identifier ) {
			imports.insert( tokens[i].first.Text );
			i++;
		}
	}

	std::unordered_set<std::string> ImportParser::getImports( 
		const std::vector<std::pair<CToken, size_t>>& tokens 
		) {
		std::unordered_set<std::string> imports;
		for( size_t i = 0; i < tokens.size(); ++i ) {
			size_t cur = i;
			processFrom( tokens, cur, imports );
		}
		return imports;
	}

}