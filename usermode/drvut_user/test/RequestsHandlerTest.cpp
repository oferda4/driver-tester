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

    TestInfo tests[] = { { 1, "First Test" }, { 2, "Second" }, { 10, "BumpInId" }, { 6, "BackDown" } };
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

    auto output = handler.listTests(ListTestsInput{});
    ASSERT_EQ(output.tests.size(), numberOfTests);
    for (uint32_t i = 0; i < numberOfTests; i++) {
        ASSERT_EQ(output.tests[i].id, tests[i].id);
        ASSERT_EQ(output.tests[i].name, tests[i].name);
    }
}

namespace {
template <typename T>
void assertSameBufferAsObj(const T& obj, const Buffer& buffer) {
    ASSERT_EQ(buffer.size(), sizeof(T));
    ASSERT_EQ(memcmp(buffer.data(), &obj, buffer.size()), 0);
}
}