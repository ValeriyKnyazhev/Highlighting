#pragma once

#include "Tokenizer.h"
#include <unordered_set>
#include <string>
#include <vector>

namespace Yapynb {

	class IdentifierParser {
	private:
		void processFor(
			const std::vector<std::pair<CToken, size_t>>& tokens,
			size_t cur,
			std::vector<std::pair<size_t, std::unordered_set<std::string> > >& identifiers );

		void processEquals(
			const std::vector<std::pair<CToken, size_t>>& tokens,
			size_t cur,
			std::vector<std::pair<size_t, std::unordered_set<std::string> > >& identifiers );
	public:

		std::unordered_set<std::string> getIdentifiers( 
			const std::vector<std::pair<CToken, size_t>>& tokens );

	};


}
