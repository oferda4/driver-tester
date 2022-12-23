#pragma once

#include "Defs.h"
#include "Buffer.h"
#include "InternalMessages.h"

enum class RequestType : uint32_t {
    LIST_TESTS,
    RUN_TEST
};

struct ParsedRequest {
    RequestType type;
    union {
        ListTestsInput listTestsInput;
        RunTestInput runTestInput;
    } input;
};

template<typename T>
concept Parser = requires(T& parser, 
                          const Buffer& data, 
                          const ListTestsOutput& listTestsOutput,
                          const RunTestOutput& runTestOutput) {
    { parser.parseRequest(data) } -> std::same_as<ParsedRequest>;
    { parser.serializeListTestsOutput(listTestsOutput) } -> std::same_as<Buffer>;
    { parser.parseRunTestOutput(runTestOutput) } -> std::same_as<Buffer>;
};
