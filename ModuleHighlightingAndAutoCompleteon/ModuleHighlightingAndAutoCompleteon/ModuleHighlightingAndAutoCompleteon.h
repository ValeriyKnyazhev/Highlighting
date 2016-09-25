#pragma once
#include <string>
#include <map>

class ModuleHighlightingAndAutoCompleteon {
private:
	enum Color {
		Red, Green, Blue
	};
	std::map<std::string, Color> KeyWords;//для каждого ключевого слова содержит номер цвета для отображения

	void readFileKeyWords(std::string);

public:
	ModuleHighlightingAndAutoCompleteon(std::string);
	ModuleHighlightingAndAutoCompleteon();

	std::string getHighlightingTextString(std::string);
	

};