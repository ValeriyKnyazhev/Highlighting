#include "stdafx.h"
#include "Autocomplete.h"

#include <iterator>

namespace Yapynb
{

	void Yapynb::CAutocomplete::ResetTrie( const std::vector<std::string>& specialWords )
	{
		Trie = CTrie();
		for( auto word : specialWords ) {
			Trie.AppendWord( word.begin(), word.end() );
		}
	}

	std::vector<std::string> Yapynb::CAutocomplete::GetCompletions(
		const std::string & prefix,
		size_t limit
	)
	{
		auto pos = Trie.Go( prefix.begin(), prefix.end() );
		std::vector<std::string> result;
		Trie.FindCompletions( std::back_inserter( result ), pos, limit );
		return result;
	}

}
