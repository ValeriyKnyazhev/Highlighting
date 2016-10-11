// -*- coding: utf-8 -*-
#include "Highlighting.h"
#include "ImportParser.h"
#include "Tokenizer.h"

namespace Yapynb {

extern const std::unordered_set<std::string> Keywords;
extern const std::unordered_set<std::string> Builtins;

CHighlighting::CHighlighting(const std::string& text) {
	ResetText(text);
}

void CHighlighting::ResetText(const std::string& text) {
	CPythonTokenizer tokenizer(text);
	Tokens = tokenizer.Tokenize();

	IdentifierParser idParser;
	UserDefined = idParser.getIdentifiers(Tokens);

	ImportParser importParser;
	Imported = importParser.getImports(Tokens);
}

const char* CHighlighting::TokenTag(const CToken& token) {
	switch (token.Type) {
		case CToken::TType::Comment:
			return "comment";
		case CToken::TType::StringLiteral:
			return "string";
		case CToken::TType::EndOfLine:
			return nullptr;
		case CToken::TType::Whitespace:
			return nullptr;
		case CToken::TType::Other:
			return nullptr;
		case CToken::TType::Number:
			return "number";
		case CToken::TType::Identifier:
			if (Keywords.count(token.Text)) {
				return "keyword";
			} else if (Builtins.count(token.Text)) {
				return "builtin";
			} else if (UserDefined.count(token.Text)) {
				return "user-defined";
			} else if (Imported.count(token.Text)){
				return "imported";
			} else {
				return nullptr;
			}
		case CToken::TType::End:
			throw std::logic_error("End token should not be here");
	}
	throw std::logic_error(
		"Unexpected token type "
		+ std::to_string(int(token.Type))
		+ " with text '" + token.Text + "'"
	);
}

void CHighlighting::OutputTagged(std::ostream& stream) {
	for (const CToken& token : Tokens) {
		auto tag = TokenTag(token);
		if (tag) {
			stream << "<" << tag << ">";
		}
		stream << token.Text;
		if (tag) {
			stream << "</" << tag << ">";
		}
	}
}

}
