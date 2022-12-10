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
        Array<TestInfo> output(index);
        ASSERT_EQ(IoctlHandler::handle(TestsManager::instance(),
                      Ioctl::LIST_TESTS,
                      BufferView(&input, sizeof(Ioctl::GetNumberOfTestsInput)),
                      BufferView(
                          output.size() > 0 ? ::std::addressof(output.at(0)) : nullptr, 
                          output.size() * sizeof(TestInfo))),
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
                  BufferView(nullptr, sizeof(TestInfo) * (numberOfTests + 1))),
        STATUS_INVALID_PARAMETER_4);
    ASSERT_EQ(IoctlHandler::handle(TestsManager::instance(),
                  Ioctl::LIST_TESTS,
                  BufferView(&input, sizeof(input)),
                  BufferView(nullptr, sizeof(TestInfo) * (numberOfTests - 1))),
        STATUS_INVALID_PARAMETER_4);
}

namespace {

std::unique_ptr<Test> createArbitraryTest() {
    return std::unique_ptr<Test>(new RegularTest());
}

}
}