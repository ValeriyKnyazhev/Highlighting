#pragma once

#include <vector>
#include <unordered_set>
#include "Tokenizer.h"

namespace Yapynb {

	void fillVectorTokensForTestIdentifiers1(std::vector<CToken>& tokens);

	void fillSetIdentifiersTest1(std::unordered_set<std::string>& identifiers);

	bool testIdentifiers1();
}