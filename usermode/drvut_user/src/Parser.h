#pragma once

#include "Defs.h"
#include "Buffer.h"
#include "Messages.h"

enum class RequestType : uint32_t {
    LIST_FIXTURES,
    LIST_TESTS,
    RUN_TEST
};

struct ParsedRequest {
    RequestType type;
    union {
        ListFixturesInput listFixturesInput;
        ListTestsInput listTestsInput;
        RunTestInput runTestInput;
    } input;
};

template<typename T>
concept Parser = requires(T& parser, 
                          const Buffer& data, 
                          const ListFixturesOutput& listFixturesOutput,
                          const ListTestsOutput& listTestsOutput,
                          const RunTestOutput& runTestOutput) {
    { parser.parseRequest(data) } -> std::same_as<ParsedRequest>;
    { parser.parseListFixturesOutput(listFixturesOutput) } -> std::same_as<Buffer>;
    { parser.parseListTestsOutput(listTestsOutput) } -> std::same_as<Buffer>;
    { parser.parseRunTestOutput(runTestOutput) } -> std::same_as<Buffer>;
};
