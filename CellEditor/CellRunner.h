#pragma once

#include <Python.h>
#include <string>

class CellRunner {
public:
	CellRunner();
	~CellRunner();
	std::string RunCell( const char* str );
	void Restart();
private:
	std::string answerBuilder( PyObject* val );
	PyObject* mainModule;
	PyObject* globalDictionary;
	PyObject* localDictionary;
};