#include <gtest/gtest.h>

#include "ProtobufParser.h"

#include "ProtobufUtils.h"

#include "messages.pb.h"

using google::protobuf::Message;

namespace {
ParsedRequest serializeAndParse(const Message& msg);
}

TEST(TestProtobufParser, BadRequest) {
    ASSERT_THROW(ProtobufParser().parseRequest(Buffer(1, 0)), FailedParsingMessage);
}

TEST(TestProtobufParser, ListFixturesRequest) {
    Request request;
    auto* specificRequest = request.mutable_list_fixtures();
    const auto parsedRequest = serializeAndParse(request);

    ASSERT_EQ(parsedRequest.type, RequestType::LIST_FIXTURES);
}

TEST(TestProtobufParser, ListTestsRequest) {
    const uint32_t arbitraryFixtureId = 24;
    Request request;
    auto *specificRequest = request.mutable_list_tests();
    specificRequest->set_fixture_id(arbitraryFixtureId);
    const auto parsedRequest = serializeAndParse(request);

    ASSERT_EQ(parsedRequest.type, RequestType::LIST_TESTS);
    ASSERT_EQ(parsedRequest.input.listTestsInput.fixtureId, arbitraryFixtureId);
}

TEST(TestProtobufParser, RunTestRequest) {
    const uint32_t arbitraryFixtureId = 18;
    const uint32_t arbitraryTestId = 103;
    Request request;
    auto* specificRequest = request.mutable_run_test();
    specificRequest->set_fixture_id(arbitraryFixtureId);
    specificRequest->set_test_id(arbitraryTestId);
    const auto parsedRequest = serializeAndParse(request);

    ASSERT_EQ(parsedRequest.type, RequestType::RUN_TEST);
    ASSERT_EQ(parsedRequest.input.runTestInput.fixtureId, arbitraryFixtureId);
    ASSERT_EQ(parsedRequest.input.runTestInput.testId, arbitraryTestId);
}

namespace {
ParsedRequest serializeAndParse(const Message& msg) {
    return ProtobufParser().parseRequest(ProtobufUtils::serialize(msg));
}
}
