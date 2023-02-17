#pragma once

#include "Defs.h"

#include <string>

class InternalMessages final {
public:
    InternalMessages() = delete;

    using IdType = uint32_t;

    struct TestInfo {
        IdType id;
        std::string name;
    };

    struct TestResult {
        bool passed;
        std::string msg;
    };

    struct ListTestsInput {
        // intentionally left blank
    };

    struct ListTestsOutput {
        std::vector<TestInfo> tests;
    };

    struct RunTestInput {
        IdType testId;
    };

    struct RunTestOutput {
        TestResult result;
    };
};
