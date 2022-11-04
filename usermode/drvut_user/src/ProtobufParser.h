#pragma once

#include "Parser.h"

class ProtobufParser final {
public:
    ParsedRequest parseRequest(const Buffer& data);
    Buffer parseListTestsOutput(const ListTestsOutput& output);
    Buffer parseRunTestOutput(const RunTestOutput& output);
};
