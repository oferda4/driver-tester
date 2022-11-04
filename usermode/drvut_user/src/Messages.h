#pragma once

#include "Defs.h"

#include <string>

using IdType = uint32_t;

struct FixtureInfo {
    IdType id;
    std::string name;
};

struct TestInfo {
    IdType id;
    std::string name;
};

struct TestResult {
    uint64_t status;
};

struct ListTestsInput {
    IdType fixtureId;
};

struct ListTestsOutput {
    std::vector<TestInfo> tests;
};

struct RunTestInput {
    IdType fixtureId;
    IdType testId;
};

struct RunTestOutput {
    TestResult result;
};
