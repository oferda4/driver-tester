#include "ProtobufParser.h"

#include "messages.pb.h"

#include "CastUtils.h"

using google::protobuf::Message;

namespace {
Buffer serializeToBuffer(const Message& msg);
Request deserializeRequest(const Buffer& buffer);
}

ParsedRequest ProtobufParser::parseRequest(const Buffer& data) {
    ParsedRequest result{};
    const Request request = deserializeRequest(data);
    
    if (request.has_list_fixtures()) {
        result.type = RequestType::LIST_FIXTURES;
        result.input.listFixturesInput = {};
    } else if (request.has_list_tests()) {
        result.type = RequestType::LIST_TESTS;
        result.input.listTestsInput = { request.list_tests().fixture_id() };
    } else if (request.has_run_test()) {
        result.type = RequestType::RUN_TEST;
        result.input.runTestInput = { .fixtureId = request.run_test().fixture_id(),
                                      .testId = request.run_test().test_id() };
    }

    return result;
}

Buffer ProtobufParser::parseListFixturesOutput(const ListFixturesOutput& output) {
    ListFixturesResponse response;
    for (auto& fixture : output.fixtures) {
        auto* info = response.add_fixtures();
        info->set_id(fixture.id);
        *info->mutable_name() = fixture.name;
    }
    return serializeToBuffer(response);
}

Buffer ProtobufParser::parseListTestsOutput(const ListTestsOutput& output) {
    ListTestsResponse response;
    for (auto& test : output.tests) {
        auto* info = response.add_tests();
        info->set_id(test.id);
        *info->mutable_name() = test.name;
    }
    return serializeToBuffer(response);
}

Buffer ProtobufParser::parseRunTestOutput(const RunTestOutput& output) {
    RunTestResponse response;
    response.set_status(output.result.status);
    return serializeToBuffer(response);
}

namespace {
Buffer serializeToBuffer(const Message& msg) {
    Buffer result(msg.ByteSizeLong());
    if (!result.empty()) {
        if (!msg.SerializeToArray(result.data(), CastUtils::cast<int>(result.size()))) {
            throw FailedSerializingMessage();
        }
    }
    return result;
}

Request deserializeRequest(const Buffer& buffer) {
    Request request;
    if (!request.ParseFromArray(buffer.data(), CastUtils::cast<int>(buffer.size()))) {
        throw FailedParsingMessage();
    }
    return request;
}
}
