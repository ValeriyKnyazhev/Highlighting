#pragma once
#include <Windows.h>

class PictureCell {
public:
	PictureCell();

	void Create( HWND parentHandle );
	void paint();
	void Show( int cmdShow );

	HWND getHandle() const;

	unsigned int getHeight() const;
	unsigned int getWidth() const;
	bool getExistence() const;
	void setExistence( bool existence );

	friend bool operator== ( const PictureCell& left, const PictureCell& right );

	static void checkHandle( const HWND handle );
private:
	LONG height, width;
	HWND handle;	
	bool isExist;	
};