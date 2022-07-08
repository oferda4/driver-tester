#pragma once

#include <gmock/gmock.h>

#include "Messages.h"

class MockClientCommunicator {
public:
    MOCK_METHOD(std::vector<FixtureInfo>, getFixtures, ());
    MOCK_METHOD(std::vector<TestInfo>, getTests, (uint32_t fixtureId));
    MOCK_METHOD(TestResult, runTest, (uint32_t testId));
};
