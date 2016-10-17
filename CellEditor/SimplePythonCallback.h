#pragma once

#include <ReturnResultCallback.h>

#include <string>
#include <Windows.h>

class CSimplePythonCallback : public IReturnResultCallback {
public:	
	CSimplePythonCallback( HWND hwndShow );
	~CSimplePythonCallback();

	virtual void ReturnResult( const std::string& resultOutput,
		const std::string& resultErrors ) override;

private:	
	HWND hwndShow;
};
