#include <iostream>
#include "Highlighting.h"

int main() {
	Highlighting Highlighting("keywords.config");
	Highlighting.HighlightText("test.txt");
	return 0;
}