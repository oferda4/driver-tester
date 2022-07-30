#pragma once

#include "Defs.h"

class Ioctls {
public:
    static constexpr uint32_t GET_FIXTURES = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_READ_DATA);
    static constexpr uint32_t GET_TESTS = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_READ_DATA);
    static constexpr uint32_t RUN_TESTS = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_WRITE_DATA);
};
