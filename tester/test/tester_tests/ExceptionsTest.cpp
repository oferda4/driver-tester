#include <gtest/gtest.h>

#include "tester/Exceptions.h"

using std::wstring;

TEST(Exceptions, ExceptionConstruction) {
	const wstring arbitraryExceptionMessage = L"arbitrary";
	const uint32_t arbitraryExceptionNum = 8;
	Exception myException(arbitraryExceptionMessage, arbitraryExceptionNum);
	ASSERT_EQ(arbitraryExceptionMessage, myException.viewMsg());
	ASSERT_EQ(arbitraryExceptionNum, myException.getNum());
}
