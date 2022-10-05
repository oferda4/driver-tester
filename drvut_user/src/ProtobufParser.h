#pragma once

#include "Parser.h"

struct FailedSerializingMessage : std::exception {
    // left blank intentionally
};

struct FailedParsingMessage : std::exception {
    // left blank intentionally
};

class ProtobufParser final {
public:
    ParsedRequest parseRequest(const Buffer& data);
    Buffer parseListFixturesOutput(const ListFixturesOutput& output);
    Buffer parseListTestsOutput(const ListTestsOutput& output);
    Buffer parseRunTestOutput(const RunTestOutput& output);
};
