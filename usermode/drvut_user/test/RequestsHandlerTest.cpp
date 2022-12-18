#include <gtest/gtest.h>

#include "RequestsHandler.h"

#include "MockFile.h"
#include "MockIoctlApi.h"

namespace {
const std::wstring FAKE_DEVICE_NAME = L"fake";
}

TEST(RequestsHandlerTest, FileOpening) {
    MoveableMockFileCreationApi creationApi;
    EXPECT_CALL(creationApi.getMock(), open(FAKE_DEVICE_NAME)).Times(1);
    RequestsHandlerImpl<FakeFileApi, MockIoctlApi> handler(FAKE_DEVICE_NAME, creationApi);
}