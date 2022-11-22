#include <gtest/gtest.h>

#include "Test.h"

namespace drvut::internal {

TEST(RegulatTestTest, sanity) {
    uint32_t callCount = 0;
    const NTSTATUS arbitraryResultStatus = 101;

    const auto result = RegularTest([&callCount, &arbitraryResultStatus]() { 
        callCount++;
        return arbitraryResultStatus; }
    ).run();
    ASSERT_EQ(result.status, arbitraryResultStatus);
    ASSERT_EQ(callCount, 1);
}

TEST(TestsManagerTest, Functionality) {
    uint32_t callCounter = 0;
    ASSERT_EQ(TestsManager::instance().list().size(), 0);
}

}
