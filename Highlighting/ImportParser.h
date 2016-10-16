#pragma once

#include "Tokenizer.h"
#include <unordered_set>
#include <vector>

namespace Yapynb {

class ImportParser {

private:
	size_t addIndexWithPoint(const size_t, const std::vector<CToken>&);
	void getAttribute(std::unordered_set<std::string>&, size_t&, const std::vector<CToken>&);
public:
	std::unordered_set<std::string> getImports(const std::vector<CToken>&);
};

}  // Yapynb