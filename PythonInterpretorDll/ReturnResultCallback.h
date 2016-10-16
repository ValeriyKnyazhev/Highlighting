#pragma once

#include <string>

class IReturnResultCallback {
public:
	virtual ~IReturnResultCallback() {};

	virtual void ReturnResult( const std::string&, const std::string& ) = 0;
};
