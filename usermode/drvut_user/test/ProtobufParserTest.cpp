#include <gtest/gtest.h>

#include "ProtobufParser.h"

#include "ProtobufUtils.h"

#include "messages.pb.h"

using google::protobuf::Message;

namespace {
ParsedRequest serializeAndParse(const Message& msg);
void assertSameFixtureInfo(FixtureInfo info1, ListFixturesResponse_FixtureInfo info2);
void assertSameTestInfo(TestInfo info1, ListTestsResponse_TestInfo info2);
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

TEST(TestProtobufParser, ListFixturesOutput) {
    const std::vector<FixtureInfo> fixtures = { 
        { 3, "some name" }, 
        { 5, "another name" },
        { 9, "nine" }
    };
    const ListFixturesOutput output = { fixtures };

    const auto response = ProtobufUtils::deserialize<ListFixturesResponse>(
        ProtobufParser().parseListFixturesOutput(output));

    ASSERT_EQ(fixtures.size(), response.fixtures_size());
    for (int i = 0; i < response.fixtures_size(); i++) {
        assertSameFixtureInfo(fixtures[i], response.fixtures()[i]);
    }
}

TEST(TestProtobufParser, ListTestsOutput) {
    const std::vector<TestInfo> tests = {
        { 21, "this is a test" },
        { 3, "NiceTest" },
        { 15, "Excellent Test!" }
    };
    const ListTestsOutput output = { tests };

    const auto response = ProtobufUtils::deserialize<ListTestsResponse>(
        ProtobufParser().parseListTestsOutput(output));

    ASSERT_EQ(tests.size(), response.tests_size());
    for (int i = 0; i < response.tests_size(); i++) {
        assertSameTestInfo(tests[i], response.tests()[i]);
    }
}

TEST(TestProtobufParser, RunTestOutput) {
    const uint64_t arbitraryTestResult = 1001;
    const RunTestOutput output = { { arbitraryTestResult } };

    const auto response = ProtobufUtils::deserialize<RunTestResponse>(
        ProtobufParser().parseRunTestOutput(output));

    ASSERT_EQ(arbitraryTestResult, response.status());
}

namespace {
ParsedRequest serializeAndParse(const Message& msg) {
    return ProtobufParser().parseRequest(ProtobufUtils::serialize(msg));
}

void assertSameFixtureInfo(FixtureInfo info1, ListFixturesResponse_FixtureInfo info2) {
    ASSERT_EQ(info1.id, info2.id());
    ASSERT_EQ(info1.name, info2.name());
}

void assertSameTestInfo(TestInfo info1, ListTestsResponse_TestInfo info2) {
    ASSERT_EQ(info1.id, info2.id());
    ASSERT_EQ(info1.name, info2.name());
}
}
