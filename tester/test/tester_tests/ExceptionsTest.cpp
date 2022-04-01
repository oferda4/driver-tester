#include <gtest/gtest.h>

#include "tester/Defs.h"
#include "tester/Exceptions.h"

using std::wstring;

static const wstring ARBITRARY_EXCEPTION_MESSAGE = L"arbitrary";
static const uint32_t ARBITRARY_EXCEPTION_NUM = 8;

TEST(Exceptions, ExceptionConstruction) {
	Exception myException(ARBITRARY_EXCEPTION_MESSAGE, ARBITRARY_EXCEPTION_NUM);
	EXPECT_EQ(ARBITRARY_EXCEPTION_MESSAGE, myException.viewMsg());
	EXPECT_EQ(ARBITRARY_EXCEPTION_NUM, myException.getNum());
}

TEST(Exceptions, WinAPIException) {
	// TODO: Use guard / mock
	const auto lastError = GetLastError();
	SetLastError(ARBITRARY_EXCEPTION_NUM);
	WinAPIException myException(ARBITRARY_EXCEPTION_MESSAGE);
	EXPECT_EQ(ARBITRARY_EXCEPTION_MESSAGE, myException.viewMsg());
	EXPECT_EQ(ARBITRARY_EXCEPTION_NUM, myException.getNum());
	SetLastError(lastError);

}
