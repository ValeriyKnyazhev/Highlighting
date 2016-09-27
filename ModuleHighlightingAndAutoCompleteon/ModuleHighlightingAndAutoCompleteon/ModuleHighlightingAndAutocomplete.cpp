// -*- coding: utf-8 -*-
#include "ModuleHighlightingAndAutocomplete.h"
#include <string>
#include <sstream>
#include <fstream>

std::istream& operator >> (std::istream& stream, Color& color) {
	int value;
	stream >> value;
	color = static_cast<Color>(value);
	return stream;
}

std::ostream& operator << (std::ostream& stream, Color color) {
	static const std::unordered_map<Color, std::string> converter{
		{Color::Red, "red"},
		{Color::Blue, "blue"},
		{Color::Green, "green"},
		{Color::Black, "black"},
	};
	return stream << converter.find(color)->second;
}

ModuleHighlightingAndAutocomplete::ModuleHighlightingAndAutocomplete(
	std::string fileConfig
)
	: stringKeyWords(std::move(fileConfig))
{
	readFileKeyWords();
}

ModuleHighlightingAndAutocomplete::ModuleHighlightingAndAutocomplete() {
}

void ModuleHighlightingAndAutocomplete::readFileKeyWords() {
	// открываем файл fileConfig, в котором содержатся ключевые слова, которые надо подсвечивать
	std::ifstream configFile;
	configFile.open( stringKeyWords );
	if (configFile) {
		std::string keyWord;
		while (configFile >> keyWord) {
			Color color;
			configFile >> color;
			keyWords[keyWord] = color;
		}
	}
}

void ModuleHighlightingAndAutocomplete::coloredOutput(
	std::ostream& resultStream,
	const std::string& word
) {
	if (word.empty()) {
		return;
	}
	auto it = keyWords.find(word);
	Color color = it != keyWords.end() ? it->second : Color::Black;
	resultStream
		<< "<font color = \"" << color << "\">"
		<< word
		<< "</font>"
	;
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

void ModuleHighlightingAndAutocomplete::HighlightText(const std::string& fileName) {
	std::ifstream inputFile(fileName);
	if (inputFile) {
		std::ofstream outputFile("Highlighted_" + fileName);
		if (outputFile) {
			parse(inputFile, outputFile);
		}
	}
}
