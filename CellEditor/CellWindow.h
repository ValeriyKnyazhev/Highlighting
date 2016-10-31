#pragma once
#include "CellResult.h"
#include "PictureCell.h"

class CellWindow {
public:

	CellWindow();

	void Create( HWND parentHandle );
	void CreatePictureWindow();
	void Show( int cmdShow );

	HWND getHandle() const;

	unsigned int getHeight() const;
	bool changeHeight( unsigned int countOfStrings );

	void setResult();
	bool isResult() const;
	bool isPicture() const;
	HWND getHandleOfResult() const;
	HWND getHandleOfPicture() const;
	unsigned int getHeightOfResult() const;
	unsigned int getHeightOfPicture() const;
	unsigned int getWidthofPicture() const;
	void paintPicture();
	std::wstring getResultText() const;

	std::wstring getText() const;

	friend bool operator== ( const CellWindow& left, const CellWindow& right );
private:

	HWND handleCellWindow;
	unsigned int height;
	unsigned int countOfStrings;

	CellResult result;
	PictureCell ptCell;
	void init();
};
