#pragma once

#include "Parser.h"

class ProtobufParser final {
public:
    ParsedRequest parseRequest(const Buffer& data);
    Buffer serializeListTestsOutput(const InternalMessages::ListTestsOutput& output);
    Buffer serializeRunTestOutput(const InternalMessages::RunTestOutput& output);
};
