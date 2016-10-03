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

class Highlighting {
private:
	std::unordered_map<std::string, Color> keyWords;//for each keyword, map contains the color number for display in the XML file
	void coloredOutput(std::ostream& stream, const std::string& word);
	void parse(std::istream& input, std::ostream& result);//parse text file to xml with color font

public:
	Highlighting() = default;
	// read file with keywords
	Highlighting(const std::string& fileConfig);


	
	void HighlightText(const std::string& fileName);//extract code with highlighting from file with name(fileName) to file with name("Highlighted_" + fileName)

};
