#pragma once

#include <gmock/gmock.h>

#include "RequestsHandler.h"

class MockRequestsHandler {
public:
    MOCK_METHOD(ListFixturesOutput, listFixtures, (const ListFixturesInput&));
};

class MoveableMockRequestsHandler {
public:
    MoveableMockRequestsHandler()
        : m_mock(std::make_unique<testing::StrictMock<MockRequestsHandler>>()) {}

    ListFixturesOutput listFixtures(const ListFixturesInput& input) {
        return m_mock->listFixtures(input);
    }
    
    testing::StrictMock<MockRequestsHandler>& getMock() {
        return *m_mock;
    }

private:
    std::unique_ptr<testing::StrictMock<MockRequestsHandler>> m_mock;
};
