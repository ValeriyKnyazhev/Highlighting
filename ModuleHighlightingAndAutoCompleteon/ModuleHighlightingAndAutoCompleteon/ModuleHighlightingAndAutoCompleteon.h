#pragma once
#include <string>
#include <map>

class ModuleHighlightingAndAutoCompleteon {
private:
	enum Color {
		Red, Green, Blue
	};
	std::map<std::string, Color> KeyWords;//��� ������� ��������� ����� �������� ����� ����� ��� �����������

	void readFileKeyWords(std::string);

public:
	ModuleHighlightingAndAutoCompleteon(std::string);
	ModuleHighlightingAndAutoCompleteon();

	std::string getHighlightingTextString(std::string);
	

};