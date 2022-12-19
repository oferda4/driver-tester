#include <gtest/gtest.h>

#include "RequestsHandler.h"

#include "MockFile.h"
#include "MockIoctlApi.h"

namespace {
const std::wstring FAKE_DEVICE_NAME = L"fake";
}

TEST(RequestsHandlerTest, OpenFileOnConstruction) {
    MoveableMockFileCreationApi creationApi;

    EXPECT_CALL(creationApi.getMock(), open(FAKE_DEVICE_NAME)).Times(1);
    (void)RequestsHandlerImpl<FakeFileApi, MoveableMockIoctlApi>(FAKE_DEVICE_NAME, creationApi);
}

TEST(RequestsHandlerTest, ListTests) {
    MoveableMockFileCreationApi creationApi;
    MoveableMockIoctlApi ioctlApi;

    const uint64_t numberOfTests = 100;

    EXPECT_CALL(ioctlApi.getMock(), send(::testing::_, ::testing::_, ::testing::_))
        .WillOnce([&numberOfTests](FileHandleGuard<FakeFileApi>&, const Buffer& inputBuffer, Buffer& outputBuffer) {
            const Ioctl::GetNumberOfTestsInput expectedInput{};
            ASSERT_EQ(inputBuffer.size(), sizeof(expectedInput));
            ASSERT_EQ(memcmp(inputBuffer.data(), &expectedInput, inputBuffer.size()), 0);
            
            ASSERT_EQ(outputBuffer.size(), sizeof(Ioctl::GetNumberOfTestsOutput));
            auto* output = reinterpret_cast<Ioctl::GetNumberOfTestsOutput*>(outputBuffer.data());
            output->numberOfTests = numberOfTests;
        });
    RequestsHandlerImpl<FakeFileApi, MoveableMockIoctlApi> handler(FAKE_DEVICE_NAME, creationApi, std::move(ioctlApi));

    auto output = handler.listTests(ListTestsInput{});
    ASSERT_EQ(output.tests.size(), numberOfTests);
}