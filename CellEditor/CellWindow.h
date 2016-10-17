#pragma once
#include "CellResult.h"

class CellWindow {
public:

	CellWindow();

	void Create( HWND parentHandle );

	void Show( int cmdShow );

	HWND getHandle() const;

	unsigned int getHeight() const;
	bool changeHeight( unsigned int countOfStrings );

	void setResult();
	bool isResult() const;
	HWND getHandleOfResult() const;
	unsigned int getHeightOfResult() const;
	std::wstring getResultText() const;

	std::wstring getText() const;

	friend bool operator== ( const CellWindow& left, const CellWindow& right );
private:

	HWND handleCellWindow;
	unsigned int height;
	unsigned int countOfStrings;

	CellResult result;

	void init();
};
