#include <iostream>
#include "ModuleHighlightingAndAutocomplete.h"

int main() {
	ModuleHighlightingAndAutocomplete moduleHighlightingAndAutocomplete = ModuleHighlightingAndAutocomplete("keywords.config");
	moduleHighlightingAndAutocomplete.Init();
	moduleHighlightingAndAutocomplete.HighlightText("test.txt");
	return 0;
}