#pragma once

#include <Python.h> // should be the first include

#include "PythonTaskQueue.h"

#include <future>
#include <memory>
#include <mutex>
#include <string>

#include "PythonCommands.h"

CPythonTaskQueue::~CPythonTaskQueue()
{
}

void CPythonTaskQueue::AddNewTask(
	const std::string& text,
	std::shared_ptr<IReturnResultCallback>& callback )
{

	std::lock_guard<std::mutex> lock( queueMutex );
	queue.emplace( text, callback, queueId );
	if( queue.size() == 1 ) {
		std::async( &CPythonTaskQueue::Run, this, queue.front() );
	}
}

void CPythonTaskQueue::Reset( PyObject* newCatcherOut, PyObject* newCatcherErr )
{
	std::lock_guard<std::mutex> lock( queueMutex );

	catcherOut = newCatcherOut;
	catcherErr = newCatcherErr;

	++queueId;

	std::queue<CPythonTask> empty;
	queue.swap( empty );
}

void CPythonTaskQueue::Run( const CPythonTask& task )
{
	if( task.queueId != this->queueId ) {
		//not relevant task
		return;
	}

	PyGILState_STATE gstate;
	gstate = PyGILState_Ensure();

	FlushPythonOutput();

	PyRun_SimpleString( task.text.c_str() );

	PyObject* output =
		PyObject_GetAttrString( catcherOut, PYTHON_CATCHER_DATA.c_str() );
	PyObject* errors =
		PyObject_GetAttrString( catcherErr, PYTHON_CATCHER_DATA.c_str() );

	std::string stringOutput = GetOutputFromPyObject( output );
	std::string stringErrors = GetOutputFromPyObject( errors );

	PyGILState_Release( gstate );

	if( task.queueId != this->queueId ) {
		//not relevant task
		return;
	}

	task.callback->ReturnResult( stringOutput, stringErrors );

	std::lock_guard<std::mutex> lock( queueMutex );
	if( queue.empty() ) {
		return;
	} else {
		queue.pop();
		if( !queue.empty() ) {
			std::async( &CPythonTaskQueue::Run, this, queue.front() );
		}
	}
}

void CPythonTaskQueue::FlushPythonOutput() const
{
	PyRun_SimpleString( CATCHER_FLUSH_OUTPUT.c_str() );
}

std::string CPythonTaskQueue::GetOutputFromPyObject( PyObject* output ) const
{
	if( PyUnicode_Check( output ) ) {
		PyObject* bytes = PyUnicode_AsEncodedString( output, "ASCII", "strict" ); // Owned reference
		if( bytes != NULL ) {
			std::string result = PyBytes_AS_STRING( bytes ); // Borrowed pointer
			result = strdup( result.c_str() );

			return result;
		} else {
			return GET_OUTPUT_ERROR_MESSAGE;
		}
	} else {
		return GET_OUTPUT_ERROR_MESSAGE;
	}
}
