#include "ProtobufUtils.h"

#include "CastUtils.h"

using google::protobuf::Message;

Buffer ProtobufUtils::serialize(const Message& msg) {
    Buffer result(msg.ByteSizeLong());
    if (!result.empty() &&
        !msg.SerializeToArray(result.data(), CastUtils::cast<int>(result.size()))) {
        throw FailedSerializingMessage();
    }
    return result;
}
