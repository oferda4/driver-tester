#pragma once

#include <gmock/gmock.h>

#include "RequestsHandler.h"

class MockRequestsHandler {
public:
    MOCK_METHOD(InternalMessages::ListTestsOutput, listTests, (const InternalMessages::ListTestsInput&));
    MOCK_METHOD(InternalMessages::RunTestOutput, runTest, (const InternalMessages::RunTestInput&));
};

class MoveableMockRequestsHandler {
public:
    MoveableMockRequestsHandler()
        : m_mock(std::make_unique<testing::StrictMock<MockRequestsHandler>>()) {}

    InternalMessages::ListTestsOutput listTests(const InternalMessages::ListTestsInput& input) {
        return m_mock->listTests(input);
    }

    InternalMessages::RunTestOutput runTest(const InternalMessages::RunTestInput& input) {
        return m_mock->runTest(input);
    }
    
    testing::StrictMock<MockRequestsHandler>& getMock() {
        return *m_mock;
    }

private:
    std::unique_ptr<testing::StrictMock<MockRequestsHandler>> m_mock;
};
