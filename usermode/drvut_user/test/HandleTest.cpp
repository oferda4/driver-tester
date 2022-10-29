#include "Handle.h"

#include "MockHandle.h"

using testing::_;

namespace {
constexpr MoveableMockHandleTraits::Type NOT_INTERESTING_HANDLE_VALUE = 0;

void assertGuardInnerValue(HandleGuard<MoveableMockHandleTraits>& guard, MoveableMockHandleTraits::Type value);
void assertInvalidWhenGettingInnerValue(HandleGuard<MoveableMockHandleTraits>& guard);
}

TEST(HandleGuardTest, GuardOnDtor) {
    const MoveableMockHandleTraits::Type arbitraryHandleValue = 125;
    MoveableMockHandleTraits traits;
    EXPECT_CALL(traits.getMock(), close(arbitraryHandleValue)).Times(1);
    HandleGuard<MoveableMockHandleTraits> guard(std::move(traits), arbitraryHandleValue);
}

TEST(HandleGuardTest, GetInnerValue) {
    const MoveableMockHandleTraits::Type arbitraryHandleValue = 1010;
    HandleGuard<MoveableMockHandleTraits> guard(arbitraryHandleValue);

    assertGuardInnerValue(guard, arbitraryHandleValue);
}

TEST(HandleGuardTest, MoveCtor) {
    const MoveableMockHandleTraits::Type arbitraryHandleValue = 8;
    HandleGuard<MoveableMockHandleTraits> movedGuard(arbitraryHandleValue);
    HandleGuard<MoveableMockHandleTraits> guard(std::move(movedGuard));

    assertGuardInnerValue(guard, arbitraryHandleValue);
}

TEST(HandleGuardTest, MoveAssignment) {
    const MoveableMockHandleTraits::Type arbitraryHandleValue = 17;
    const MoveableMockHandleTraits::Type arbitraryDifferentHandleValue = 101;
    static_assert(arbitraryHandleValue != arbitraryDifferentHandleValue);

    HandleGuard<MoveableMockHandleTraits> movedGuard(arbitraryHandleValue);
    HandleGuard<MoveableMockHandleTraits> guard(arbitraryDifferentHandleValue);
    guard = std::move(movedGuard);

    assertGuardInnerValue(guard, arbitraryHandleValue);
}

TEST(HandleGuardTest, InvalidateAfterMoveCtor) {
    MoveableMockHandleTraits traits;
    EXPECT_CALL(traits.getMock(), close(_)).Times(1);
    HandleGuard<MoveableMockHandleTraits> movedGuard(std::move(traits), NOT_INTERESTING_HANDLE_VALUE);
    HandleGuard<MoveableMockHandleTraits> ignored(std::move(movedGuard));

    assertInvalidWhenGettingInnerValue(movedGuard);
}

TEST(HandleGuardTest, InvalidateAfterMoveAssignment) {
    MoveableMockHandleTraits traits;
    EXPECT_CALL(traits.getMock(), close(_)).Times(1);
    HandleGuard<MoveableMockHandleTraits> movedGuard(std::move(traits), NOT_INTERESTING_HANDLE_VALUE);
    HandleGuard<MoveableMockHandleTraits> ignored(NOT_INTERESTING_HANDLE_VALUE);
    ignored = std::move(movedGuard);

    assertInvalidWhenGettingInnerValue(movedGuard);
}

namespace {
void assertGuardInnerValue(HandleGuard<MoveableMockHandleTraits>& guard, MoveableMockHandleTraits::Type value) {
    ASSERT_EQ(value, *guard);
    ASSERT_EQ(value, *(static_cast<const HandleGuard<MoveableMockHandleTraits>&>(guard)));
}

void assertInvalidWhenGettingInnerValue(HandleGuard<MoveableMockHandleTraits>& guard) {
    ASSERT_THROW(*guard, InvalidHandle);
    ASSERT_THROW(*(static_cast<const HandleGuard<MoveableMockHandleTraits>&>(guard)), InvalidHandle);
}
}
