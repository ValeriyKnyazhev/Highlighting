#pragma once

#include "Trie.h"

#include <string>
#include <vector>

namespace Yapynb {

class CAutocomplete {
public:
	CAutocomplete() = default;

	void ResetTrie(const std::vector<std::string>& specialWords);
	std::vector<std::string> GetCompletions(const std::string& prefix, size_t limit);

private:	
	CTrie Trie;
};

}
