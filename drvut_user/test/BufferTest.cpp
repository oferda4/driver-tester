#include <gtest/gtest.h>

#include "Buffer.h"

namespace {
template<std::integral T>
void testNumberConversion();
}

TEST(BufferTest, numberConversion) {
    ASSERT_NO_THROW(testNumberConversion<uint16_t>());
    ASSERT_NO_THROW(testNumberConversion<int32_t>());
    ASSERT_NO_THROW(testNumberConversion<uint64_t>());
}

TEST(BufferTest, toNumberBadSize) {
    using ArbitraryNumType = uint32_t;
    ASSERT_THROW(BufferUtils::toNumber<ArbitraryNumType>(Buffer(sizeof(ArbitraryNumType) - 1, 0)), 
                 InvalidBufferSize);
}

namespace {
template <std::integral T>
void testNumberConversion() {
    const T arbitraryNum = static_cast<T>(11223344);
    Buffer buffer = BufferUtils::fromNumber(arbitraryNum);
    T resultNum = BufferUtils::toNumber<T>(buffer);
    ASSERT_EQ(arbitraryNum, resultNum);
}
}
