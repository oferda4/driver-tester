#include <gtest/gtest.h>

#include "ProtobufParser.h"

#include "ProtobufUtils.h"

#include "runner_user_messages.pb.h"

using google::protobuf::Message;

namespace {
ParsedRequest serializeAndParse(const Message& msg);
void assertSameTestInfo(TestInfo info1, ListTestsResponse_TestInfo info2);
}

TEST(ProtobufParserTest, BadRequest) {
    ASSERT_THROW(ProtobufParser().parseRequest(Buffer(1, 0)), FailedParsingMessage);
}

TEST(ProtobufParserTest, ListTestsRequest) {
    Request request;
    auto *specificRequest = request.mutable_list_tests();
    const auto parsedRequest = serializeAndParse(request);

    ASSERT_EQ(parsedRequest.type, RequestType::LIST_TESTS);
}

TEST(ProtobufParserTest, RunTestRequest) {
    const uint32_t arbitraryTestId = 103;
    Request request;
    auto* specificRequest = request.mutable_run_test();
    specificRequest->set_test_id(arbitraryTestId);
    const auto parsedRequest = serializeAndParse(request);

    ASSERT_EQ(parsedRequest.type, RequestType::RUN_TEST);
    ASSERT_EQ(parsedRequest.input.runTestInput.testId, arbitraryTestId);
}

TEST(ProtobufParserTest, ListTestsOutput) {
    const std::vector<TestInfo> tests = {
        { 21, "this is a test" },
        { 3, "NiceTest" },
        { 15, "Excellent Test!" }
    };
    const ListTestsOutput output = { tests };

    const auto response = ProtobufUtils::deserialize<ListTestsResponse>(
        ProtobufParser().serializeListTestsOutput(output));

    ASSERT_EQ(tests.size(), response.tests_size());
    for (int i = 0; i < response.tests_size(); i++) {
        assertSameTestInfo(tests[i], response.tests()[i]);
    }
}

TEST(ProtobufParserTest, RunTestOutput) {
    const uint64_t arbitraryTestResult = 1001;
    const RunTestOutput output = { { arbitraryTestResult } };

    const auto response = ProtobufUtils::deserialize<RunTestResponse>(
        ProtobufParser().serializeRunTestOutput(output));

    ASSERT_EQ(arbitraryTestResult, response.status());
}

namespace {
ParsedRequest serializeAndParse(const Message& msg) {
    return ProtobufParser().parseRequest(ProtobufUtils::serialize(msg));
}

void assertSameTestInfo(TestInfo info1, ListTestsResponse_TestInfo info2) {
    ASSERT_EQ(info1.id, info2.id());
    ASSERT_EQ(info1.name, info2.name());
}
}
