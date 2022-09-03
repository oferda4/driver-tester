#pragma once

/**
 * We keep these structs simple as they can be used from a user mode code
 * and kernel mode code (which is lack some stls).
 */

constexpr unsigned int MAX_NAME_SIZE = 20;

struct FixtureInfo {
    unsigned int id;
    char name[MAX_NAME_SIZE];
};

struct TestInfo {
    unsigned int id;
    char name[MAX_NAME_SIZE];
};

struct TestResult {
    unsigned long status;
};
