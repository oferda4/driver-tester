#pragma once

#include "Defs.h"

class Ioctl {
public:
#pragma pack(push, 1)
    struct ListTestsInput {
        // intentionally left blank
    };

    struct ListTestsOutput {
        uint32_t numberOfTests;
        TestInfo info[1];
    };

    struct RunTestInput {
        uint32_t testId;
    };

    struct RunTestOutput {
        NTSTATUS result;
    };
#pragma pack(pop)

    static constexpr uint32_t LIST_TESTS = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_READ_DATA);
    static constexpr uint32_t RUN_TEST = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_WRITE_DATA);
};
