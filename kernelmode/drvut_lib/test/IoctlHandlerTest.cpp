#include <gtest/gtest.h>

#include "IoctlHandler.h"
#include "Ioctl.h"

namespace drvut::internal {

TEST(IoctlHandlerTest, InvalidCode) {
    const uint32_t arbitraryInvalidCode = -1;
    TestsManager::destroy();
    ASSERT_EQ(IoctlHandler::handle(TestsManager::instance(), 
                                   arbitraryInvalidCode, 
                                   BufferView(nullptr, 0), 
                                   BufferView(nullptr, 0)),
              STATUS_INVALID_PARAMETER_2);
}

/*
TEST(IoctlHandlerTest, ListTests_Sanity) {
    TestsManager::destroy();
    Ioctl::ListTestsInput input{};
    uint64_t resultNumberOfTests = 0;
    uint64_t expectedNumberOfTests = 0;

    TestsManager::instance().add

    ASSERT_EQ(IoctlHandler::handle(TestsManager::instance(),
                  Ioctl::LIST_TESTS,
                  BufferView(&input, sizeof(input)),
                  BufferView(&numberOfTests, sizeof(numberOfTests))),
        STATUS_SUCCESS);

    Array<byte> outputBuffer(sizeof(Ioctl::ListTestsOutput) + resultNumberOfTests * sizeof(TestInfo));
    Ioctl::ListTestsOutput* output = ::std::addressof(outputBuffer.at(0));

    ASSERT_EQ(output->resultNumberOfTests);
}
*/

TEST(IoctlHandlerTest, ListTests_NoTests) {
    TestsManager::destroy();
    Ioctl::ListTestsInput input{};
    uint64_t numberOfTests = 0;
    
    ASSERT_EQ(IoctlHandler::handle(TestsManager::instance(),
                  Ioctl::LIST_TESTS,
                  BufferView(&input, sizeof(input)),
                  BufferView(&numberOfTests, sizeof(numberOfTests))),
        STATUS_SUCCESS);
    ASSERT_EQ(numberOfTests, 0);
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
    ASSERT_EQ(IoctlHandler::handle(TestsManager::instance(),
                  Ioctl::LIST_TESTS,
                  BufferView(&input, sizeof(input)),
                  BufferView(nullptr, sizeof(Ioctl::ListTestsOutput::numberOfTests)-1)),
        STATUS_INVALID_PARAMETER_4);
}

}