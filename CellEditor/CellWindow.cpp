#include "stdafx.h"

#include "CellWindow.h"

// Временный размер окна текста.
const int temporarySize = 34;
// Временный размер одной строчки.
const int heightOfString = 16;

CellWindow::CellWindow()
{
	handleCellWindow = 0;
	height = temporarySize;
	countOfStrings = 0;
}

void CellWindow::Create( HWND parentHandle )
{
	CellResult::checkHandle( parentHandle );

	//can use ES_AUTOHSCROLL, if we want to move inside the cell only by using the pointer
	handleCellWindow = CreateWindowEx( 0,
		L"EDIT",
		0,
		WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE | WS_BORDER //| ES_AUTOHSCROLL
		| WS_HSCROLL,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		parentHandle,
		0,
		GetModuleHandle( 0 ),
		0 );

	//TODO: Add scrollbar, when the length of the text is larger than the length of the window
	ShowScrollBar( handleCellWindow, SB_HORZ, FALSE );

	CellResult::checkHandle( handleCellWindow );

	result.Create( parentHandle );
	init();
	SetFocus( handleCellWindow );
}

void CellWindow::Show( int cmdShow )
{
	ShowWindow( handleCellWindow, cmdShow );
}

HWND CellWindow::getHandle() const
{
	return handleCellWindow;
}

unsigned int CellWindow::getHeight() const
{
	return height;
}

bool CellWindow::changeHeight( unsigned int newCountOfStrings )
{
	bool changed = (countOfStrings != newCountOfStrings);
	countOfStrings = newCountOfStrings;
	height = temporarySize + countOfStrings * heightOfString;
	// Поправить
	return changed;
}

void CellWindow::setResult()
{
	result.setExistence( true );
}

bool CellWindow::isResult() const
{
	return result.getExistence();
}

HWND CellWindow::getHandleOfResult() const
{
	return result.getHandle();
}

std::wstring CellWindow::getResultText() const
{
	return result.getText();
}

unsigned int CellWindow::getHeightOfResult() const
{
	return result.getHeight();
}

std::wstring CellWindow::getText() const
{
	int length = SendMessage( handleCellWindow, WM_GETTEXTLENGTH, 0, 0 );
	length++;
	std::wstring text;
	text.resize( length );
	::GetWindowText( handleCellWindow, (LPWSTR)text.c_str(), length );
	return text;
}

bool operator== ( const CellWindow& left, const CellWindow& right )
{
	return left.getHandle() == right.getHandle();
}

void CellWindow::init()
{
	HMODULE module = ::GetModuleHandle( 0 );
	HRSRC resourseHandle = ::FindResource( module, MAKEINTRESOURCE( IDR_TEXT1 ), L"TEXT" );
	HGLOBAL handleData = ::LoadResource( module, resourseHandle );
	DWORD size = ::SizeofResource( module, resourseHandle );
	LPVOID data = LockResource( handleData );
	SetWindowText( handleCellWindow, reinterpret_cast<LPCWSTR>(data) );
}