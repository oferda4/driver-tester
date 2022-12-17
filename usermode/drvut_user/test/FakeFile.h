#pragma once

#include <gmock/gmock.h>

#include "Defs.h"
#include "File.h"

class FakeFileApi final {
public:
    void close(uint32_t) {}
    HANDLE open(const std::wstring&) { return 0; }
};
