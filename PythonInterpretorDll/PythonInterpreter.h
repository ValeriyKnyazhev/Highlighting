#pragma once

#ifdef PYTHONINTERPRETORDLL_EXPORTS
#define PYTHONINTERPRETORDLL_API __declspec(dllexport) 
#else
#define PYTHONINTERPRETORDLL_API __declspec(dllimport) 
#endif

#include <exception>
#include <memory>
#include <string>

#include "PythonCommands.h"
#include "PythonTaskQueue.h"
#include "ReturnResultCallback.h"

class PYTHONINTERPRETORDLL_API CPythonInterpretor {
public:
	CPythonInterpretor();
	virtual ~CPythonInterpretor();

	/**
	* Run piece of code on Python
	**/
	void Run(
		const std::string& text,
		std::shared_ptr<IReturnResultCallback> callback);

	/**
	* Reset interpreter state
	**/
	void Reset();

private:
	PyThreadState* state;

	CPythonTaskQueue queue;

	void InitializePython();
	void FinalizePython();
};
