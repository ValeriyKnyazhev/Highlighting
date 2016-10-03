#include <iostream>
#include <string>
#include <vector>
#include "Tokenizer.h"

using namespace Yapynb;

int main() {
	std::string text(
		std::istreambuf_iterator<char>(std::cin),
		std::istreambuf_iterator<char>()
	);

	CPythonTokenizer tokenizer(text);
	auto tokens = tokenizer.Tokenize();
	for (auto tok : tokens) {
		std::cout << tok.Text << std::endl;
	}

	return 0;
}
