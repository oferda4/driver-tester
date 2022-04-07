#pragma once

#include "tester/Handle.h"

class MockException : public Exception {
public:
    MockException(std::wstring msg);
};

class MockHandleTraits {
public:
    MOVEABLE(MockHandleTraits);

    using HandleType = uint32_t;
    using ExceptionType = MockException;

    static constexpr HandleType INVALID_VALUE = 0;
    static bool close(HandleType handle);
};

using MockHandle = Handle<MockHandleTraits>;
