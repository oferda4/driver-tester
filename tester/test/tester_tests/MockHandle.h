#pragma once

#include <gmock/gmock.h>
#include <optional>

#include "tester/Handle.h"
#include "MockException.h"
#include "MockTracer.h"

struct MockHandleTraits {
    MockHandleTraits() = default;
    ~MockHandleTraits() = default;
    NOCOPY(MockHandleTraits);
    MOVEABLE(MockHandleTraits);

    using HandleType = uint32_t;
    using ExceptionType = MockException;

    static constexpr HandleType INVALID_VALUE = 0;
    static bool close(HandleType handle);

    MOCK_METHOD(bool, mockClose, (HandleType handle));

    static std::optional<testing::NiceMock<MockHandleTraits>> currMock;
};

using MockHandle = Handle<MockHandleTraits, MockTracer>;
