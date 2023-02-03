#pragma once

#include <google/protobuf/message.h>

#include "Buffer.h"

struct FailedSerializingMessage : std::exception {
    // left blank intentionally
};

struct FailedParsingMessage : std::exception {
    // left blank intentionally
};

class ProtobufUtils {
public:
    ProtobufUtils() = delete;

    static Buffer serialize(const google::protobuf::Message& msg);
    template <typename MessageType>
        requires std::derived_from<MessageType, google::protobuf::Message>
    static MessageType deserialize(const Buffer& buffer);
};

#include "ProtobufUtils.inl"
