#pragma once

#include "precompiled.h"

//Необходимо продумать архитектуру, как всё будет взаимодейтвовать, ибо пока что это всего лишь копия CellWindow.
//А в CellWindow методы-"костыли", чтобы извлекать данные отсюда, но чтобы не делать CellWindow public.
//Без связи с другими модулями трудно пока это представить.
class CellResult
{
public:

	CellResult();

	void Create(HWND parentHandle);

	void Show(int cmdShow);

	HWND getHandle() const;

	unsigned int getHeight() const;
	bool changeHeight(unsigned int countOfStrings);

	bool getExistence() const;
	void setExistence(bool existence);

	std::wstring getText() const;

	friend bool operator== (const CellResult& left, const CellResult& right);

private:

	HWND handleCellResult;
	unsigned int height;
	unsigned int countOfStrings;
	bool isExist;

	void init();
};
