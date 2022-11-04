#pragma once

#include "Defs.h"

#include <string>

using IdType = uint32_t;

struct TestInfo {
    IdType id;
    std::string name;
};

struct TestResult {
    uint64_t status;
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
