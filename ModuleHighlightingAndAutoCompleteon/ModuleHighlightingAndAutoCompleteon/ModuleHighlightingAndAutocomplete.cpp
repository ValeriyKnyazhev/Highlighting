#include "ModuleHighlightingAndAutocomplete.h"
#include <string>
#include <sstream>
#include <fstream>

ModuleHighlightingAndAutocomplete::ModuleHighlightingAndAutocomplete(std::string fileConfig) {
	keyWords = std::map<std::string, Color>();
	stringKeyWords = fileConfig;
}

ModuleHighlightingAndAutocomplete::ModuleHighlightingAndAutocomplete() {
	keyWords = std::map<std::string, Color>();
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

std::string ModuleHighlightingAndAutocomplete::parse(std::string text) {
	std::stringstream resultStream;
	resultStream << "<text>\n<font color = 'black'>";
	std::string word = "";
	size_t index = 0;
	while (index < text.size()) {
		if (text[index] == '\n' || text[index] == ' ') {
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
			resultStream << text[index];
		} else {
			word += text[index];
		}
		index++;
	}
	resultStream << "</font>\n</text>";
	return resultStream.str();
}

void ModuleHighlightingAndAutocomplete::Init() {
	readFileKeyWords();
}

void ModuleHighlightingAndAutocomplete::HighlightText(std::string fileName) {
	std::ifstream inputFile;
	inputFile.open(fileName);
	if (inputFile) {
		std::stringstream stringStream;
		stringStream << inputFile.rdbuf();
		std::string text = stringStream.str();
		inputFile.close();
		std::ofstream outputFile;
		outputFile.open("Highlighted_" + fileName);
		if (outputFile) {
			outputFile << parse(text);
			outputFile.close();
		}
	}
}