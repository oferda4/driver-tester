#pragma once

#include "ProtobufUtils.h"

#include "CastUtils.h"

template <typename MessageType>
    requires std::derived_from<MessageType, google::protobuf::Message>
MessageType ProtobufUtils::deserialize(const Buffer& buffer) {
    MessageType msg;
    if (!msg.ParseFromArray(buffer.data(), CastUtils::cast<int>(buffer.size()))) {
        throw FailedParsingMessage();
    }
    return msg;
}
