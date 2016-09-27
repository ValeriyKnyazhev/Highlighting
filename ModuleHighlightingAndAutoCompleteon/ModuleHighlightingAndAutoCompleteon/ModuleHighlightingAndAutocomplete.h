#pragma once
#include <istream>
#include <ostream>
#include <string>
#include <unordered_map>

enum class Color {
    Red,
    Blue,
    Green,
    Black,
};

std::istream& operator >> (std::istream& stream, Color& color);
std::ostream& operator << (std::ostream& stream, Color color);

class ModuleHighlightingAndAutocomplete {
private:
	std::unordered_map<std::string, Color> keyWords;//for each keyword, map contains the color number for display in the XML file
	std::string stringKeyWords;
	void readFileKeyWords();//read file with all keywords and colors for it
	void coloredOutput(std::ostream& stream, const std::string& word);
	void parse(std::istream& input, std::ostream& result);//parse text file to xml with color font

public:
	ModuleHighlightingAndAutocomplete(std::string fileConfig);//set file with keywords
	ModuleHighlightingAndAutocomplete();
	
	void HighlightText(const std::string& fileName);//extract code with highlighting from file with name(fileName) to file with name("Highlighted_" + fileName)

};
