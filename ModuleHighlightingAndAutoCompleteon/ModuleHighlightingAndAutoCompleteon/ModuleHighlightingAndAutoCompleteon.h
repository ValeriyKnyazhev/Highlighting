#pragma once
#include <string>
#include <map>

class ModuleHighlightingAndAutoCompleteon {
private:
	enum Color {
		Blue, Red, Green
	};
	std::map<std::string, Color> keyWords;//��� ������� ��������� ����� �������� ����� ����� ��� �����������
	std::string stringKeyWords;
	void readFileKeyWords();

public:
	ModuleHighlightingAndAutoCompleteon(std::string);
	ModuleHighlightingAndAutoCompleteon();

	void init();
	std::string getHighlightingTextString(std::string);

	

};