#pragma once

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
    NTSTATUS status;
};
