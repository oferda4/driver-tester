#pragma once

#include "Buffer.h"

template <std::integral NumType>
NumType BufferUtils::toNumber(const Buffer& buffer) {
    if (buffer.size() < sizeof(NumType)) {
        throw InvalidBufferSize(buffer.size());
    }
    NumType result;
    memcpy(&result, buffer.data(), sizeof(NumType));
    return result;
}

template <std::integral NumType>
Buffer BufferUtils::fromNumber(NumType num) {
    Buffer result(sizeof(NumType), 0);
    memcpy(result.data(), &num, sizeof(NumType));
    return result;
}
