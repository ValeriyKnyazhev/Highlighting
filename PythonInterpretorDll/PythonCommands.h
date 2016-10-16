#pragma once

#include <string>

/**
* Catcher out code
**/
const std::string CATCHER_OUT_CLASS_CODE =
"import sys\n\
class StdOutCatcher :\n\
	def __init__(self) :\n\
		self.data = ''\n\
	def write(self, stuff) :\n\
		self.data = self.data + stuff\n\
\n\
catcherOut = StdOutCatcher()\n\
sys.stdout = catcherOut\n";

/**
* Catcher err code
**/
const std::string CATCHER_ERR_CLASS_CODE =
"import sys\n\
class StdErrCatcher :\n\
	def __init__(self) :\n\
		self.data = ''\n\
	def write(self, stuff) :\n\
		self.data = self.data + stuff\n\
\n\
catcherErr = StdErrCatcher()\n\
sys.stderr = catcherErr\n";

/**
* Flush catcher output
**/
const std::string CATCHER_FLUSH_OUTPUT = "catcherOut.data = ''\ncatcherErr.data = ''";

const std::string PYTHON_MAIN = "__main__";

const std::string PYTHON_CATCHER_OUT = "catcherOut";
const std::string PYTHON_CATCHER_ERR = "catcherErr";

const std::string PYTHON_CATCHER_DATA = "data";
