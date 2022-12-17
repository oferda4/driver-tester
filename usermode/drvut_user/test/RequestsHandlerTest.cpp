#include <gtest/gtest.h>

#include "RequestsHandler.h"

#include "FakeFile.h"
#include "MockIoctlApi.h"

namespace {
const std::wstring FAKE_DEVICE_NAME = L"fake";
}

TEST(RequestsHandlerTest, ListTests) {
    FakeFileApi creationApi;
    RequestsHandlerImpl<FakeFileApi, MockIoctlApi> handler(FAKE_DEVICE_NAME, creationApi);
}