#pragma once

#include <gmock/gmock.h>

#include "Defs.h"

class MockResource {
public:
    MOCK_METHOD(NTSTATUS, initialize, ());
    MOCK_METHOD(NTSTATUS, destroy, ());
};

class MoveableMockResource {
public:
    MoveableMockResource() : m_mock(std::make_unique<testing::StrictMock<MockResource>>()) {
    }

    NTSTATUS initialize() {
        return m_mock->initialize();
    }

    NTSTATUS destroy() {
        return m_mock->destroy();
    }

    testing::StrictMock<MockResource>& getMock() {
        return *m_mock;
    }

private:
    std::unique_ptr<testing::StrictMock<MockResource>> m_mock;
};
