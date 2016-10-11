#pragma once

#include "Tokenizer.h"
#include "IdentifierParser.h"

#include <istream>
#include <ostream>
#include <string>
#include <unordered_set>
#include <vector>

namespace Yapynb {

class CHighlighting {
public:
	CHighlighting() = default;
	explicit CHighlighting(const std::string& text);

	void ResetText(const std::string& text);

	void OutputTagged(std::ostream& stream);

private:
	const char* TokenTag(const CToken& token);

	std::unordered_set<std::string> UserDefined;
	std::unordered_set<std::string> Imported;

	std::vector<CToken> Tokens;
};

}
