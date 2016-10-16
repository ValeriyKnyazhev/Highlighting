#pragma once

#include <Python.h> // should be the first include

#include <exception>
#include <memory>
#include <mutex>
#include <string>
#include <queue>

#include "ReturnResultCallback.h"

struct CPythonTask {
	CPythonTask(
		const std::string& text_,
		std::shared_ptr<IReturnResultCallback>& callback_,
		int queueId_ )
		: text( text_ )
		, callback( callback_ )
		, queueId( queueId_ )
	{
	}

	std::string text;
	std::shared_ptr<IReturnResultCallback> callback;
	int queueId;
};

class CPythonTaskQueue {
public:
	CPythonTaskQueue()
		: queueId( 0 )
	{
	}
	~CPythonTaskQueue();

	// Create new task and run it if nothing is running now
	void AddNewTask(
		const std::string& text,
		std::shared_ptr<IReturnResultCallback>& callback );

	// Reset queue
	void Reset( PyObject* newCatcherOut, PyObject* newCatcherErr );
private:
	std::queue<CPythonTask> queue;
	std::mutex queueMutex;
	// Helps to get output from python
	PyObject* catcherOut;
	PyObject* catcherErr;
	// Helps to manage tasks
	volatile int queueId;

	// Run task and start next one if it's available
	void Run( const CPythonTask& task );

	void FlushPythonOutput() const;

	const std::string GET_OUTPUT_ERROR_MESSAGE = "Output error";

	std::string GetOutputFromPyObject( PyObject* output ) const;
};
