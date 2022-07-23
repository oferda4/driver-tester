#include <gtest/gtest.h>

#include "tester/Safety.h"
#include "FakeException.h"
#include "MockTracer.h"

TEST(SafetyTest, TryExecuteThrowingFunc) {
    ASSERT_NO_THROW(Safety::tryExecute<MockTracer>([] { throw FakeException(); }));
}
