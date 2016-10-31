#include "stdafx.h"

#include "YaPyN_Editor.h"

int WINAPI wWinMain( HINSTANCE instance, HINSTANCE prevInstance, LPWSTR commandLine, int cmdShow )
{
	UNREFERENCED_PARAMETER( instance );
	UNREFERENCED_PARAMETER( commandLine );
	UNREFERENCED_PARAMETER( prevInstance );

	setlocale( LC_ALL, "Russian" );

	if( !YaPyN_Editor::RegisterClass() ) {
		return -1;
	}
	YaPyN_Editor window;

	if( !window.Create() ) {
		return -1;
	}

	window.Show( cmdShow );
	MSG message;
	BOOL getMessageResult = 0;
	auto acceleratorTable = LoadAccelerators( instance, MAKEINTRESOURCE( IDR_ACCELERATOR1 ) );
	while( (getMessageResult = ::GetMessage( &message, 0, 0, 0 )) != 0 ) {
		if( getMessageResult == -1 ) {
			return -1;
		}
		if( !TranslateAccelerator( window.GetHandle(), acceleratorTable, &message ) ) {
			::TranslateMessage( &message );
			::DispatchMessage( &message );
		}
	}
	::DestroyAcceleratorTable( acceleratorTable );
	return 0;
}
