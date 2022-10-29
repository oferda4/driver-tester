#include "Buffer.h"

#include <algorithm>

InvalidBufferSize::InvalidBufferSize(size_t size)
    : std::exception("invalid buffer size", static_cast<int>(size)) {
    // left blank intentionally
}

void BufferUtils::append(Buffer& dest, const Buffer& src) {
    dest.insert(dest.end(), src.begin(), src.end());
}

bool BufferUtils::equal(const Buffer& buff1, const Buffer& buff2) {
    return std::equal(buff1.begin(), buff1.end(), buff2.begin(), buff2.end());
}
