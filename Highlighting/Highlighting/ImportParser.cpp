#include "ImportParser.h"

namespace Yapynb
{
	size_t ImportParser::addIndexWithPoint(size_t cur, const std::vector<CToken>& tokens) {
		size_t result = 1;
		if (cur + result == tokens.size()) {
			return 0;
		}
		if (tokens[cur + result].Type == CToken::TType::Whitespace) {
			result++;
			if (cur + result == tokens.size()) {
				return 0;
			}
		}
		if (tokens[cur + result].Type == CToken::TType::Other && tokens[cur + result].Text == ".") {
			result++;
			if (cur + result < tokens.size() && tokens[cur + result].Type == CToken::TType::Whitespace) {
				result++;
			}
			return result;
		}
		return 0;
	}

	void ImportParser::getAttribute(std::unordered_set<std::string>& imports, size_t& i,
		const std::vector<CToken>& tokens)
	{
		if (i + 4 < tokens.size() && tokens[i + 1].Type == CToken::TType::Whitespace &&
			tokens[i + 2].Type == CToken::TType::Identifier && tokens[i + 2].Text == "as" &&
			tokens[i + 3].Type == CToken::TType::Whitespace &&
			tokens[i + 4].Type == CToken::TType::Identifier) {
			imports.insert( tokens[i + 4].Text );
			i += 5;
		} else if (tokens[i].Type == CToken::TType::Identifier) {
			imports.insert( tokens[i].Text );
			i++;
		}
	}

	std::unordered_set<std::string> ImportParser::getImports( const std::vector<CToken>& tokens )
	{
		std::unordered_set<std::string> imports;
		for (size_t i = 0; i < tokens.size(); ++i) {
			size_t cur = i;
			if (tokens[cur].Type == CToken::TType::Identifier && tokens[cur].Text == "from") {
				cur++;
				if (cur < tokens.size() && tokens[cur].Type == CToken::TType::Whitespace) {
					cur++;
				} else {
					continue;
				}
				size_t add = 0;
				while (cur < tokens.size() && tokens[cur].Type == CToken::TType::Identifier &&
					(add = addIndexWithPoint( cur, tokens )) > 0) {
					cur += add;
				}
				if (cur >= tokens.size() || tokens[cur].Type != CToken::TType::Identifier) {
					continue;
				}
				cur++;
				if (cur >= tokens.size() || tokens[cur].Type != CToken::TType::Whitespace) {
					continue;
				}
				cur++;
				if (tokens[cur].Type == CToken::TType::Identifier && tokens[cur].Text == "import") {
					cur++;
					if (cur >= tokens.size() || tokens[cur].Type != CToken::TType::Whitespace) {
						continue;
					}
					cur++;
					while(cur < tokens.size()) {
						if (tokens[cur].Type == CToken::TType::Whitespace) {
							cur++;
						}
						getAttribute( imports, cur, tokens );
						if (cur < tokens.size() && tokens[cur].Type == CToken::TType::Whitespace) {
							cur++;
						}
						if (cur < tokens.size() && tokens[cur].Type == CToken::TType::Other &&
							tokens[cur].Text == ",") {
							cur++;
						} else {
							break;
						}
					}
				}
			}
		}		
		return imports;
	}

}