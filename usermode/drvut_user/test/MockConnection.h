#pragma once

#include <gmock/gmock.h>

#include "Connection.h"

class MockConnection {
public:
    MOCK_METHOD(Buffer, recv, (size_t));
    MOCK_METHOD(size_t, send, (const Buffer&));
};

class MoveableMockConnection {
public:
    MoveableMockConnection() 
        : m_mock(std::make_unique<testing::StrictMock<MockConnection>>()) {}

    Buffer recv(size_t size) {
        return m_mock->recv(size);
    }

    size_t send(const Buffer& data) {
        return m_mock->send(data);
    }

    testing::StrictMock<MockConnection>& getMock() {
        return *m_mock;
    }

private:
    std::unique_ptr<testing::StrictMock<MockConnection>> m_mock;
};
