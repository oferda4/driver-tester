#include "Exceptions.h"

#include "Defs.h"

using std::string;
using std::exception;

Win32Exception::Win32Exception(const string& message) :
	exception(message.c_str(), GetLastError()) {
	// Left blank intentionally
}
