#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "IoctlHandler.h"
#include "Ioctl.h"

namespace drvut::internal {

namespace {
std::unique_ptr<Test> createArbitraryTest();
}

TEST(IoctlHandlerTest, InvalidCode) {
    const uint32_t arbitraryInvalidCode = -1;
    TestsManager::destroy();
    ASSERT_EQ(IoctlHandler::handle(TestsManager::instance(), 
                                   arbitraryInvalidCode, 
                                   BufferView(nullptr, 0), 
                                   BufferView(nullptr, 0)),
              STATUS_INVALID_PARAMETER_2);
}

TEST(IoctlHandlerTest, GetNumberOfTests_Sanity) {
    TestsManager::destroy();
    Ioctl::GetNumberOfTestsInput input{};
    uint64_t output = 0;
    
    const uint64_t numberOfTestsToAdd = 10;
    uint64_t index = 0;

    do {
        ASSERT_EQ(IoctlHandler::handle(TestsManager::instance(),
                      Ioctl::GET_NUMBER_OF_TESTS,
                      BufferView(&input, sizeof(Ioctl::GetNumberOfTestsInput)),
                      BufferView(&output, sizeof(output))),
            STATUS_SUCCESS);
        ASSERT_EQ(output, index);

        TestsManager::instance().add(createArbitraryTest(), "");
        index++;
    } while (index < numberOfTestsToAdd);
}

TEST(IoctlHandlerTest, GetNumberOfTests_BadInput) {
    TestsManager::destroy();
    ASSERT_EQ(IoctlHandler::handle(TestsManager::instance(),
                  Ioctl::GET_NUMBER_OF_TESTS,
                  BufferView(nullptr, sizeof(Ioctl::GetNumberOfTestsInput) + 1),
                  BufferView(nullptr, 0)),
        STATUS_INVALID_PARAMETER_3);
    ASSERT_EQ(IoctlHandler::handle(TestsManager::instance(),
                  Ioctl::GET_NUMBER_OF_TESTS,
                  BufferView(nullptr, sizeof(Ioctl::GetNumberOfTestsInput) - 1),
                  BufferView(nullptr, 0)),
        STATUS_INVALID_PARAMETER_3);
}

TEST(IoctlHandlerTest, GetNumberOfTests_BadOutput) {
    TestsManager::destroy();
    Ioctl::GetNumberOfTestsInput input{};
    ASSERT_EQ(IoctlHandler::handle(TestsManager::instance(),
                  Ioctl::GET_NUMBER_OF_TESTS,
                  BufferView(&input, sizeof(input)),
                  BufferView(nullptr, sizeof(Ioctl::GetNumberOfTestsOutput) + 1)),
        STATUS_INVALID_PARAMETER_4);
    ASSERT_EQ(IoctlHandler::handle(TestsManager::instance(),
                  Ioctl::GET_NUMBER_OF_TESTS,
                  BufferView(&input, sizeof(input)),
                  BufferView(nullptr, sizeof(Ioctl::GetNumberOfTestsOutput) - 1)),
        STATUS_INVALID_PARAMETER_4);
}

TEST(IoctlHandlerTest, ListTests_Sanity) {
    TestsManager::destroy();
    Ioctl::ListTestsInput input{};
    
    // the forcing of using only uint8_t is merely for simplifying giving a string name
    const uint8_t numberOfTestsToAdd = 10;
    uint8_t index = 0;
    char indexName[1];

    do {
        Array<Ioctl::TestInfo> output(index);
        ASSERT_EQ(IoctlHandler::handle(TestsManager::instance(),
                      Ioctl::LIST_TESTS,
                      BufferView(&input, sizeof(Ioctl::GetNumberOfTestsInput)),
                      BufferView(
                          output.size() > 0 ? ::std::addressof(output.at(0)) : nullptr, 
                          output.size() * sizeof(Ioctl::TestInfo))),
            STATUS_SUCCESS);

        const auto resultList = TestsManager::instance().list();
        ASSERT_EQ(resultList.size(), index);
        for (uint8_t secondaryIndex = 0; secondaryIndex < index; secondaryIndex++) {
            ASSERT_EQ(resultList.at(secondaryIndex).id, secondaryIndex);
            ASSERT_EQ(resultList.at(secondaryIndex).name[0], secondaryIndex);
            ASSERT_EQ(resultList.at(secondaryIndex).name[1], 0);
        }
        
        indexName[0] = index;
        TestsManager::instance().add(createArbitraryTest(), indexName);
        index++;
    } while (index < numberOfTestsToAdd);
}

TEST(IoctlHandlerTest, ListTests_BadInput) {
    TestsManager::destroy();
    ASSERT_EQ(IoctlHandler::handle(TestsManager::instance(),
                  Ioctl::LIST_TESTS,
                  BufferView(nullptr, sizeof(Ioctl::ListTestsInput) + 1),
                  BufferView(nullptr, 0)),
        STATUS_INVALID_PARAMETER_3);
    ASSERT_EQ(IoctlHandler::handle(TestsManager::instance(),
                  Ioctl::LIST_TESTS,
                  BufferView(nullptr, sizeof(Ioctl::ListTestsInput) - 1),
                  BufferView(nullptr, 0)),
        STATUS_INVALID_PARAMETER_3);
}

TEST(IoctlHandlerTest, ListTests_BadOutput) {
    TestsManager::destroy();
    Ioctl::ListTestsInput input{};
    
    TestsManager::instance().add(createArbitraryTest(), "Arbitrary Test");
    const uint64_t numberOfTests = 1;

    ASSERT_EQ(IoctlHandler::handle(TestsManager::instance(),
                  Ioctl::LIST_TESTS,
                  BufferView(&input, sizeof(input)),
                  BufferView(nullptr, sizeof(Ioctl::TestInfo) * (numberOfTests + 1))),
        STATUS_INVALID_PARAMETER_4);
    ASSERT_EQ(IoctlHandler::handle(TestsManager::instance(),
                  Ioctl::LIST_TESTS,
                  BufferView(&input, sizeof(input)),
                  BufferView(nullptr, sizeof(Ioctl::TestInfo) * (numberOfTests - 1))),
        STATUS_INVALID_PARAMETER_4);
}

TEST(IoctlHandlerTest, RunTest_Sanity) {
    TestsManager::destroy();
    auto& manager = TestsManager::instance();
    const NTSTATUS arbitraryResultStatus = 1461;

    uint32_t expectNotCalledTestCallCount = 0;
    std::unique_ptr<drvut::internal::Test> expectNotCalledTest(
        new RegularTest([&expectNotCalledTestCallCount, &arbitraryResultStatus]() { 
            expectNotCalledTestCallCount++; 
            return arbitraryResultStatus;
        }));
    uint32_t expectCalledTestCallCount = 0;
    std::unique_ptr<drvut::internal::Test> expectCalledTest(
        new RegularTest([&expectCalledTestCallCount, &arbitraryResultStatus]() { 
            expectCalledTestCallCount++; 
            return arbitraryResultStatus;
        }));

    manager.add(std::move(expectNotCalledTest), "ExpectNotCalled");
    manager.add(std::move(expectCalledTest), "ExpectCalled");

    auto tests = manager.list();
    ASSERT_EQ(tests.size(), 2);

    Ioctl::RunTestInput input = { .testId = tests.at(1).id };
    Ioctl::RunTestOutput output = {0};
    ASSERT_EQ(IoctlHandler::handle(manager, 
                                   Ioctl::RUN_TEST, 
                                   BufferView(&input, sizeof(input)), 
                                   BufferView(&output, sizeof(output))),
              STATUS_SUCCESS);

    ASSERT_EQ(output.result, arbitraryResultStatus);
    ASSERT_EQ(expectNotCalledTestCallCount, 0);
    ASSERT_EQ(expectCalledTestCallCount, 1);
}

TEST(IoctlHandlerTest, RunTest_BadInput) {
    TestsManager::destroy();
    ASSERT_EQ(IoctlHandler::handle(TestsManager::instance(),
                  Ioctl::RUN_TEST,
                  BufferView(nullptr, sizeof(Ioctl::RunTestInput) + 1),
                  BufferView(nullptr, 0)),
        STATUS_INVALID_PARAMETER_3);
    ASSERT_EQ(IoctlHandler::handle(TestsManager::instance(),
                  Ioctl::RUN_TEST,
                  BufferView(nullptr, sizeof(Ioctl::RunTestInput) - 1),
                  BufferView(nullptr, 0)),
        STATUS_INVALID_PARAMETER_3);
}

TEST(IoctlHandlerTest, RunTest_BadOutput) {
    TestsManager::destroy();
    Ioctl::RunTestInput input{};

    ASSERT_EQ(IoctlHandler::handle(TestsManager::instance(),
                  Ioctl::RUN_TEST,
                  BufferView(&input, sizeof(input)),
                  BufferView(nullptr, sizeof(Ioctl::RunTestOutput) + 1)),
        STATUS_INVALID_PARAMETER_4);
    ASSERT_EQ(IoctlHandler::handle(TestsManager::instance(),
                  Ioctl::RUN_TEST,
                  BufferView(&input, sizeof(input)),
                  BufferView(nullptr, sizeof(Ioctl::RunTestOutput) - 1)),
        STATUS_INVALID_PARAMETER_4);
}

TEST(IoctlHandlerTest, RunTest_UnknownTest) {
    TestsManager::destroy();
    // we won't add  any test so any id will cause the failure
    Ioctl::RunTestInput input{ .testId = 5 };
    Ioctl::RunTestOutput output = { 0 };

    ASSERT_ANY_THROW(IoctlHandler::handle(TestsManager::instance(),
                     Ioctl::RUN_TEST,
                     BufferView(&input, sizeof(input)),
                     BufferView(&output, sizeof(output))));
}

namespace {

std::unique_ptr<Test> createArbitraryTest() {
    return std::unique_ptr<Test>(new RegularTest());
}

}
}