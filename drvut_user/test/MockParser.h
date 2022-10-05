#pragma once

#include <gmock/gmock.h>

#include "Parser.h"

class MockParser {
public:
    MOCK_METHOD(ParsedRequest, parseRequest, (const Buffer&));
    MOCK_METHOD(Buffer, parseListFixturesOutput, (const ListFixturesOutput&));
    MOCK_METHOD(Buffer, parseListTestsOutput, (const ListTestsOutput&));
    MOCK_METHOD(Buffer, parseRunTestOutput, (const RunTestOutput&));
};

class MoveableMockParser {
public:
    MoveableMockParser()
        : m_mock(std::make_unique<testing::StrictMock<MockParser>>()) {}

    ParsedRequest parseRequest(const Buffer& data) {
        return m_mock->parseRequest(data);
    }

    Buffer parseListFixturesOutput(const ListFixturesOutput& output) {
        return m_mock->parseListFixturesOutput(output);
    }

    Buffer parseListTestsOutput(const ListTestsOutput& output) {
        return m_mock->parseListTestsOutput(output);
    }

    Buffer parseRunTestOutput(const RunTestOutput& output) {
        return m_mock->parseRunTestOutput(output);
    }

    testing::StrictMock<MockParser>& getMock() {
        return *m_mock;
    }

private:
    std::unique_ptr<testing::StrictMock<MockParser>> m_mock;
};
