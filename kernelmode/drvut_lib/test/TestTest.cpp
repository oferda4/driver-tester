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

TEST(TestsManagerTest, AddDifferentNames) {
    TestsManager::destroy();
    auto& manager = TestsManager::instance();
    auto arbitraryTestMethod = []() -> NTSTATUS { return 0; };
    
    ASSERT_NO_THROW(manager.add(std::unique_ptr<::drvut::internal::Test>(
        new RegularTest(arbitraryTestMethod)), "test0"));
    ASSERT_NO_THROW(manager.add(std::unique_ptr<::drvut::internal::Test>(
        new RegularTest(arbitraryTestMethod)), "test1"));
    ASSERT_NO_THROW(manager.add(std::unique_ptr<::drvut::internal::Test>(
        new RegularTest(arbitraryTestMethod)), "test2"));

    const auto tests = manager.list();
    ASSERT_EQ(tests.at(0).name, ::std::string("test0"));
    ASSERT_EQ(tests.at(1).name, ::std::string("test1"));
    ASSERT_EQ(tests.at(2).name, ::std::string("test2"));
}

TEST(TestsManagerTest, RunCorrectTest) {
    TestsManager::destroy();
    auto& manager = TestsManager::instance();
    const NTSTATUS arbitraryResultStatus = 1234;

    uint32_t shouldNotRunCallCount = 0;
    uint32_t shouldRunCallCount = 0;
    auto shouldNotRunMethod = [&shouldNotRunCallCount]() -> NTSTATUS { 
        shouldNotRunCallCount++; 
        return arbitraryResultStatus; 
    };
    auto shouldRunMethod = [&shouldRunCallCount]() -> NTSTATUS { 
        shouldRunCallCount++;
        return arbitraryResultStatus; 
    };

    ASSERT_NO_THROW(manager.add(std::unique_ptr<::drvut::internal::Test>(
        new RegularTest(shouldNotRunMethod)), "should not run"));
    ASSERT_NO_THROW(manager.add(std::unique_ptr<::drvut::internal::Test>(
        new RegularTest(shouldNotRunMethod)), "should not run2"));
    ASSERT_NO_THROW(manager.add(std::unique_ptr<::drvut::internal::Test>(
        new RegularTest(shouldRunMethod)), "should run"));

    const auto result = manager.run(manager.list().at(2).id);
    ASSERT_EQ(arbitraryResultStatus, static_cast<NTSTATUS>(result.status));
    ASSERT_EQ(shouldNotRunCallCount, 0);
    ASSERT_EQ(shouldRunCallCount, 1);
}

TEST(TestsManagerTest, RunNonExistingTest) {
    TestsManager::destroy();
    ASSERT_ANY_THROW(TestsManager::instance().run(0));
}

}

namespace drvut {

TEST(TestSyntax, CreateRegularTest) {
    internal::TestsManager::destroy();
    const char arbitraryName[] = "Some Name";
    bool didRun = false;

    // test(arbitraryName, [&didRun]() {  }) {

//    }
}

}
