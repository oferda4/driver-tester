#pragma once

#include "Defs.h"

class Ioctl {
public:
    Ioctl() = delete;

    static constexpr unsigned int MAX_NAME_SIZE = 20;

#pragma pack(push)
#pragma pack(1)
    struct TestInfo {
        unsigned int id;
        char name[MAX_NAME_SIZE];
    };

    struct TestResult {
        long status;
    };

    struct GetNumberOfTestsInput {
        // intentionally left blank
    };

    struct GetNumberOfTestsOutput {
        uint64_t numberOfTests;
    };

    struct ListTestsInput {
        // intentionally left blank
    };

    struct ListTestsOutput {
#pragma warning(push)
#pragma warning(disable : 4200)
        TestInfo info[];
#pragma warning(pop)
    };
    
    struct RunTestInput {
        uint32_t testId;
    };

    struct RunTestOutput {
        NTSTATUS result;
    };
#pragma pack(pop)

    static constexpr uint32_t GET_NUMBER_OF_TESTS = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_READ_DATA);
    static constexpr uint32_t LIST_TESTS = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_READ_DATA);
    static constexpr uint32_t RUN_TEST = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_WRITE_DATA);
};
