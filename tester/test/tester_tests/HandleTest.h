#pragma once

#include <gmock/gmock.h>
#include <optional>

#include "tester/Defs.h"
#include "tester/Handle.h"

class HandleTest : public testing::Test {
private:
    void SetUp() override;
    void TearDown() override;
};

class MockException : public Exception {
public:
    MockException(std::wstring msg);
};

struct MockHandleTraits {
    MockHandleTraits() = default;
    MockHandleTraits(MockHandleTraits&&) noexcept = default;
    MockHandleTraits& operator=(MockHandleTraits&&) noexcept = default;
    // MOVEABLE(MockHandleTraits);

    using HandleType = uint32_t;
    using ExceptionType = MockException;

    static constexpr HandleType INVALID_VALUE = 0;
    static bool close(HandleType handle);

    MOCK_METHOD(bool, mockClose, (HandleType handle));

    static std::optional<testing::NiceMock<MockHandleTraits>> currMock;
};

using MockHandle = Handle<MockHandleTraits>;
