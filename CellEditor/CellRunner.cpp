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
		answer.append( answerBuilder( val ) );
	}
	return answer;
}

std::string CellRunner::answerBuilder( PyObject* val )
{
	std::string answer;
	if( PyLong_Check( val ) ) {
		answer.append( std::to_string( PyLong_AsLong( val ) ) );
	} else if( PyUnicode_Check( val ) ) {
		answer.append( std::string( "\'" ) );
		answer.append( std::string( PyUnicode_AsUTF8( val ) ) );
		answer.append( std::string( "\'" ) );
	} else if( PyList_Check( val ) ) {
		int listSize = PyList_Size( val );
		answer.append( std::string( "[" ) );
		for( int i = 0; i < listSize - 1; i++ ) {
			answer.append( answerBuilder( PyList_GetItem( val, i ) ) );
			answer.append( std::string( ", " ) );
		}
		answer.append( answerBuilder( PyList_GetItem( val, listSize - 1 ) ) );
		answer.append( std::string( "]" ) );
	} else if( PyDict_Check( val ) ) {
		PyObject* keys = PyDict_Keys( val );
		answer.append( std::string( "{" ) );
		for( int i = 0; i < PyList_Size( keys ); i++ ) {
			PyObject* key = PyList_GetItem( keys, i );
			PyObject* dictval = PyDict_GetItem( val, key );			
			answer.append( answerBuilder( key ) );			
			answer.append( " : " );
			answer.append( answerBuilder( dictval ) );
			if( i < PyList_Size( keys ) - 1 ) {
				answer.append( std::string( ", " ) );
			}
		}
		answer.append( std::string( "}" ) );
	} else {
		answer.append( std::string( "None" ) );
	}
	answer.append( " \n" );
	return answer;
}