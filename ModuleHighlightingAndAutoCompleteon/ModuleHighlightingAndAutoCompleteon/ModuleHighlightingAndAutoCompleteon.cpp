#include "ModuleHighlightingAndAutoCompleteon.h"
#include <string>

ModuleHighlightingAndAutoCompleteon::ModuleHighlightingAndAutoCompleteon(std::string fileConfig) {
	//��������� ���� fileConfig, � ������� ���������� �������� �����, ������� ���� ������������
	readFileKeyWords(fileConfig);
}

ModuleHighlightingAndAutoCompleteon::ModuleHighlightingAndAutoCompleteon() {
	
}

void ModuleHighlightingAndAutoCompleteon::readFileKeyWords(std::string) {

}

std::string ModuleHighlightingAndAutoCompleteon::getHighlightingTextString(std::string) {

	return 0;
}