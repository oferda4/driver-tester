#pragma once

#include "Parser.h"

class ProtobufParser final {
public:
    ParsedRequest parseRequest(const Buffer& data);
    Buffer serializeListTestsOutput(const ListTestsOutput& output);
    Buffer serializeRunTestOutput(const RunTestOutput& output);
};
