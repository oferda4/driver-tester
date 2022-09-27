#pragma once

#include <gmock/gmock.h>

#include "Protocol.h"

class MockProtocol {
public:
    MOCK_METHOD(Request, parse, (const Buffer&));
    MOCK_METHOD(ListFixturesInput, parseListFixturesInput, (const Buffer&));
    MOCK_METHOD(Buffer, parseListFixturesOutput, (const ListFixturesOutput&));
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

    testing::StrictMock<MockProtocol>& getMock() {
        return *m_mock;
    }

private:
    std::unique_ptr<testing::StrictMock<MockProtocol>> m_mock;
};
