#pragma once

#include "Defs.h"

class Ioctls {
public:
    struct ListTestsInput {
        uint32_t fixtureId;
    };

    struct RunTestInput {
        uint32_t fixtureId;
        uint32_t testId;
    };

    struct RunTestOutput {
        NTSTATUS result;
    };

    static constexpr uint32_t LIST_FIXTURES = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_READ_DATA);
    static constexpr uint32_t LIST_TESTS = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_READ_DATA);
    static constexpr uint32_t RUN_TEST = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_WRITE_DATA);
};
