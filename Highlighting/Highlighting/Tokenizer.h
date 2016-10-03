#pragma once

#include <string>
#include <istream>
#include <memory>

namespace Yapynb {

struct CToken {
public:
	enum class TType {
		Comment,
		StringLiteral,
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
};

class CPythonTokenizer : public ITokenizer {
public:
	CPythonTokenizer(const std::string& text);

	CToken Next() override;

private:
	class CImpl;
	std::unique_ptr<CImpl> impl;
};

}  // Yapynb
