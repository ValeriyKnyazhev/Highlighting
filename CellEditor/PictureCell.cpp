#include "stdafx.h"
#include "PictureCell.h"

void PictureCell::paint()
{
	PAINTSTRUCT paintStruct;
	HDC hdc = ::BeginPaint( handle, &paintStruct );			
	if( isExist ) {
		HBITMAP  hBmps = (HBITMAP)LoadImage( GetModuleHandle( 0 ), fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
		RECT Rect;
		BITMAP Bitmap;
		GetObject( hBmps, sizeof( BITMAP ), &Bitmap );
		width = Bitmap.bmWidth;
		height = Bitmap.bmHeight;
		HDC hCompatibleDC = CreateCompatibleDC( hdc );
		HANDLE hOldBitmap = SelectObject( hCompatibleDC, hBmps );
		GetClientRect( handle, &Rect );
		StretchBlt( hdc, 0, 0, Rect.right, Rect.bottom, hCompatibleDC, 0, 0, Bitmap.bmWidth,
			Bitmap.bmHeight, SRCCOPY );
		SelectObject( hCompatibleDC, hOldBitmap );
		DeleteObject( hBmps );
		DeleteDC( hCompatibleDC );
	}	
	EndPaint( handle, &paintStruct );	
}

const int heightOfString = 18;

PictureCell::PictureCell()
{
	handle = 0;
	height = heightOfString;	
	isExist = false;
}

void PictureCell::Create( HWND parentHandle )
{	
	handle = CreateWindowEx( 0,
		L"STATIC",
		0,
		WS_CHILD | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		parentHandle,
		0,
		GetModuleHandle( 0 ),
		0 );
	checkHandle( handle );	
	SetFocus( handle );		
}

void PictureCell::Show( int cmdShow )
{
	ShowWindow( handle, cmdShow );
}

void PictureCell::LoadFile()
{
	OPENFILENAME openFileName = {};
	openFileName.lStructSize = sizeof( OPENFILENAME );
	openFileName.lpstrFile = fileName;
	openFileName.hwndOwner = handle;
	openFileName.lpstrFile[0] = '\0';
	openFileName.nMaxFile = sizeof( fileName );
	int result = GetOpenFileName( &openFileName );	
	if ( result ) {
		setExistence( true );
	}
}

HWND PictureCell::getHandle() const
{
	return handle;
}

unsigned int PictureCell::getHeight() const
{
	return height;
}

unsigned int PictureCell::getWidth() const
{
	return width;
}
bool PictureCell::getExistence() const
{
	return isExist;
}

void PictureCell::setExistence( bool existence )
{
	isExist = existence;
}

void PictureCell::checkHandle( const HWND handle )
{
	if( handle == 0 ) {
		MessageBox( handle, L"Error: handle is NULL", NULL, MB_OK );
	}
	assert( handle != 0 );
}

bool operator== ( const PictureCell& left, const PictureCell& right )
{
	return left.getHandle() == right.getHandle();
}
