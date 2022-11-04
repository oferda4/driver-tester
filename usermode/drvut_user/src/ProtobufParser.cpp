#include "ProtobufParser.h"

#include "messages.pb.h"

#include "ProtobufUtils.h"

ParsedRequest ProtobufParser::parseRequest(const Buffer& data) {
    ParsedRequest result{};
    const Request request = ProtobufUtils::deserialize<Request>(data);
    
     if (request.has_list_tests()) {
        result.type = RequestType::LIST_TESTS;
        result.input.listTestsInput = { request.list_tests().fixture_id() };
    } else if (request.has_run_test()) {
        result.type = RequestType::RUN_TEST;
        result.input.runTestInput = { .fixtureId = request.run_test().fixture_id(),
                                      .testId = request.run_test().test_id() };
    }

    return result;
}

Buffer ProtobufParser::parseListTestsOutput(const ListTestsOutput& output) {
    ListTestsResponse response;
    for (auto& test : output.tests) {
        auto* info = response.add_tests();
        info->set_id(test.id);
        *info->mutable_name() = test.name;
    }
    return ProtobufUtils::serialize(response);
}

Buffer ProtobufParser::parseRunTestOutput(const RunTestOutput& output) {
    RunTestResponse response;
    response.set_status(output.result.status);
    return ProtobufUtils::serialize(response);
}
