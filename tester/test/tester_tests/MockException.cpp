#include "tester/Defs.h"
#include "MockException.h"

using std::wstring;

MockException::MockException(wstring msg) : Exception(std::move(msg), 0) {
    // Intentionally left blank
}
