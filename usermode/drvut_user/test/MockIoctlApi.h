#pragma once

#include <gmock/gmock.h>

#include "Defs.h"
#include "IoctlApi.h"
#include "Buffer.h"
#include "FakeFile.h"

class MockIoctlApi {
public:
    virtual ~MockIoctlApi() = default;

    MOCK_METHOD(void, send, (FileHandleGuard<FakeFileApi>&, const Buffer&, Buffer&));
};

class MoveableMockIoctlApi {
public:
    MoveableMockIoctlApi()
        : m_mock(std::make_unique<testing::StrictMock<MockIoctlApi>>()) {}
    virtual ~MoveableMockIoctlApi() = default;

    void send(FileHandleGuard<FakeFileApi>& handle, const Buffer& input, Buffer& output) {
        m_mock->send(handle, input, output);
    }

private:
    std::unique_ptr<testing::StrictMock<MockIoctlApi>> m_mock;
};
