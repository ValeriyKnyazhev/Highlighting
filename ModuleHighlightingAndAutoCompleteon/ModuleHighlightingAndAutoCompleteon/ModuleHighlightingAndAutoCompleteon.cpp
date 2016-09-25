#include "ModuleHighlightingAndAutoCompleteon.h"
#include <string>

ModuleHighlightingAndAutoCompleteon::ModuleHighlightingAndAutoCompleteon(std::string fileConfig) {
	//открываем файл fileConfig, в котором содержатся ключевые слова, которые надо подсвечивать
	readFileKeyWords(fileConfig);
}

ModuleHighlightingAndAutoCompleteon::ModuleHighlightingAndAutoCompleteon() {
	
}

void ModuleHighlightingAndAutoCompleteon::readFileKeyWords(std::string) {

}

std::string ModuleHighlightingAndAutoCompleteon::getHighlightingTextString(std::string) {

	return 0;
}