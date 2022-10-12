#pragma once

#include <gmock/gmock.h>

struct MockHandleTraits {
    using Type = int;
    MOCK_METHOD(void, close, (Type));
};

struct MoveableMockHandleTraits {
    using Type = MockHandleTraits::Type;

    MoveableMockHandleTraits()
        : m_mock(std::make_unique<testing::NiceMock<MockHandleTraits>>()) {}

    void close(Type handle) {
        m_mock->close(handle);
    }


    testing::NiceMock<MockHandleTraits>& getMock() {
        return *m_mock;
    }

private:
    std::unique_ptr<testing::NiceMock<MockHandleTraits>> m_mock;
};
