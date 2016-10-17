#include "stdafx.h"

#include "CellResult.h"

const int heightOfString = 18;

CellResult::CellResult()
{
	handleCellResult = 0;
	height = heightOfString;
	countOfStrings = 0;
	isExist = false;
}

void CellResult::Create( HWND parentHandle )
{
	checkHandle( parentHandle );

	//can use ES_AUTOHSCROLL, if we want to move inside the cell only by using the pointer
	handleCellResult = CreateWindowEx( 0,
		L"EDIT",
		0,
		WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE | WS_BORDER | ES_READONLY | ES_AUTOHSCROLL | WS_HSCROLL,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		parentHandle,
		0,
		GetModuleHandle( 0 ),
		0 );

	//TODO: Add scrollbar, when the length of the text is larger than the length of the window
	ShowScrollBar( handleCellResult, SB_HORZ, FALSE );
	EnableScrollBar( handleCellResult, SB_HORZ, ESB_DISABLE_RIGHT );

	checkHandle( handleCellResult );

	init();
	SetFocus( handleCellResult );
}

void CellResult::Show( int cmdShow )
{
	ShowWindow( handleCellResult, cmdShow );
}

HWND CellResult::getHandle() const
{
	return handleCellResult;
}

unsigned int CellResult::getHeight() const
{
	return height;
}

bool CellResult::changeHeight( unsigned int newCountOfStrings )
{
	bool changed = (countOfStrings != newCountOfStrings);
	countOfStrings = ((newCountOfStrings == 0) ? 1 : newCountOfStrings) + 1;
	height = countOfStrings * heightOfString;
	// Поправить
	return changed;
}

bool CellResult::getExistence() const
{
	return isExist;
}

void CellResult::setExistence( bool existence )
{
	isExist = existence;
}

std::wstring CellResult::getText() const
{
	int length = SendMessage( handleCellResult, WM_GETTEXTLENGTH, 0, 0 );
	length++;
	std::wstring text;
	text.resize( length );
	::GetWindowText( handleCellResult, (LPWSTR)text.c_str(), length );
	return text;
}

void CellResult::checkHandle( const HWND handle )
{
	if( handle == 0 ) {
		MessageBox( handle, L"Error: handle is NULL", NULL, MB_OK );
	}
	assert( handle != 0 );
}

bool operator== ( const CellResult& left, const CellResult& right )
{
	return left.getHandle() == right.getHandle();
}

void CellResult::init()
{
	HMODULE module = ::GetModuleHandle( 0 );
	HRSRC resourseHandle = ::FindResource( module, MAKEINTRESOURCE( IDR_TEXT1 ), L"TEXT" );
	HGLOBAL handleData = ::LoadResource( module, resourseHandle );
	// TODO warning
	// DWORD size = ::SizeofResource( module, resourseHandle );
	LPVOID data = LockResource( handleData );
	SetWindowText( handleCellResult, reinterpret_cast<LPCWSTR>(data) );
}