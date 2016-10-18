#pragma once

#include "Tokenizer.h"
#include <unordered_set>
#include <string>
#include <vector>

namespace Yapynb {

	class IdentifierParser {
	public:
		std::unordered_set<std::string> getIdentifiers( 
			const std::vector<std::pair<CToken, size_t>>& tokens );

	};


}
