#pragma once

#include "Tokenizer.h"
#include "Highlighting.h"
#include "ImportParser.h"
#include "IdentifierParser.h"

#include <string>
#include <unordered_set>
#include <vector>

namespace Yapynb {

class CTextProcessor {
public:
	CTextProcessor() = default;

	void ResetText(const std::string& text);
	std::string GetTaggedText();

private:
	CHighlighting highlighter;
	std::vector<CToken> Tokens;
	std::vector<std::string> specialWords;

	static IdentifierParser idParser;
	static ImportParser importParser;
};

}
