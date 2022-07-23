#pragma once

#include <gmock/gmock.h>

#include "tester/Defs.h"

class MockLastErrorAPIImpl {
public:
    MOCK_METHOD(uint32_t, getLastError, (), (const));
};
