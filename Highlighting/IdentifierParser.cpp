#include "stdafx.h"

#include "Tokenizer.h"
#include "IdentifierParser.h"

namespace Yapynb {
	void IdentifierParser::processFor( 
		const std::vector<std::pair<CToken, size_t>>& tokens, 
		size_t cur, 
		std::unordered_set<std::string>& forVariables
		) {
		if (
			tokens[cur].first.Type != CToken::TType::Identifier ||
			tokens[cur].first.Text != "for"
			) {
			return;
		}
		cur++;
		if (cur >= tokens.size() ||
			tokens[cur].first.Type != CToken::TType::Whitespace
			) {
			return;
		}
		cur++;
		while( cur < tokens.size() ) {
			if( tokens[cur].first.Type == CToken::TType::Whitespace ) {
				cur++;
			}
			if( 
				cur < tokens.size() &&
				tokens[cur].first.Type == CToken::TType::Identifier
				) {
				forVariables.insert( tokens[cur].first.Text );
				cur++;
			}
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

	void IdentifierParser::processEquals( 
		const std::vector<std::pair<CToken, size_t>>& tokens, 
		size_t cur, 
		std::vector<std::pair<size_t, std::unordered_set<std::string> > >& identifiers 
		) {
		if (tokens[cur].first.Type != CToken::TType::Other ||
			tokens[cur].first.Text != "="
			) {
			return;
		}
		if( cur > 0 && tokens[cur - 1].first.Text == "=" ) {
			return;
		}
		if( cur + 1 < tokens.size() && tokens[cur + 1].first.Text == "=" ) {
			return;
		}
		cur--;
		if( cur >= 0 &&
			tokens[cur].first.Type == CToken::TType::Whitespace
			) {
			cur--;
		}
		while( cur >= 0 ) {
			if( tokens[cur].first.Type == CToken::TType::Whitespace ) {
				if( cur == 0 ) {
					return;
				}
				cur--;
			}
			if( tokens[cur].first.Type == CToken::TType::Identifier ) {
				identifiers.back().second.insert( tokens[cur].first.Text );
				if( cur == 0 ) {
					return;
				}
				cur--;
			}
			if( tokens[cur].first.Type == CToken::TType::Whitespace ) {
				if( cur == 0 ) {
					return;
				}
				cur--;
			}
			if(
				tokens[cur].first.Type == CToken::TType::Other &&
				tokens[cur].first.Text == ","
				) {
				if( cur == 0 ) {
					return;
				}
				cur--;
			} else {
				return;
			}
		}
	}

	std::unordered_set<std::string> IdentifierParser::getIdentifiers(
		const std::vector<std::pair<CToken, size_t>>& tokens 
		) {
		std::vector<std::pair<size_t, std::unordered_set<std::string> > > identifiers;
		std::unordered_set<std::string> forVariables;
		size_t previousScope = 0;
		identifiers.push_back( 
			std::make_pair( 
				previousScope, 
				std::unordered_set<std::string>() 
			) 
		);
		for (size_t i = 0; i < tokens.size(); ++i) {
			if( tokens[i].second != previousScope ) {
				if( tokens[i].second > previousScope ) {
					previousScope = tokens[i].second;
					identifiers.push_back(
						std::make_pair(
							previousScope,
							forVariables
						) 
					);
					forVariables.clear();
				} else {
					previousScope = tokens[i].second;
					while( 
						identifiers.size() > 0 && 
						identifiers.back().first > previousScope 
						) {
						identifiers.pop_back();
					}
				}
			} 
			size_t cur = i;
			processFor( tokens, cur, forVariables );
			processEquals(  tokens, cur, identifiers );
			if (
				i + 2 < tokens.size() &&
				tokens[i].first.Type == CToken::TType::Identifier &&
				(tokens[i].first.Text == "class" ||
					tokens[i].first.Text == "def") &&
				tokens[i + 1].first.Type == CToken::TType::Whitespace &&
				tokens[i + 2].first.Type == CToken::TType::Identifier
				) {
				identifiers.back().second.insert( tokens[i + 2].first.Text );
			}
		}
		std::unordered_set<std::string> result;
		for( size_t i = 0; i < identifiers.size(); ++i ) {
			for (auto it = identifiers[i].second.begin(); it != identifiers[i].second.end(); ++it) {
				std::cout << identifiers[i].first << " " << *it << std::endl;
			}
			result.insert( identifiers[i].second.begin(), identifiers[i].second.end() );
		}
		return result;
	}

}