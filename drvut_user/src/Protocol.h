#pragma once

#include "Defs.h"
#include "Buffer.h"
#include "Messages.h"

enum class RequestType : uint32_t {
    LIST_FIXTURES,
    LIST_TESTS,
    RUN_TEST
};

struct Request {
    RequestType type;
    Buffer input;
};

template<typename T>
concept Protocol = requires(T& t, 
                            const Buffer& data, 
                            const ListFixturesOutput& listFixturesOutput,
                            const ListTestsOutput& listTestsOutput,
                            const RunTestOutput& runTestOutput) {
    { t.parse(data) } -> std::same_as<Request>;
    { t.parseListFixturesInput(data) } -> std::same_as<ListFixturesInput>;
    { t.parseListFixturesOutput(listFixturesOutput) } -> std::same_as<Buffer>;
    { t.parseListTestsInput(data) } -> std::same_as<ListTestsInput>;
    { t.parseListTestsOutput(listTestsOutput) } -> std::same_as<Buffer>;
    { t.parseRunTestInput(data) } -> std::same_as<RunTestInput>;
    { t.parseRunTestOutput(runTestOutput) } -> std::same_as<Buffer>;
};
