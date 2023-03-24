#pragma once

#include <gmock/gmock.h>

#include "MockConnection.h"
#include "Server.h"

class MockServer {
public:
    using ConnectionType = MoveableMockConnection;
    MOCK_METHOD(ConnectionType, waitForConnection, ());
};

class MoveableMockServer {
public:
    using ConnectionType = MockServer::ConnectionType;

    MoveableMockServer() : m_mock(std::make_unique<testing::StrictMock<MockServer>>()) {
    }

    ConnectionType waitForConnection() {
        return m_mock->waitForConnection();
    }

    testing::StrictMock<MockServer>& getMock() {
        return *m_mock;
    }

private:
    std::unique_ptr<testing::StrictMock<MockServer>> m_mock;
};
