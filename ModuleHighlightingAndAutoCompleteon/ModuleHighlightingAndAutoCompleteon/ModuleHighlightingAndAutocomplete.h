#pragma once
#include <string>
#include <map>

class ModuleHighlightingAndAutocomplete {
private:
	enum Color {
		Red, Blue, Green
	};
	std::map<std::string, Color> keyWords;//for each keyword, map contains the color number for display in the XML file
	std::string stringKeyWords;
	void readFileKeyWords();//read file with all keywords and colors for it
	std::string parse(std::string text);//parse text file to xml with color font

public:
	ModuleHighlightingAndAutocomplete(std::string fileConfig);//set file with keywords
	ModuleHighlightingAndAutocomplete();
	
	void HighlightText(std::string fileName);//extract code with highlighting from file with name(fileName) to file with name("Highlighted_" + fileName)

};