#include "stdafx.h"

#include "CellRunner.h"
#include <iostream>

CellRunner::CellRunner()
{
	Py_Initialize();
	mainModule = PyImport_AddModule( "__main__" );
	globalDictionary = PyModule_GetDict( mainModule );
	localDictionary = PyDict_New();
}

CellRunner::~CellRunner()
{
	Py_Finalize();
}

void CellRunner::Restart()
{
	Py_Finalize();
	Py_Initialize();
	mainModule = PyImport_AddModule( "__main__" );
	globalDictionary = PyModule_GetDict( mainModule );
	localDictionary = PyDict_New();
}

std::string CellRunner::RunCell( const char* str )
{
	std::string answer;
	localDictionary = PyDict_New();
	PyObject* result = PyRun_String( str, Py_file_input, globalDictionary, localDictionary );
	if( !result ) {
		Restart();
		return std::string( "Error: invalid input" );
	}
	PyDict_Update( globalDictionary, localDictionary );
	PyObject* keys = PyDict_Keys( localDictionary );

	for( int i = 0; i < PyList_Size( keys ); i++ ) {
		PyObject* key = PyList_GetItem( keys, i );
		PyObject* val = PyDict_GetItem( localDictionary, key );
		answer.append( std::string( PyUnicode_AsUTF8( key ) ) );
		answer.append( "=" );
		if( PyLong_Check( val ) ) {
			answer.append( std::to_string( PyLong_AsLong( val ) ) );
		} else if( PyUnicode_Check( val ) ) {
			answer.append( std::string("\"" ));
			answer.append( std::string( PyUnicode_AsUTF8( val ) ) );
			answer.append( std::string( "\"" ) );
		} else {
			answer.append( std::string( "None" ) );
		}
		answer.append( " \n" );
	}
	return answer;
}