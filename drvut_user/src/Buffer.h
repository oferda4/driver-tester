#pragma once

#include "Defs.h"

struct InvalidBufferSize : std::exception {
    InvalidBufferSize(size_t size);
};

using Buffer = std::vector<byte>;

class BufferUtils {
public:
    BufferUtils() = delete;

    template<std::integral NumType>
    static NumType toNumber(const Buffer& buffer);
    template <std::integral NumType>
    static Buffer fromNumber(NumType num);
};

#include "Buffer.inl"
