#pragma once

#include <gmock/gmock.h>

#include "tester/Exceptions.h"

class MockException final : public Exception {
public:
    MockException(std::wstring msg);
};
