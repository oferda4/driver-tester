#include <gtest/gtest.h>

#include <string>

#include "Defs.h"
#include "Test.h"

namespace drvut::internal {

TEST(RegulatTestTest, Sanity) {
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

TEST(TestsManagerTest, AddRetainsUniqueness) {
    TestsManager::destroy();
    auto arbitraryTestMethod = []() -> NTSTATUS { return 0; };
    const uint32_t numberOfTestsToAdd = 1024;

    for (uint32_t i = 0; i < numberOfTestsToAdd; i++) {
        ASSERT_NO_THROW(TestsManager::instance()
            .add(std::unique_ptr<::drvut::internal::Test>(new RegularTest(arbitraryTestMethod)), "arbitrary"));
    }

    const auto tests = TestsManager::instance().list();
    // Not the most generic but the simplest way to check uniqueness is to assume the implementation detail
    for (uint32_t i = 0; i < tests.size(); i++) {
        ASSERT_EQ(tests.at(i).id, i);
    }
}

}
