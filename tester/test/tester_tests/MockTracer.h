#pragma once

#include <gmock/gmock.h>

#include "tester/Defs.h"
#include "tester/Exceptions.h"

struct MockTracer {
    static void exception(const Exception& exc) {}
    static void info(const std::wstring& msg) {}
};
