// -*- coding: utf-8 -*-
#include "ModuleHighlightingAndAutocomplete.h"
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>

std::istream& operator >> (std::istream& stream, Color& color) {
	int value;
	stream >> value;
	color = static_cast<Color>(value);
	return stream;
}

std::ostream& operator << (std::ostream& stream, Color color) {
	switch (color) {
		case Color::Red:
			return stream << "red";
		case Color::Blue:
			return stream << "blue";
		case Color::Green:
			return stream << "green";
		case Color::Black:
			return stream << "black";
	}
	throw std::logic_error(
		"Unknown color with numeric value " + std::to_string(static_cast<int>(color))
	);
}

namespace {

std::unordered_map<std::string, Color> readKeyWordsFile(const std::string& path) {
	// открываем файл fileConfig, в котором содержатся ключевые слова, которые надо подсвечивать
	std::unordered_map<std::string, Color> result;
	std::ifstream configFile( path );
	if (configFile) {
		std::string keyWord;
		while (configFile >> keyWord) {
			Color color;
			configFile >> color;
			result[keyWord] = color;
		}
	}
	return result;
}

}  // namespace

ModuleHighlightingAndAutocomplete::ModuleHighlightingAndAutocomplete(
	const std::string& fileConfig
)
	: keyWords(readKeyWordsFile(fileConfig))
{
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
