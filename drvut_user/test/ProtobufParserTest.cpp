#include <gtest/gtest.h>

#include "ProtobufParser.h"

#include "messages.pb.h"

TEST(TestProtobufParser, BadRequest) {
    ASSERT_THROW(ProtobufParser().parseRequest(Buffer(1, 0)), FailedParsingMessage);
}