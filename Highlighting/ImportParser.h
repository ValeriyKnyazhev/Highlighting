#pragma once

#include "Tokenizer.h"
#include <unordered_set>
#include <vector>

namespace Yapynb {

	class ImportParser {

	private:
		void processFrom(
			const std::vector<std::pair<CToken, size_t>>& tokens,
			size_t cur,
			std::unordered_set<std::string>& identifiers );

		size_t addIndexWithPoint( 
			const size_t, const std::vector<std::pair<CToken, size_t>>& );
		void getAttribute( std::unordered_set<std::string>&, size_t&, 
			const std::vector<std::pair<CToken, size_t>>& );
	public:
		std::unordered_set<std::string> getImports( 
			const std::vector<std::pair<CToken, size_t>>& );
	};

}  // Yapynb