#pragma once

#include "Tokenizer.h"
#include "Highlighting.h"
#include "Autocomplete.h"
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
	std::vector<std::string> GetCompletions(
		const std::string& prefix, 
		size_t limit = std::numeric_limits<int>::max()
		);

private:
	CHighlighting Highlighter;
	CAutocomplete Autocompleter;
	std::vector<CToken> Tokens;
	std::unordered_set<std::string> UserDefined;
	std::unordered_set<std::string> Imported;

	static IdentifierParser idParser;
	static ImportParser importParser;
};

}
