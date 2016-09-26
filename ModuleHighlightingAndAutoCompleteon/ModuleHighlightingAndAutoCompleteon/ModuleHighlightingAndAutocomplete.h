#pragma once
#include <string>
#include <map>

class ModuleHighlightingAndAutocomplete {
private:
	enum Color {
		Red, Blue, Green
	};
	std::map<std::string, Color> keyWords;//��� ������� ��������� ����� �������� ����� ����� ��� �����������
	std::string stringKeyWords;
	void readFileKeyWords();
	std::string parse(std::string);

public:
	ModuleHighlightingAndAutocomplete(std::string);
	ModuleHighlightingAndAutocomplete();
	
	void HighlightText(std::string);

	

};