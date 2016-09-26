#include "ModuleHighlightingAndAutocomplete.h"
#include <string>
#include <sstream>
#include <fstream>

ModuleHighlightingAndAutocomplete::ModuleHighlightingAndAutocomplete(std::string fileConfig) {
	stringKeyWords = fileConfig;
	readFileKeyWords();
}

ModuleHighlightingAndAutocomplete::ModuleHighlightingAndAutocomplete() {
	stringKeyWords = "";
}

void ModuleHighlightingAndAutocomplete::readFileKeyWords() {
	//открываем файл fileConfig, в котором содержатся ключевые слова, которые надо подсвечивать
	std::ifstream configFile;
	configFile.open( stringKeyWords );
	if (configFile) {
		std::string keyWord;
		int color;
		while (configFile >> keyWord) {
			configFile >> color;
			keyWords[keyWord] = static_cast<Color>(color);
		}
		configFile.close();
	}
}

void ModuleHighlightingAndAutocomplete::parse(
	std::istream& input,
	std::ostream& resultStream
) {
	resultStream << "<text>\n<font color = 'black'>";
	std::string word = "";
	for (char currentSymbol = input.get(); input; currentSymbol = input.get()) {
		if (currentSymbol == '\n' || currentSymbol == ' ') {
			bool isKeyword = false;
			if (word.size() > 0) {
				for (auto it : keyWords) {
					if (word.substr( 0, it.first.size() ) == it.first) {
						isKeyword = true;
						resultStream << "</font>\n<font color = ";
						switch (it.second) {
							case Blue: {
								resultStream << "'blue'>";
								break;
							}
							case Red: {
								resultStream << "'red'>";
								break;
							}
							case Green: {
								resultStream << "'green'>";
								break;
							}
						}
						resultStream << it.first << "</font>\n<font color = 'black'>";
						if (it.first.size() < word.size()) {
							resultStream << word.substr(it.first.size());
						}
						break;
					}
				}
				if (!isKeyword) {
					resultStream << word;
				}
			}
			word = "";
			resultStream << currentSymbol;
		} else {
			word += currentSymbol;
		}
	}
	resultStream << "</font>\n</text>";
}

void ModuleHighlightingAndAutocomplete::HighlightText(std::string fileName) {
	std::ifstream inputFile(fileName);
	if (inputFile) {
		std::ofstream outputFile("Highlighted_" + fileName);
		if (outputFile) {
			parse(inputFile, outputFile);
		}
	}
}
