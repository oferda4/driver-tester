#pragma once

#include <gmock/gmock.h>

#include "RequestsHandler.h"

class MockRequestsHandler {
public:
    MOCK_METHOD(ListFixturesOutput, listFixtures, (const ListFixturesInput&));
    MOCK_METHOD(ListTestsOutput, listTests, (const ListTestsInput&));
    MOCK_METHOD(RunTestOutput, runTest, (const RunTestInput&));
};

class MoveableMockRequestsHandler {
public:
    MoveableMockRequestsHandler()
        : m_mock(std::make_unique<testing::StrictMock<MockRequestsHandler>>()) {}

    ListFixturesOutput listFixtures(const ListFixturesInput& input) {
        return m_mock->listFixtures(input);
    }

    ListTestsOutput listTests(const ListTestsInput& input) {
        return m_mock->listTests(input);
    }

    RunTestOutput runTest(const RunTestInput& input) {
        return m_mock->runTest(input);
    }
    
    testing::StrictMock<MockRequestsHandler>& getMock() {
        return *m_mock;
    }

private:
    std::unique_ptr<testing::StrictMock<MockRequestsHandler>> m_mock;
};
