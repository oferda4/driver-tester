#pragma once

#include <gmock/gmock.h>

#include "Protocol.h"

class MockProtocol {
public:
    MOCK_METHOD(Request, parse, (const Buffer&));
    MOCK_METHOD(ListFixturesInput, parseListFixturesInput, (const Buffer&));
    MOCK_METHOD(Buffer, parseListFixturesOutput, (const ListFixturesOutput&));
    MOCK_METHOD(ListTestsInput, parseListTestsInput, (const Buffer&));
    MOCK_METHOD(Buffer, parseListTestsOutput, (const ListTestsOutput&));
    MOCK_METHOD(RunTestInput, parseRunTestInput, (const Buffer&));
    MOCK_METHOD(Buffer, parseRunTestOutput, (const RunTestOutput&));
};

class MoveableMockProtocol {
public:
    MoveableMockProtocol()
        : m_mock(std::make_unique<testing::StrictMock<MockProtocol>>()) {}

    Request parse(const Buffer& data) {
        return m_mock->parse(data);
    }

    ListFixturesInput parseListFixturesInput(const Buffer& data) {
        return m_mock->parseListFixturesInput(data);
    }

    Buffer parseListFixturesOutput(const ListFixturesOutput& output) {
        return m_mock->parseListFixturesOutput(output);
    }

    ListTestsInput parseListTestsInput(const Buffer& data) {
        return m_mock->parseListTestsInput(data);
    }

    Buffer parseListTestsOutput(const ListTestsOutput& output) {
        return m_mock->parseListTestsOutput(output);
    }

    RunTestInput parseRunTestInput(const Buffer& data) {
        return m_mock->parseRunTestInput(data);
    }

    Buffer parseRunTestOutput(const RunTestOutput& output) {
        return m_mock->parseRunTestOutput(output);
    }

    testing::StrictMock<MockProtocol>& getMock() {
        return *m_mock;
    }

private:
    std::unique_ptr<testing::StrictMock<MockProtocol>> m_mock;
};
