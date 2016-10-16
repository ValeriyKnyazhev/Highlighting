#pragma once

#include "Tokenizer.h"

#include <istream>
#include <ostream>
#include <string>
#include <unordered_set>
#include <vector>

namespace Yapynb {

	class CHighlighting {
	public:
		CHighlighting() = default;
		void ResetTokens( const std::vector<CToken>& tokens,
			const std::unordered_set<std::string>& userDefined,
			const std::unordered_set<std::string>& imported );
		void OutputTagged( std::ostream& stream );

	private:
		const char* TokenTag( const CToken& token );

		std::unordered_set<std::string> UserDefined;
		std::unordered_set<std::string> Imported;
		std::vector<CToken> Tokens;
	};

}
