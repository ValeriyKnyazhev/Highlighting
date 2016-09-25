#include "ModuleHighlightingAndAutoCompleteon.h"
#include <string>
#include <fstream>

ModuleHighlightingAndAutoCompleteon::ModuleHighlightingAndAutoCompleteon(std::string fileConfig) {
	//открываем файл fileConfig, в котором содержатся ключевые слова, которые надо подсвечивать
	keyWords = std::map<std::string, Color>();
	stringKeyWords = fileConfig;
}

ModuleHighlightingAndAutoCompleteon::ModuleHighlightingAndAutoCompleteon() {
	
}

void ModuleHighlightingAndAutoCompleteon::readFileKeyWords() {
	std::ifstream fin;
	fin.open(stringKeyWords);

	if (fin) {
		std::string keyWord;
		int color;

		while (fin >> keyWord) {
			fin >> color;
			keyWords[keyWord] = static_cast<Color>(color);
		}

	}

	fin.close();
}

void ModuleHighlightingAndAutoCompleteon::init() {
	readFileKeyWords();
}

std::string ModuleHighlightingAndAutoCompleteon::getHighlightingTextString(std::string) {

	return 0;
}