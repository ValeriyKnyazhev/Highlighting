#include "stdafx.h"

#include "Tokenizer.h"
#include "IdentifierParser.h"

namespace Yapynb {

	std::unordered_set<std::string> IdentifierParser::getIdentifiers( 
		const std::vector<std::pair<CToken, size_t>>& tokens 
		) {
		std::unordered_set<std::string> identifiers;

		for( size_t i = 0; i < tokens.size(); ++i ) {
			size_t cur = i;
			if(
				tokens[cur].first.Type == CToken::TType::Identifier &&
				tokens[cur].first.Text == "for"
				) {
				cur++;
				if( cur < tokens.size() &&
					tokens[cur].first.Type == CToken::TType::Whitespace
					) {
					cur++;
					while( cur < tokens.size() ) {
						if( tokens[cur].first.Type == CToken::TType::Whitespace ) {
							cur++;
						}
						if( 
							cur < tokens.size() &&
							tokens[cur].first.Type == CToken::TType::Identifier
							) {
							identifiers.insert( tokens[cur].first.Text );
							cur++;
						}
						if(
							cur < tokens.size() &&
							tokens[cur].first.Type == CToken::TType::Whitespace
							) {
							cur++;
						}
						if(
							cur < tokens.size() &&
							tokens[cur].first.Type == CToken::TType::Other &&
							tokens[cur].first.Text == ","
							) {
							cur++;
						} else {
							break;
						}
					}
				}
			}		
			if( 
				i + 2 < tokens.size() &&
				tokens[i].first.Type == CToken::TType::Identifier &&
				( tokens[i].first.Text == "class" || 
					tokens[i].first.Text == "def" ) &&
				tokens[i + 1].first.Type == CToken::TType::Whitespace &&
				tokens[i + 2].first.Type == CToken::TType::Identifier
				) {
				identifiers.insert( tokens[i + 2].first.Text );
			}
			cur = i;
			if (
				tokens[cur].first.Type == CToken::TType::Other &&
				tokens[cur].first.Text == "="
				) {
				if( cur > 0 && tokens[cur - 1].first.Text == "=" ) {
					continue;
				}
				if( cur + 1 < tokens.size() && tokens[cur + 1].first.Text == "=" ) {
					continue;
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
							break;
						}
						cur--;
					}
					if( tokens[cur].first.Type == CToken::TType::Identifier ) {
						identifiers.insert( tokens[cur].first.Text );
						if( cur == 0 ) {
							break;
						}
						cur--;
					}
					if( tokens[cur].first.Type == CToken::TType::Whitespace ) {
						if( cur == 0 ) {
							break;
						}
						cur--;
					}
					if(
						tokens[cur].first.Type == CToken::TType::Other &&
						tokens[cur].first.Text == ","
						) {
						if( cur == 0 ) {
							break;
						}
						cur--;
					} else {
						break;
					}
				}
			}	
		}
		return identifiers;
	}


}