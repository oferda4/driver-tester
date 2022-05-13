#include "HandleTest.h"

#include "MockHandle.h"

#include <gtest/gtest.h>

using std::optional;

using testing::NiceMock;
using testing::Return;
using testing::_;

static void assertMovedAndNewHandle(optional<MockHandle> movedHandle, optional<MockHandle> newHandle);

constexpr MockHandleTraits::HandleType ARBITRARY_HANDLE_VALUE = 16;
static_assert(ARBITRARY_HANDLE_VALUE != MockHandleTraits::INVALID_VALUE);

void HandleTest::SetUp() {
    MockHandleTraits::currMock.emplace();
}

void HandleTest::TearDown() {
    MockHandleTraits::currMock.reset();
}

TEST_F(HandleTest, ValidHandleCtor) {
    EXPECT_NO_THROW((MockHandle(ARBITRARY_HANDLE_VALUE)));
}

TEST_F(HandleTest, InvalidHandleCtor) {
    EXPECT_THROW((MockHandle(MockHandleTraits::INVALID_VALUE)), MockException);
}

TEST_F(HandleTest, Dtor) {
    optional<MockHandle> handle{ MockHandle(ARBITRARY_HANDLE_VALUE) };
    EXPECT_CALL(*MockHandleTraits::currMock, mockClose(ARBITRARY_HANDLE_VALUE))
        .WillOnce(Return(true));
    handle.reset();
}

TEST_F(HandleTest, Cast) {
    MockHandle handle(ARBITRARY_HANDLE_VALUE);
    EXPECT_EQ(handle, ARBITRARY_HANDLE_VALUE);
}

TEST_F(HandleTest, MoveCtor) {
    optional<MockHandle> handle = MockHandle(ARBITRARY_HANDLE_VALUE);
    optional<MockHandle> newHandle = MockHandle(std::move(*handle));
    assertMovedAndNewHandle(std::move(handle), std::move(newHandle));
}

TEST_F(HandleTest, MoveAssignment) {
    optional<MockHandle> handle = MockHandle(ARBITRARY_HANDLE_VALUE);
    optional<MockHandle> newHandle = std::move(*handle);
    assertMovedAndNewHandle(std::move(handle), std::move(newHandle));
}

void assertMovedAndNewHandle(optional<MockHandle> movedHandle, optional<MockHandle> newHandle) {
    EXPECT_EQ(*movedHandle, MockHandleTraits::INVALID_VALUE);
    EXPECT_EQ(*newHandle, ARBITRARY_HANDLE_VALUE);

    EXPECT_CALL(*MockHandleTraits::currMock, mockClose(_))
        .Times(0);
    movedHandle.reset();
    EXPECT_CALL(*MockHandleTraits::currMock, mockClose(ARBITRARY_HANDLE_VALUE))
        .WillOnce(Return(true));
    newHandle.reset();
}

TEST_F(HandleTest, NotCopyable) {
    static_assert(!std::is_copy_constructible<MockHandle>::value);
    static_assert(!std::is_copy_assignable<MockHandle>::value);
}
