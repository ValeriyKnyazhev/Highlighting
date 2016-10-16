#include "stdafx.h"
#include "TextProcessor.h"

namespace Yapynb {

	extern const std::unordered_set<std::string> Keywords;
	extern const std::unordered_set<std::string> Builtins;

	IdentifierParser CTextProcessor::idParser = IdentifierParser();
	ImportParser CTextProcessor::importParser = ImportParser();

	void CTextProcessor::ResetText( const std::string & text )
	{
		CPythonTokenizer tokenizer( text );
		Tokens = tokenizer.Tokenize();
		UserDefined = idParser.getIdentifiers( Tokens );
		Imported = importParser.getImports( Tokens );
	}

	std::string CTextProcessor::GetTaggedText()
	{
		Highlighter.ResetTokens( Tokens, UserDefined, Imported );
		std::ostringstream stream;
		Highlighter.OutputTagged( stream );
		return stream.str();
	}

	std::vector<std::string> CTextProcessor::GetCompletions( const std::string& prefix, size_t limit )
	{
		std::vector<std::string> specialWords;
		std::copy( UserDefined.begin(), UserDefined.end(), std::back_inserter( specialWords ) );
		std::copy( Imported.begin(), Imported.end(), std::back_inserter( specialWords ) );
		std::copy( Keywords.begin(), Keywords.end(), std::back_inserter( specialWords ) );
		std::copy( Builtins.begin(), Builtins.end(), std::back_inserter( specialWords ) );
		Autocompleter.ResetTrie( specialWords );
		return Autocompleter.GetCompletions( prefix, limit );
	}



}
