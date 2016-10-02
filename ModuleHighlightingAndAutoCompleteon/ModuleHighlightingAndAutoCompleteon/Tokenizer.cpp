#include "Tokenizer.h"

#include <regex>


namespace Yapynb {

namespace {

const auto RegexFlags =
	std::regex_constants::ECMAScript
	| std::regex_constants::nosubs
	| std::regex_constants::optimize
;

const std::vector<std::pair<CToken::TType, std::regex>> TokenRegexps{
	{CToken::TType::Comment, std::regex("^#.*\\n", RegexFlags)},
	{CToken::TType::StringLiteral, std::regex(R"re(^('([^']|\')*')|("([^"]\')*"))re", RegexFlags)},
	{CToken::TType::Whitespace, std::regex("^\\s+", RegexFlags)},
	{CToken::TType::Identifier, std::regex(R"re(^(_|[:alpha:])\w*)re", RegexFlags)},
	{CToken::TType::Number, std::regex(R"re(^(\d+(\.?\d*)|\.\d+)j?)re", RegexFlags)},
	{CToken::TType::Other, std::regex(R"re(^.)re", RegexFlags)},
	{CToken::TType::End, std::regex(R"re(^$)re", RegexFlags)},
};

}

class CPythonTokenizer::CImpl {
public:
	CImpl(const std::string& text)
		: begin(text.end())
		, end(text.end())
	{
	}

	CToken Next() {
		std::pair<CToken::TType, std::smatch> bestMatch;
		bestMatch.first = CToken::TType::End;
		for (const auto& tokenRegexp : TokenRegexps) {
			std::smatch bestHere = *std::max_element(
				std::sregex_iterator(begin, end, tokenRegexp.second),
				std::sregex_iterator(),
				[](const std::smatch& a, const std::smatch& b) {
					return a.length() < b.length();
				}
			);
			if (bestHere.length() > bestMatch.second.length()) {
				bestMatch.first = tokenRegexp.first;
				bestMatch.second = bestHere;
			}
		}
		std::advance(begin, bestMatch.second.length());
		return CToken(bestMatch.first, bestMatch.second.str());
	}

private:
	std::string::const_iterator begin;
	std::string::const_iterator end;
};

CPythonTokenizer::CPythonTokenizer(const std::string& text)
	: impl(new CImpl(text))
{
}

CToken CPythonTokenizer::Next() {
	return impl->Next();
}

}  // Yapynb
