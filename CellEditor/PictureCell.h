#pragma once
#include <Windows.h>

#define FileNameSize 256
class PictureCell {
public:
	PictureCell();

	void Create( HWND parentHandle );
	void paint();
	void Show( int cmdShow );
	void LoadFile();
	HWND getHandle() const;

	unsigned int getHeight() const;
	unsigned int getWidth() const;
	bool getExistence() const;
	void setExistence( bool existence );

	friend bool operator== ( const PictureCell& left, const PictureCell& right );

	static void checkHandle( const HWND handle );
private:
	wchar_t fileName[FileNameSize];
	LONG height, width;
	HWND handle;	
	HANDLE hBitmap;
	bool isExist;	
};