#pragma once

#include <Python.h> // should be the first include

#include "PythonInterpreter.h"

#include <codecvt>
#include <locale>
#include <memory>
#include <strsafe.h>
#include <Windows.h>

#include "ReturnResultCallback.h"

void CPythonInterpretor::InitializePython()
{
	Py_Initialize();
	PyEval_InitThreads();

	PyObject* mainModule = PyImport_AddModule( PYTHON_MAIN.c_str() );
	PyRun_SimpleString( CATCHER_OUT_CLASS_CODE.c_str() );
	PyRun_SimpleString( CATCHER_ERR_CLASS_CODE.c_str() );

	PyObject* catcherOut =
		PyObject_GetAttrString( mainModule, PYTHON_CATCHER_OUT.c_str() );

	PyObject* catcherErr =
		PyObject_GetAttrString( mainModule, PYTHON_CATCHER_ERR.c_str() );

	queue.Reset( catcherOut, catcherErr );

	state = PyEval_SaveThread();
}

void CPythonInterpretor::FinalizePython()
{
	PyEval_RestoreThread( state );
	Py_Finalize();
}

void CPythonInterpretor::Reset()
{
	FinalizePython();
	InitializePython();
}

CPythonInterpretor::CPythonInterpretor()
{
	InitializePython();
}

CPythonInterpretor::~CPythonInterpretor()
{
	FinalizePython();
}

void CPythonInterpretor::Run(
	const std::string& text,
	std::shared_ptr<IReturnResultCallback> callback )
{

	queue.AddNewTask( text, callback );
}
