#include <gtest/gtest.h>

#include <string>

#include "Defs.h"
#include "Test.h"

#include "MockFixture.h"

namespace drvut::internal {

TEST(RegulatTestTest, Sanity) {
    uint32_t callCount = 0;
    
    const auto result = RegularTest([&callCount]() {
                            callCount++;
                        }).run();
    ASSERT_TRUE(result.passed);
    ASSERT_EQ(callCount, 1);
}

TEST(RegulatTestTest, AssignOperator) {
    uint32_t callCount = 0;
    
    RegularTest test;
    test = [&callCount]() {
        callCount++;
    };
    const auto result = test.run();

    ASSERT_TRUE(result.passed);
    ASSERT_EQ(callCount, 1);
}

TEST(TestsManagerTest, AddRetainsUniqueness) {
    TestsManager::destroy();
    auto arbitraryTestMethod = []() {};
    const uint32_t numberOfTestsToAdd = 1024;

    for (uint32_t i = 0; i < numberOfTestsToAdd; i++) {
        ASSERT_NO_THROW(TestsManager::instance().add(
            std::unique_ptr<::drvut::internal::Test>(new RegularTest(arbitraryTestMethod)),
            "arbitrary"));
    }

    const auto tests = TestsManager::instance().list();
    // Not the most generic but the simplest way to check uniqueness is to
    // assume the implementation detail
    for (uint32_t i = 0; i < tests.size(); i++) {
        ASSERT_EQ(tests.at(i).id, i);
    }
}

TEST(TestsManagerTest, AddDifferentNames) {
    TestsManager::destroy();
    auto& manager = TestsManager::instance();
    auto arbitraryTestMethod = []() {};

    ASSERT_NO_THROW(manager.add(
        std::unique_ptr<::drvut::internal::Test>(new RegularTest(arbitraryTestMethod)), "test0"));
    ASSERT_NO_THROW(manager.add(
        std::unique_ptr<::drvut::internal::Test>(new RegularTest(arbitraryTestMethod)), "test1"));
    ASSERT_NO_THROW(manager.add(
        std::unique_ptr<::drvut::internal::Test>(new RegularTest(arbitraryTestMethod)), "test2"));

    const auto tests = manager.list();
    ASSERT_EQ(tests.at(0).name, ::std::string("test0"));
    ASSERT_EQ(tests.at(1).name, ::std::string("test1"));
    ASSERT_EQ(tests.at(2).name, ::std::string("test2"));
}

TEST(TestsManagerTest, RunCorrectTest) {
    TestsManager::destroy();
    auto& manager = TestsManager::instance();
    
    uint32_t shouldNotRunCallCount = 0;
    uint32_t shouldRunCallCount = 0;
    auto shouldNotRunMethod = [&shouldNotRunCallCount]() {
        shouldNotRunCallCount++;
    };
    auto shouldRunMethod = [&shouldRunCallCount]() {
        shouldRunCallCount++;
    };

    ASSERT_NO_THROW(
        manager.add(std::unique_ptr<::drvut::internal::Test>(new RegularTest(shouldNotRunMethod)),
                    "should not run"));
    ASSERT_NO_THROW(
        manager.add(std::unique_ptr<::drvut::internal::Test>(new RegularTest(shouldNotRunMethod)),
                    "should not run2"));
    ASSERT_NO_THROW(manager.add(
        std::unique_ptr<::drvut::internal::Test>(new RegularTest(shouldRunMethod)), "should run"));

    const auto result = manager.run(manager.list().at(2).id);
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
    auto& manager = internal::TestsManager::instance();

    const char arbitraryName[] = "Some Name";
    bool didRun = false;
    
    test(arbitraryName) = [&didRun]() {
        didRun = true;
    };

    auto tests = manager.list();
    ASSERT_EQ(tests.size(), 1);
    ASSERT_EQ(std::string(tests.at(0).name), std::string(arbitraryName));
    ASSERT_TRUE(manager.run(tests.at(0).id).passed);
    ASSERT_TRUE(didRun);
}

TEST(TestSyntax, TestWithFixture) {
    MockFixture::setupCallCount = 0;
    MockFixture::teardownCallCount = 0;

    internal::TestsManager::destroy();
    auto& manager = internal::TestsManager::instance();

    bool wasCalled = false;
    test("TestWithFixtures") = [&wasCalled](MockFixture& fixture1, MockFixture& fixture2) { 
        wasCalled = true;
        ASSERT_EQ(2, MockFixture::setupCallCount);
    };

    auto tests = manager.list();
    ASSERT_TRUE(manager.run(tests.at(0).id).passed);
    ASSERT_EQ(2, MockFixture::teardownCallCount);
}

TEST(TestSyntax, TestWithFailingSetup) {
    MockFixture::setupCallCount = 0;
    MockFixture::teardownCallCount = 0;

    internal::TestsManager::destroy();
    auto& manager = internal::TestsManager::instance();

    bool wasCalled = false;
    test("TestWithFailingFixture") = [&wasCalled](MockFixture& fixture1,
                                            FakeFailingOnSetupFixture& failingFixture, 
                                            MockFixture& fixture2) {
        GTEST_FAIL();
    };

    auto tests = manager.list();
    const auto result = manager.run(tests.at(0).id);
    ASSERT_FALSE(result.passed);
    ASSERT_EQ("failure in setup", std::string(result.msg));

    // the second should never be called
    ASSERT_EQ(1, MockFixture::setupCallCount);
    ASSERT_EQ(1, MockFixture::teardownCallCount);
}

}
