#pragma once

#include "Defs.h"

class Ioctl {
public:
#pragma pack(push)
#pragma pack(1)
    struct ListTestsInput {
        // intentionally left blank
    };

    struct ListTestsOutput {
        uint64_t numberOfTests;
#pragma warning(push)
#pragma warning(disable: 4200)
        TestInfo info[0];
#pragma warning(pop)
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
