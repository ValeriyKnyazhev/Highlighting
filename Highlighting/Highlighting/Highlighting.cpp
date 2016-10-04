// -*- coding: utf-8 -*-
#include "Highlighting.h"
#include "ImportParser.h"
#include "Tokenizer.h"

namespace Yapynb {

const std::unordered_set<std::string> CHighlighting::Keywords{
	"and",
	"as",
	"assert",
	"break",
	"class",
	"continue",
	"def",
	"del",
	"elif",
	"else",
	"except",
	"exec",
	"finally",
	"for",
	"from",
	"global",
	"if",
	"import",
	"in",
	"is",
	"lambda",
	"not",
	"or",
	"pass",
	"print",
	"raise",
	"return",
	"try",
	"while",
	"with",
	"yield",
};

const std::unordered_set<std::string> CHighlighting::Builtins{
	"ArithmeticError",
	"AssertionError",
	"AttributeError",
	"BaseException",
	"BufferError",
	"BytesWarning",
	"DeprecationWarning",
	"EOFError",
	"Ellipsis",
	"EnvironmentError",
	"Exception",
	"False",
	"FloatingPointError",
	"FutureWarning",
	"GeneratorExit",
	"IOError",
	"ImportError",
	"ImportWarning",
	"IndentationError",
	"IndexError",
	"KeyError",
	"KeyboardInterrupt",
	"LookupError",
	"MemoryError",
	"NameError",
	"None",
	"NotImplemented",
	"NotImplementedError",
	"OSError",
	"OverflowError",
	"PendingDeprecationWarning",
	"ReferenceError",
	"RuntimeError",
	"RuntimeWarning",
	"StandardError",
	"StopIteration",
	"SyntaxError",
	"SyntaxWarning",
	"SystemError",
	"SystemExit",
	"TabError",
	"True",
	"TypeError",
	"UnboundLocalError",
	"UnicodeDecodeError",
	"UnicodeEncodeError",
	"UnicodeError",
	"UnicodeTranslateError",
	"UnicodeWarning",
	"UserWarning",
	"ValueError",
	"Warning",
	"ZeroDivisionError",
	"_",
	"__debug__",
	"__doc__",
	"__import__",
	"__name__",
	"__package__",
	"abs",
	"all",
	"any",
	"apply",
	"basestring",
	"bin",
	"bool",
	"buffer",
	"bytearray",
	"bytes",
	"callable",
	"chr",
	"classmethod",
	"cmp",
	"coerce",
	"compile",
	"complex",
	"copyright",
	"credits",
	"delattr",
	"dict",
	"dir",
	"divmod",
	"enumerate",
	"eval",
	"execfile",
	"exit",
	"file",
	"filter",
	"float",
	"format",
	"frozenset",
	"getattr",
	"globals",
	"hasattr",
	"hash",
	"help",
	"hex",
	"id",
	"input",
	"int",
	"intern",
	"isinstance",
	"issubclass",
	"iter",
	"len",
	"license",
	"list",
	"locals",
	"long",
	"map",
	"max",
	"memoryview",
	"min",
	"next",
	"object",
	"oct",
	"open",
	"ord",
	"pow",
	"print",
	"property",
	"quit",
	"range",
	"raw_input",
	"reduce",
	"reload",
	"repr",
	"reversed",
	"round",
	"set",
	"setattr",
	"slice",
	"sorted",
	"staticmethod",
	"str",
	"sum",
	"super",
	"tuple",
	"type",
	"unichr",
	"unicode",
	"vars",
	"xrange",
	"zip",
};

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
