#pragma once

#include <gmock/gmock.h>

#include "tester/Service.h"
#include "MockException.h"

struct BasicMockServiceController {
    using ExceptionType = MockException;

    BasicMockServiceController() = default;
    ~BasicMockServiceController() = default;
    NOCOPY(BasicMockServiceController);
    BasicMockServiceController(BasicMockServiceController&&) noexcept {};
    BasicMockServiceController& operator=(BasicMockServiceController&&) noexcept {};

    MOCK_METHOD(bool, start, (), ());
    MOCK_METHOD(bool, stop, (), ());
    MOCK_METHOD(bool, remove, (), ());
};

using MockServiceController = BasicMockServiceController;
using MockService = Service<MockServiceController>;
