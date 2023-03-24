#include "ProtobufParser.h"

#include "InternalMessages.h"
#include "ProtobufUtils.h"
#include "runner_user_messages.pb.h"

ParsedRequest ProtobufParser::parseRequest(const Buffer& data) {
    ParsedRequest result{};
    const Request request = ProtobufUtils::deserialize<Request>(data);

    if (request.has_run_test()) {
        result.type = RequestType::RUN_TEST;
        result.input.runTestInput = { .testId = request.run_test().test_id() };
    } else if (request.has_list_tests()) {
        result.type = RequestType::LIST_TESTS;
        result.input.listTestsInput = {};
    } else {
        throw std::invalid_argument("Invalid request");
    }

    return result;
}

Buffer ProtobufParser::serializeListTestsOutput(const InternalMessages::ListTestsOutput& output) {
    ListTestsResponse response;
    for (auto& test : output.tests) {
        auto* info = response.add_tests();
        info->set_id(test.id);
        *info->mutable_name() = test.name;
    }
    return ProtobufUtils::serialize(response);
}

Buffer ProtobufParser::serializeRunTestOutput(const InternalMessages::RunTestOutput& output) {
    RunTestResponse response;
    response.set_passed(output.result.passed);
    response.set_msg(output.result.msg);
    return ProtobufUtils::serialize(response);
}
