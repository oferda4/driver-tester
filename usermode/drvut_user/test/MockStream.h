#pragma once

#include <gmock/gmock.h>

#include "Stream.h"

class MockStream {
public:
    MOCK_METHOD(Buffer, recv, ());
    MOCK_METHOD(void, send, (const Buffer&));
};

class MoveableMockStream {
public:
    MoveableMockStream() : m_mock(std::make_unique<testing::StrictMock<MockStream>>()) {
    }

    Buffer recv() {
        return m_mock->recv();
    }

    void send(const Buffer& data) {
        m_mock->send(data);
    }

    testing::StrictMock<MockStream>& getMock() {
        return *m_mock;
    }

private:
    std::unique_ptr<testing::StrictMock<MockStream>> m_mock;
};
