#include <iostream>
#include "ModuleHighlightingAndAutocomplete.h"

int main() {
	ModuleHighlightingAndAutocomplete moduleHighlightingAndAutocomplete("keywords.config");
	moduleHighlightingAndAutocomplete.HighlightText("test.txt");
	return 0;
}