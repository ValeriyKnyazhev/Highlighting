#include <iostream>
#include "Highlighting.h"
#include "TestImports.h"

int main() {
	Highlighting Highlighting("keywords.config");
	Highlighting.HighlightText("test.txt");
	TestImports::test();
	return 0;
}