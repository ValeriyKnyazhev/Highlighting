#include "Tokenizer.h"

#include <regex>


namespace Yapynb {

std::vector<CToken> ITokenizer::Tokenize() {
	std::vector<CToken> result;
	do {
		result.push_back(Next());
	} while (result.back().Type != CToken::TType::End);
	return result;
}

namespace {

const auto RegexFlags =
	std::regex_constants::ECMAScript
	| std::regex_constants::nosubs
	| std::regex_constants::optimize
;

const std::vector<std::pair<CToken::TType, std::regex>> TokenRegexps{
	{CToken::TType::Comment, std::regex("^#.*\\n", RegexFlags)},
	{CToken::TType::StringLiteral, std::regex(R"re(^('([^']|\')*')|("([^"]\')*"))re", RegexFlags)},
	{CToken::TType::EndOfLine, std::regex("^\\n+", RegexFlags)},
	{CToken::TType::Whitespace, std::regex("^[\\t ]+", RegexFlags)},
	{CToken::TType::Identifier, std::regex(R"re(^(_|[[:alpha:]])\w*)re", RegexFlags)},
	{CToken::TType::Number, std::regex(R"re(^(\d+(\.?\d*)|\.\d+)j?)re", RegexFlags)},
	{CToken::TType::Other, std::regex(R"re(^.)re", RegexFlags)},
	{CToken::TType::End, std::regex(R"re(^$)re", RegexFlags)},
};

}

class CPythonTokenizer::CImpl {
public:
	CImpl(const std::string& text)
		: begin(text.begin())
		, end(text.end())
	{
	}

	CToken Next() {
		CToken best;
		best.Type = CToken::TType::End;
		for (const auto& tokenRegexp : TokenRegexps) {
			std::smatch matchedHere;
			if (std::regex_search(begin, end, matchedHere, tokenRegexp.second)) {
				auto bestHere = *std::max_element(
					matchedHere.begin(),
					matchedHere.end(),
					[](const auto& a, const auto& b) {
					return a.length() < b.length();
				}
				);
				if (bestHere.length() > (int)best.Text.size()) {
					best.Type = tokenRegexp.first;
					best.Text = bestHere.str();
				}
			}
		}
		std::advance(begin, best.Text.size());
		return best;
	}

private:
	std::string::const_iterator begin;
	std::string::const_iterator end;
};

CPythonTokenizer::CPythonTokenizer(const std::string& text)
	: impl(new CImpl(text))
{
}

CPythonTokenizer::~CPythonTokenizer() {
	// dtor should be here to provide std::unique_ptr with right deleter
}

CToken CPythonTokenizer::Next() {
	return impl->Next();
}

}  // Yapynb
