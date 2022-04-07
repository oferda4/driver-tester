#include <gtest/gtest.h>

#include "HandleTest.h"

using std::wstring;

static MockHandle createValidHandle();

TEST(HandleTest, ValidHandleCtor) {
    EXPECT_NO_THROW(createValidHandle);
}

MockHandle createValidHandle() {
    constexpr MockHandleTraits::HandleType ARBITRARY_HANDLE_VALUE = 16;
    static_assert(ARBITRARY_HANDLE_VALUE != MockHandleTraits::INVALID_VALUE);
    return MockHandle(ARBITRARY_HANDLE_VALUE);
}

TEST(HandleTest, InvalidHandleCtor) {
    EXPECT_THROW((MockHandle(MockHandleTraits::INVALID_VALUE)), MockException);
}

bool MockHandleTraits::close(HandleType handle) {
    return true;
}

MockException::MockException(wstring msg) : 
    Exception(std::move(msg), 0) {
    // Intentionally left blank
}