#include <iostream>
#include "ModuleHighlightingAndAutoCompleteon.h"

int main() {
	ModuleHighlightingAndAutoCompleteon moduleHighlightingAndAutoCompleteon = ModuleHighlightingAndAutoCompleteon("keywords.config");
	moduleHighlightingAndAutoCompleteon.init();

	return 0;
}