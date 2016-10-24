#pragma once

#include <string>
#include <memory>
#include <vector>

namespace Yapynb {

struct CToken {
public:
	enum class TType {
		Comment,
		StringLiteral,
		EndOfLine,
		Whitespace,
		Identifier,
		Number,
		Other,
		End,
	};

	CToken()
		: Type(TType::Other)
	{
	}

	CToken(TType type, std::string text)
		: Type(type)
		, Text(std::move(text))
	{
	}

	TType Type;
	std::string Text;
};

class ITokenizer {
public:
	virtual CToken Next() = 0;

	virtual ~ITokenizer() {
	}

	size_t GetScope( const std::string& whiteSpaceLine );

	std::vector<std::pair<CToken, size_t>> Tokenize();
};

class CPythonTokenizer : public ITokenizer {
public:
	explicit CPythonTokenizer(const std::string& text);

	~CPythonTokenizer() override;

	CToken Next() override;

private:
	class CImpl;
	std::unique_ptr<CImpl> impl;
};

}  // Yapynb
