#include "HandleTest.h"

#include <gtest/gtest.h>

using std::wstring;
using std::optional;

using testing::NiceMock;
using testing::Return;

constexpr MockHandleTraits::HandleType ARBITRARY_HANDLE_VALUE = 16;
static_assert(ARBITRARY_HANDLE_VALUE != MockHandleTraits::INVALID_VALUE);

std::optional<NiceMock<MockHandleTraits>> MockHandleTraits::currMock{};

TEST_F(HandleTest, ValidHandleCtor) {
    EXPECT_NO_THROW((MockHandle(ARBITRARY_HANDLE_VALUE)));
}

TEST_F(HandleTest, InvalidHandleCtor) {
    EXPECT_THROW((MockHandle(MockHandleTraits::INVALID_VALUE)), MockException);
}

TEST_F(HandleTest, HandleDtor) {
    optional<MockHandle> handle{ MockHandle(ARBITRARY_HANDLE_VALUE) };
    EXPECT_CALL(*MockHandleTraits::currMock, mockClose(ARBITRARY_HANDLE_VALUE))
        .WillOnce(Return(true));
    handle.reset();
}

TEST_F(HandleTest, HandleCast) {
    MockHandle handle(ARBITRARY_HANDLE_VALUE);
    EXPECT_EQ(handle, ARBITRARY_HANDLE_VALUE);
}

void HandleTest::SetUp() {
    MockHandleTraits::currMock.emplace();
}

void HandleTest::TearDown() {
    MockHandleTraits::currMock.reset();
}

bool MockHandleTraits::close(HandleType handle) {
    return currMock->mockClose(handle);
}

MockException::MockException(wstring msg) : 
    Exception(std::move(msg), 0) {
    // Intentionally left blank
}