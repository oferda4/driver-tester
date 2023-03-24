#pragma once

#include "Defs.h"

#include <gmock/gmock.h>

#include "Buffer.h"
#include "IoctlApi.h"
#include "MockFile.h"

class MockIoctlApi {
public:
    MOCK_METHOD(void, send, (FileHandleGuard<FakeFileApi>&, uint32_t code, const Buffer&, Buffer&));
};

class MoveableMockIoctlApi {
public:
    MoveableMockIoctlApi() : m_mock(std::make_unique<testing::StrictMock<MockIoctlApi>>()) {
    }

    void send(FileHandleGuard<FakeFileApi>& handle, uint32_t code, const Buffer& input,
              Buffer& output) {
        m_mock->send(handle, code, input, output);
    }

    testing::StrictMock<MockIoctlApi>& getMock() {
        return *m_mock;
    }

private:
    std::unique_ptr<testing::StrictMock<MockIoctlApi>> m_mock;
};
