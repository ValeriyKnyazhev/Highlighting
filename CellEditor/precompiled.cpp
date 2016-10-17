#include "precompiled.h"

void checkHandle(HWND handle)
{
	if (handle == 0) {
		MessageBox(handle, L"Error: handle is NULL", NULL, MB_OK);
	}
	assert(handle != 0);
}