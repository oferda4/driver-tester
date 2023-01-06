#pragma once

#include "Defs.h"
#include "Buffer.h"
#include "InternalMessages.h"

enum class RequestType : uint32_t {
    INVALID,
    LIST_TESTS,
    RUN_TEST
};

struct ParsedRequest {
    RequestType type;
    union {
        InternalMessages::ListTestsInput listTestsInput;
        InternalMessages::RunTestInput runTestInput;
    } input;
};

template<typename T>
concept Parser = requires(T& parser, 
                          const Buffer& data, 
                          const InternalMessages::ListTestsOutput& listTestsOutput,
                          const InternalMessages::RunTestOutput& runTestOutput) {
    { parser.parseRequest(data) } -> std::same_as<ParsedRequest>;
    { parser.serializeListTestsOutput(listTestsOutput) } -> std::same_as<Buffer>;
    { parser.serializeRunTestOutput(runTestOutput) } -> std::same_as<Buffer>;
};
