// -*- coding: utf-8 -*-
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
	// открываем файл fileConfig, в котором содержатся ключевые слова, которые надо подсвечивать
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

void ModuleHighlightingAndAutocomplete::coloredOutput(
	std::ostream& resultStream,
	const std::string& word
) {
	if (word.empty()) {
		return;
	}
	auto keyWordIt = keyWords.find(word);
	if (keyWordIt != keyWords.end()) {
		resultStream << "<font color = ";
		switch (keyWordIt->second) {
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
		resultStream << word << "</font>";
	} else {
		resultStream << "<font color = 'black'>" << word << "</font>";
	}
}

void ModuleHighlightingAndAutocomplete::parse(
	std::istream& input,
	std::ostream& resultStream
) {
	resultStream << "<text>\n";
	std::string word;
	for (char currentSymbol = input.get(); input; currentSymbol = input.get()) {
		if (isalpha(currentSymbol)) {
			word += currentSymbol;
		} else {
			coloredOutput(resultStream, word);
			word.clear();
			resultStream << currentSymbol;
		}
	}
	coloredOutput(resultStream, word);
	resultStream << "\n</text>";
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
