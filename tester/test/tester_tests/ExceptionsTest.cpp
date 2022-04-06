#include "ExceptionsTest.h"

#include <gtest/gtest.h>

#include "tester/Defs.h"
#include "tester/Exceptions.h"

using std::wstring;
using testing::Return;

static const wstring ARBITRARY_EXCEPTION_MESSAGE = L"arbitrary";
static const uint32_t ARBITRARY_EXCEPTION_NUM = 8;

TEST(Exceptions, ExceptionConstruction) {
    Exception myException(ARBITRARY_EXCEPTION_MESSAGE, ARBITRARY_EXCEPTION_NUM);
    EXPECT_EQ(ARBITRARY_EXCEPTION_MESSAGE, myException.viewMsg());
    EXPECT_EQ(ARBITRARY_EXCEPTION_NUM, myException.getNum());
}

TEST(Exceptions, WinAPIException) {
    MockLastErrorAPIImpl mock;
    EXPECT_CALL(mock, getLastError()).WillOnce(Return(ARBITRARY_EXCEPTION_NUM));
    WinAPIException<MockLastErrorAPIImpl> myException(ARBITRARY_EXCEPTION_MESSAGE, mock);
    EXPECT_EQ(ARBITRARY_EXCEPTION_MESSAGE, myException.viewMsg());
    EXPECT_EQ(ARBITRARY_EXCEPTION_NUM, myException.getNum());
}
