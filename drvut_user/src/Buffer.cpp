#include "Buffer.h"

InvalidBufferSize::InvalidBufferSize(size_t size)
    : std::exception("invalid buffer size", size) {
    // left blank intentionally
}