#include <gtest/gtest.h>

#include "RequestsHandler.h"

#include "MockFile.h"
#include "MockIoctlApi.h"

namespace {
const std::wstring FAKE_DEVICE_NAME = L"fake";

template <typename T>
void assertSameBufferAsObj(const T& obj, const Buffer& buffer);
}

TEST(RequestsHandlerTest, OpenFileOnConstruction) {
    MoveableMockFileCreationApi creationApi;

    EXPECT_CALL(creationApi.getMock(), open(FAKE_DEVICE_NAME)).Times(1);
    (void)RequestsHandlerImpl<FakeFileApi, MoveableMockIoctlApi>(FAKE_DEVICE_NAME, creationApi);
}

TEST(RequestsHandlerTest, ListTests) {
    MoveableMockFileCreationApi creationApi;
    MoveableMockIoctlApi ioctlApi;

    const TestInfo tests[] = { { 1, "First Test" }, { 2, "Second" }, { 10, "BumpInId" }, { 6, "BackDown" } };
    const uint64_t numberOfTests = sizeof(tests) / sizeof(tests[0]);

    EXPECT_CALL(ioctlApi.getMock(), send(::testing::_, ::testing::_, ::testing::_))
        .WillOnce([&numberOfTests](FileHandleGuard<FakeFileApi>&, const Buffer& inputBuffer, Buffer& outputBuffer) {
            assertSameBufferAsObj(Ioctl::GetNumberOfTestsInput{}, inputBuffer);

            ASSERT_EQ(outputBuffer.size(), sizeof(Ioctl::GetNumberOfTestsOutput));
            auto* output = reinterpret_cast<Ioctl::GetNumberOfTestsOutput*>(outputBuffer.data());
            output->numberOfTests = numberOfTests;
        })
        .WillOnce([&numberOfTests, &tests](FileHandleGuard<FakeFileApi>&, const Buffer& inputBuffer, Buffer& outputBuffer) {
            assertSameBufferAsObj(Ioctl::ListTestsInput{}, inputBuffer);
            
            ASSERT_EQ(outputBuffer.size(), sizeof(TestInfo) * numberOfTests);
            auto* output = reinterpret_cast<Ioctl::ListTestsOutput*>(outputBuffer.data());
            memcpy(output->info, tests, outputBuffer.size());
        });
    RequestsHandlerImpl<FakeFileApi, MoveableMockIoctlApi> handler(FAKE_DEVICE_NAME, creationApi, std::move(ioctlApi));

    const auto output = handler.listTests(ListTestsInput{});
    ASSERT_EQ(output.tests.size(), numberOfTests);
    for (uint32_t i = 0; i < numberOfTests; i++) {
        ASSERT_EQ(output.tests[i].id, tests[i].id);
        ASSERT_EQ(output.tests[i].name, tests[i].name);
    }
}

TEST(RequestsHandlerTest, RunTest) {
    MoveableMockFileCreationApi creationApi;
    MoveableMockIoctlApi ioctlApi;

    const uint32_t arbitraryTestId = 1001;
    const NTSTATUS arbitraryResult = 37002;
    
    EXPECT_CALL(ioctlApi.getMock(), send(::testing::_, ::testing::_, ::testing::_))
        .WillOnce([&arbitraryTestId, &arbitraryResult](FileHandleGuard<FakeFileApi>&, const Buffer& inputBuffer, Buffer& outputBuffer) {
            assertSameBufferAsObj(Ioctl::RunTestInput{ .testId = arbitraryTestId }, inputBuffer);

            ASSERT_EQ(outputBuffer.size(), sizeof(Ioctl::RunTestOutput));
            auto* output = reinterpret_cast<Ioctl::RunTestOutput*>(outputBuffer.data());
            output->result = arbitraryResult;
        });
    RequestsHandlerImpl<FakeFileApi, MoveableMockIoctlApi> handler(FAKE_DEVICE_NAME, creationApi, std::move(ioctlApi));

    const auto output = handler.runTest(RunTestInput{.testId = arbitraryTestId});
    ASSERT_EQ(output.result.status, arbitraryResult);
}

namespace {
template <typename T>
void assertSameBufferAsObj(const T& obj, const Buffer& buffer) {
    ASSERT_EQ(buffer.size(), sizeof(T));
    ASSERT_EQ(memcmp(buffer.data(), &obj, buffer.size()), 0);
}
}