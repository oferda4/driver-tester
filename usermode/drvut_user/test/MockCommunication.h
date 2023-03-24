#pragma once

#include <gmock/gmock.h>

#include "Communication.h"
#include "MockStream.h"

class MockCommunicationSetup {
public:
    MOCK_METHOD(MoveableMockStream, run, ());
};

class MoveableMockCommunicationSetup {
public:
    MoveableMockCommunicationSetup()
        : m_mock(std::make_unique<testing::StrictMock<MockCommunicationSetup>>()) {
    }

    MoveableMockStream run() {
        return m_mock->run();
    }

    testing::StrictMock<MockCommunicationSetup>& getMock() {
        return *m_mock;
    }

private:
    std::unique_ptr<testing::StrictMock<MockCommunicationSetup>> m_mock;
};

class MockCommunicationLogic {
public:
    MOCK_METHOD(void, run, (MoveableMockStream&));
};

class MoveableMockCommunicationLogic {
public:
    MoveableMockCommunicationLogic()
        : m_mock(std::make_unique<testing::StrictMock<MockCommunicationLogic>>()) {
    }

    void run(MoveableMockStream& stream) {
        m_mock->run(stream);
    }

    testing::StrictMock<MockCommunicationLogic>& getMock() {
        return *m_mock;
    }

private:
    std::unique_ptr<testing::StrictMock<MockCommunicationLogic>> m_mock;
};
