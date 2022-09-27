#pragma once

#include <gmock/gmock.h>

#include "Connection.h"

class MockConnection {
public:
    MOCK_METHOD(Buffer, recv, (uint32_t));
    MOCK_METHOD(uint32_t, send, (const Buffer&));
};

class MoveableMockConnection {
public:
    MoveableMockConnection() 
        : m_mock(std::make_unique<testing::StrictMock<MockConnection>>()) {}

    Buffer recv(uint32_t size) {
        return m_mock->recv(size);
    }

    uint32_t send(const Buffer& data) {
        return m_mock->send(data);
    }

    testing::StrictMock<MockConnection>& getMock() {
        return *m_mock;
    }

private:
    std::unique_ptr<testing::StrictMock<MockConnection>> m_mock;
};
