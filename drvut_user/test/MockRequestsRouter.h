#pragma once

#include <gmock/gmock.h>

#include "RequestsRouter.h"

class MockRequestsRouter {
public:
    MOCK_METHOD(Buffer, route, (const Buffer&));
};

class MoveableMockRequestsRouter {
public:
    MoveableMockRequestsRouter()
        : m_mock(std::make_unique<testing::StrictMock<MockRequestsRouter>>()) {}

    Buffer route(const Buffer& data) {
        return m_mock->route(data);
    }

    testing::StrictMock<MockRequestsRouter>& getMock() {
        return *m_mock;
    }

private:
    std::unique_ptr<testing::StrictMock<MockRequestsRouter>> m_mock;
};
